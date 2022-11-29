;;; Yi Zhu
;;; 116513081
;;; yzhu1217

;;; Implementation that computes the nth fibonacci number.

    .global fib                 ; exposes fib as a label for the linker
fib:                            ; the label: the next instruction starts fib() function.
    ;; Add your code here.
    cpi r24, 0  ;compare the argument parameter with 0, base case
    breq 1f     ;branch to 1 forward to return
    cpi r24, 1  ;compare the argument parameter with 1, base case
    breq 1f     ;branch to 1 forward to return

    push r24 
    push r25    ;callee-save the the value for recursive use

    sbiw r24,1  ;subtract 1 from the value
    call fib    ;recursive call

    pop r31    ;clear the registers to set it to 0
    pop r30 

    push r24    ;callee save 
    push r25

    sbiw r30, 2 ;subtract 2 from the value
    movw r24, r30 ;copy the value from r30 to r24

    call fib    ;recursive call
    pop r31     ;free up the register r31:r30
    pop r30     

    add r24, r30
    adc r25, r31    ;move the value from r30:r31 to the return value account for overflow 

1:    
    ret                         ; returns.  necessary.
