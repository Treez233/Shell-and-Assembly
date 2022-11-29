;;; Yi Zhu
;;; 116513081
;;; yzhu1217

;;; Global data
        .data
pctd:
        .asciz "%d"            ;Format string
pctd2:
        .asciz " %d"            ;Format string

        .text

;;; Implementation of reverse_prefix_sum
    .global reverse_prefix_sum

reverse_prefix_sum:
    clr r27
    movw r26, r24       ;load the first element of the array to X

    clr r21             ;clearing r21 r24 and r25
    clr r24
    clr r25

    ld r20, X+          ;load r20 with X with post incremented

    cpi r20, -1         ;compare the value in r20 to -1(base case)
    breq 1f             ;branch to 1 to return

    push r26            ;save the value in X    
    push r27       

    push r20            ;save the current element 

    movw r24, r26       ;copy the next element of the array to r24
    call reverse_prefix_sum ;recursively call reverse_prefix_sum

    pop r20             ;restoring the values in r20 that we saved
    pop r27             ;restoring the value of X
    pop r26

    add r24, r20        ;add the current value and the saved value
    adc r25, r21        ;account for overflow


    st -X, r24          ;move the element back one and add the value in r24 to the array 
1:
    ret                 ;return

;;; Implementation of print_array
    .global print_array

print_array:
    clr r27
    movw r26, r24       ;load the first element of the array to X
    
    clr r25             ;initialize the register r24:r25

    ld r24, X+          ;load the first element into the array with post increment
    cpi r24, -1         ;compare to -1 to check if the end of the array has been reached
    breq 1f             ;branch to 2 if equal


    ldi r22, lo8(pctd)  ;load the format string without spaces
    ldi r23, hi8(pctd)

    call print          ;call to print the element

    ld r24, X+          ;load the next element to r24
with_spaces:
    cpi r24, -1         ;check if the end the array has been reached
    breq 1f             ;branch to 2 if r24 == -1

    ldi r22, lo8(pctd2)  ;load the format string with spaces
    ldi r23, hi8(pctd2)

    call print          ;call to print the element

    clr r25             ;clr r24:r25
    ld r24, X+          ;load the next element to r24
    jmp with_spaces     ;jump to with_spaces to repeat the loop
1:
    clr r25             ;clr r24:r25
    ldi r24, 10         ;load a new line character into r24
    call putchar        ;print the new line character

    ret                 ;return

print:
    clr r25

    push r27            ;save the values in the registers
    push r26
    push r25
    push r24
    push r23
    push r22

    call printf         ;print the elements

    pop r22             ;restore the registers
    pop r23
    pop r24
    pop r25
    pop r26
    pop r27

    ret                 ;return