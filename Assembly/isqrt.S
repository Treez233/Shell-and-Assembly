;;; Yi Zhu
;;; 1165r2081
;;; yzhu1217

;;; Implementation of isqrt
    .global isqrt

isqrt:
    cpi r24, 2      ;check if the value is less than 2
    brlo 1f         ;branch to 1 forward to return

    push r24        ;save the low byte
    push r25        ;save the high byte

    lsr r24         ;shift r24 right one bit (divide by 2)
    lsr r24         ;shift r24 right two bits (divide by 4)

    clr r25         ;clear the high byte

    call isqrt      ;recursive call the function to calculate the square root

    lsl r24         ;shift r24 left


    movw r20, r24   ;copy the value in r24 to r26
    inc r20         ;increment r26 by 1
    mul r20, r20    ;square the value in r26 and the result will be in r0

    movw r22, r0    ;move the product in r0 to r26
    clr r1          ;clear r1

    pop r19         ;retore r19 and r18
    pop r18

    cp r18, r22     ;compare the product to the value in r22(n)
    brlt 1f         ;if r18 is less then return small

    jmp 2f          ;jump to 2 to return the large

1:
    ret             ;return
2:
    movw r24, r20   ;set the value to large
    ret             ;return