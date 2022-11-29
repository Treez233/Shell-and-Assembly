;;; Yi Zhu
;;; 116513081
;;; yzhu1217

;;; Implementation of palindrom.
    .global is_palindrome

is_palindrome:

    push r29        ;;save the value in register r28:29
    push r28

    movw r28, r24   ;;store the string to the register r28:29

    call Strlen     ;;get the length of the string passed in
    
    adiw r24,1      ;;add one to the string length (strlen(r24) + 1)
    movw r16,r24    ;;copy the string to r16
    lsr r16         ;;split the string to 2 parts by dividing by 2
                    ;;use that for the upper limit of the loop

    sbiw r26, 2     ;;move r26 to point to the last character

    ldi r18, 1      ;;initialize the lower limit of the loop to 1(i = 1)
    clr r19
1:
    cp r16, r18     ;;compare the upper limit(r16) to the lower limit(r18)
    brlo 4f         ;;branch to 4 if r16 is less than r18

    ld r22, Y       ;;load the first section of the string to r22
    ld r23, X       ;;load the second section of the string to r23

    cp r22,r23      ;;compare r22 to r23
    breq 2f         ;;branch to 2 if they are equal

    jmp 3f          ;;branch to 3 if they are not equal
2:  
    adiw r28, 1     ;;move forward one to the next character in the string
    sbiw r26, 1     ;;move backward one to the previous character in the string

    inc r18
    jmp 1b

3:
    ldi r24, 0      ;;set the return value to 0(failure)

    pop r28         ;;restore the value in  r28:29    
    pop r29

    ret             ;;return

4:
    ldi r24, 1      ;;set the return value to 1(success)

    pop r28         ;;restore the value in r28:29
    pop r29

    ret             ;;return


    
;;; Strlen
    .global Strlen
Strlen:
    ;;; uint16_t Strlen(char *arg)
    movw r26, r24        ;; copy argument to X (r27:26) pointer
    mov r27, r25
    ldi r24, 0           ;; initialize return value to zero
    clr r25
2:  
    ld r16, X+          ;; load X with post-increment
    cpi r16, 0          ;; if loaded value was zero, branch 1f (label 1, forward)
    breq 1f
    adiw r24, 1         ;; increment return value
    jmp 2b              ;; jump 2b (label 2, backward)
1:

    ret                 ;; return