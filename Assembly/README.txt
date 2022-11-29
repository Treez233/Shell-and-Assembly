Example on how you could test print_array

The following illustrates how you can write an assembly driver 
that tests whether your print_array function implementation 
(for reverse_prefix_sum) is correct.  Notice we are not relying 
on a makefile.  The % represents the linux prompt and the 
sample driver is in the file check_print_array.S.  

Disclaimer: just because your code works for the driver, 
does not mean it is completely correct.

% cat check_print_array.S
        .data
 
elems: .byte 10, 20, 7, -1
 
        .text
 
.global main
main:
        call init_serial_stdio
 
        ldi r24, lo8(elems)    ; initializing argument
        ldi r25, hi8(elems)
 
        call print_array
 
        cli                    ; stopping program
        sleep
 
        ret
 
% avr-gcc -g -mmcu=atmega32u4 check_print_array.S reverse_prefix_sum.S serial.c
% simavr --mcu atmega32u4 a.out
Loaded 2058 .text at address 0x0
Loaded 68 .data
Serial simulator online.
10 20 7
%
