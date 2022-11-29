# set the microcontroller; This is the one used in the
# circuit playground.  To use a different controller,
# pins_arduino.h in this directory may need to be replaced.

MCU=atmega32u4

RUN_AVR=simavr --mcu $(MCU)

# if not using grace, vagrant, or the provisioning steps in
# the Vagrantfile to install a modified simavr globally, use
# a relative path to the run_avr program.

# RUN_AVR=../../../circuit-playground/simavr/simavr/run_avr --mcu $(MCU) 

ELFS=fibonacci_s fibonacci_r palindrome_s palindrome_r isqrt_s isqrt_r reverse_prefix_sum_s reverse_prefix_sum_r
just_compile: $(ELFS)

# The following rule takes a .S file, assembles it, and
# links it with a compiled serial.c, which gives printf /
# putchar somemplace to go.

%: %.S 
	avr-gcc -g -mmcu=$(MCU) $<   serial.c -o $@

%.s: %.c
	avr-gcc -S -mmcu=$(MCU) $<  -o $@

# the .gdb rule starts a simulator but does not execute any instructions
# until "avr-gdb assembler" (or whatever for the second parameter) is run
# and given the command to "continue".
%.gdb: %
	@echo "adding add-auto-load-safe-path .gdbinit to ~/.gdbinit configuration file"
	grep "add-auto-load-safe-path .gdbinit" ~/.gdbinit || echo "add-auto-load-safe-path .gdbinit" >> ~/.gdbinit

	$(RUN_AVR) -g $* & avr-gdb $* 

# the .run rule starts a simulator and executes the instructions.  If the
# code does not end with "cli\n sleep", the simulator will continue to execute
# the code.  The library wrapper has an infinite loop that would otherwise
# execute after main().
%.run: %
	$(RUN_AVR) $*

#	avr-as -mmcu=atmega128 --gstabs -o $@ $<

isqrt_r: isqrt_reference.c isqrt_driver.c serial.c 
	avr-gcc -g -mmcu=$(MCU) $^ -o $@

isqrt_s: isqrt.S isqrt_driver.c serial.c 
	avr-gcc -g -mmcu=$(MCU) $^ -o $@

palindrome_r: palindrome_reference.c palindrome_driver.c serial.c 
	avr-gcc -g -mmcu=$(MCU) $^ -o $@

palindrome_s: palindrome.S palindrome_driver.c serial.c 
	avr-gcc -g -mmcu=$(MCU) $^ -o $@

fibonacci_r: fibonacci_reference.c fibonacci_driver.c serial.c 
	avr-gcc -g -mmcu=$(MCU) $^ -o $@

fibonacci_s: fibonacci.S fibonacci_driver.c serial.c 
	avr-gcc -g -mmcu=$(MCU) $^ -o $@

reverse_prefix_sum_s: reverse_prefix_sum.S reverse_prefix_sum_driver.c serial.c 
	avr-gcc -g -mmcu=$(MCU) $^ -o $@

reverse_prefix_sum_r: reverse_prefix_sum_reference.c reverse_prefix_sum_driver.c serial.c 
	avr-gcc -g -mmcu=$(MCU) $^ -o $@

clean:
	rm -f $(ELFS) *_reference.s
