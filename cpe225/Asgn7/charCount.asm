; Ryan Blair
; Assignment 7
; Date: 11/17/15
; R1 - current char
; R2 - local result
; R3 - result from previous stacks
; R4 - search char

	.ORIG x3300
	; bookkeeping
COUNT	ADD R6, R6, #-1	; return value slot
	ADD R6, R6, #-1	; return address
	STR R7, R6, #0
	ADD R6, R6, #-1 ; dynamic link
	STR R5, R6, #0 
	ADD R5, R6, #-1 ; new frame pointer
	ADD R6, R6, #-1 ; memory for local variables

	; initialize result, search character
        LDR R4, R5, #5	; put search character into R4
 	LDR R1, R5, #4	; put current character address into R1
        LDR R1, R1, #0
	BRz TERM	; end of string check

CHECK	NOT R1, R1
	ADD R1, R1, #1	; make it negative for comparison
	ADD R2, R4, R1	; comparison
	BRnp NO

	; search char found
        AND R2, R2, #0
	ADD R2, R2, #1
	STR R2, R5, #0	; stores return value of 1 into stack 
	BRnzp NEXT

NO	AND R2, R2, #0
	STR R2, R5, #0	; stores return value of 0 into stack 

NEXT 	ADD R6, R6, #-1
	STR R4, R6, #0	; puts in search char into next stack 
	
        LDR R1, R5, #4
	ADD R1, R1, #1		
	ADD R6, R6, #-1
	STR R1, R6, #0	; puts in next char in word into next stack

        JSR COUNT	; recursive call

        ; result += charCount(str+1, c);
        LDR R3, R6, #0	; load return value from previous stack
	ADD R6, R6, #3	; R6 back to top of stack
	LDR R2, R5, #0	; loads result
	ADD R2, R2, R3
	STR R2, R5, #3 ; store return value for this stack
	BRnzp END

TERM 	STR R1, R5, #3 ; null string => R0, put in return value

END	ADD R6, R5, #1 ; pop local variables
	LDR R5, R6, #0 ; pop dynamic link
	ADD R6, R6, #1
  
	LDR R7, R6, #0 ; pop return address
	ADD R6, R6, #1 ; R6 now at return value

	RET
