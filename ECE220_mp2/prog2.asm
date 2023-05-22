;
; The code below represents a calculator, capable of evaluating postfix expressions.
; The flow of our code is to first read an input from the keyboard and echo it to the console.
; Then based on the character, we can proceed to a subroutine. 
; If the character is a number/operand, we push it onto the stack. 
; If the character is an operator, we pop two values from the stack, 
; perform the operation, and push the result onto the stack.
; This flow repeats for every character read from the keyboard and 
; only stops given the ASCII char "=", or an invalid character, such as a letter.
; When the ASCII char "=" is typed, we move to print the output of the expression given, 
; in hexadecimal representation. 
; If an invalid character is entered, we end the program and print "Invalid Expression".
; The operations our calculator uses is addition, subtraction, multiplication, division, and power.
; Addition is done through the ADD function while subtraction also uses the ADD function 
; but also negates the first number popped. 
; Multiplication is done by adding a number x to itself y times (x times y). 
; Division is done by counting the number of times the first number popped 
; negated can be added to the second number before the sum is negative. 
; Power is done by taking the first value, 
; and decrementing it to be a counter x. The second number y is multiplied by itself y times 
; through repeated addition. 
; We repeat this process each time "updating" the number to be multiplied y times 
; based on the result of the previous multiplication. 
; We end the loop when our counter x hits 0.
; 
.ORIG x3000

START
	GETC			; reading input char from keyboard, storing in R0
	OUT			; echoing char to console
EVALUATE
	ADD R1, R0, #-16	; checking if input is the operator div, min, plus
	ADD R1, R1, #-16	; mul or the character space
	ADD R1, R1, #-16	
	BRn OPERATOR		; if negative, could be an operator
	ADD R1, R1, #-9		; checking if input is a number 0-9
	BRnz NUMBER		; if n or z, input is a number
	ADD R1, R1, #-4		; checking if input is the character "="
	BRz EQUAL		; if z then input is "="
	ADD R1, R1, #-16	; checking if input is the operator "^"
	ADD R1, R1, #-16
	ADD R1, R1, #-1
	BRz TO_EXP		; if z then input is "^"
	BRnp INVALID_LOOP	; else invalid input
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	ADD R3, R5, #0		; load the value thats been popped to R3
	AND R1, R1, #0		; clear R1
	ADD R1, R1, #4		; setting our hex char counter to 4
DEVELOP_HEX
	BRz DONE		; if R1 is 0, we have printed all 4 hex char and are done
	AND R2, R2, #0		; clear R2
	AND R0, R0, #0		; clear R0 so as to not mess up when we print
	ADD R2, R2, #4		; setting up our bit counter to 4
INNER_HEX
	BRz OUT_HEX		; if R is 0, then we have our 4 bits and can move to print
	ADD R0, R0, R0		; left shift ouput R0
	ADD R3, R3, #0		; restate our hex number in question
	BRzp #1			; if 1 at leftmost bit of R3, we skip one line
	ADD R0, R0, #1		; add #1 to output R0
	ADD R3, R3, R3		; left shift R3
	ADD R2, R2, #-1		; decrement our bit counter
	BRnzp INNER_HEX		; loop back to start
OUT_HEX
	ADD R4, R0, #0		; load R0 to R4
	ADD R4, R4, #-9		; add #-9 to R4
	BRnz #1			; if R4 is not positive we skip one line
	ADD R0, R0, #7		; if R4 is positive we add #7
	ADD R0, R0, #10		; add #48 to R4, to get the complementary ASCII char
	ADD R0, R0, #10
	ADD R0, R0, #10
	ADD R0, R0, #10
	ADD R0, R0, #8
	OUT			; print our hex char
	ADD R1, R1, #-1		; decrement hex char counter
	BRnzp DEVELOP_HEX	; loop to the top
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;

OPERATOR			; checks for div, min, plus, mul, or char space
	ADD R1, R1, #1		; checking for divide
	BRz TO_DIV		; if z, we move to perform division
	ADD R1, R1, #2		; checking for subtract
	BRz TO_MIN		; if z, we move to perform subtraction
	ADD R1, R1, #2		; checking for add
	BRz TO_PLUS		; if z, we move to perform addition
	ADD R1, R1, #1		; checking for multiply
	BRz TO_MUL		; if z, we move to perform multiplication
	ADD R1, R1, #10		; checking for space
	BRz SPACE		; if z, we move to deal with space
	LD R0, INVALID		; if none of the operators above, must be 
	OUT			; and invalid char, so we move to deal with that
	BRnzp START		; return to start to recieve another char
TO_DIV		
	JSR DIV			; call our division function
	BRnzp START		; loop back to start when operation is done
TO_MIN
	JSR MIN			; call our subtraction function
	BRnzp START		; loop back to start when operaion is done
TO_PLUS
	JSR PLUS		; call our addition function
	BRnzp START		; loop back to start when operation is done
TO_MUL
	JSR MUL			; call our multiplication function
	BRnzp START		; loop back to start when operation is done
TO_EXP
	JSR EXP			; call our power function
	BRnzp START		; loop back to start when operation is done

NUMBER
	ADD R1, R1, #9		; add 9 to get the complementary decimal number
	ADD R0, R1, #0		; store that number in R0
	JSR PUSH		; push our number onto the stack
	BRnzp START		; loop back to start to retrieve new char
EQUAL
	LD R3, STACK_START	; loads start of our stack to R3
	LD R4, STACK_TOP	; loads top of our stack to R4
	NOT R4, R4		; negate R4 by inverting bits and adding #1
	ADD R4, R4, #1
	ADD R3, R3, R4		; add R3 and R4 to check if there is only one value in stack
	ADD R3, R3, #-1		; decrement our sum by #1
	BRnp INVALID_LOOP	; if we have 0 or 2+ numbers in stack "=" is invalid
	JSR POP			; if only 1 number in stack then we pop
	ADD R1, R5, #-1		; check if underflow
	BRz INVALID_LOOP	; if present invalid
	ADD R5, R0, #0		; put result in R5
	BRnzp PRINT_HEX		; move to print result in hex
SPACE
	LD R0, SPACE_CHAR	; load the hex equivalent to ASCII space to R0 
	OUT			; print the space
	BRnzp START		; loop back to the start to retrieve new char
INVALID_LOOP
	LEA R0, INVALID		; load the invalid string
	PUTS			; print the null terminated string
	BRnzp DONE		; proceed to end

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
	ST R7, SAVE_SEVEN	; save R7
	JSR POP			; pop value 1
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if present must be invalid
	ADD R3, R0, #0		; store first value in R3
	JSR POP			; pop value 2
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if present must be invalid
	ADD R4, R0, #0		; store second value in R4
	ADD R0, R3, R4		; store the sum of value 1 and 2 in R0
	JSR PUSH 		; push sum onto stack
	LD R7, SAVE_SEVEN	; load back our saved R7
	RET			; return to calling function
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
	ST R7, SAVE_SEVEN	; store R7 so as to save current value
	JSR POP			; pop first number from stack to R0
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if present must be invalid
	NOT R3, R0		; negate first number and put it in R1
	ADD R3, R3, #1		
	JSR POP			; put second number from stack to R0
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if present must be invalid
	ADD R4, R0, #0		; load second number to R4
	ADD R0, R4, R3		; add our two numbers
	JSR PUSH		; push the new number to our stack
	LD R7, SAVE_SEVEN	; load back our saved R7 value
	RET			; go back to previous function
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
	ST R7, SAVE_SEVEN	; store R7 to save current value
	JSR POP			; pop first value from stack
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if present must be invalid
	ADD R3, R0, #0		; store first value in R3
	JSR POP			; pop second value from stack
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if present, must be invalid
	ADD R4, R0, #0		; store second value in R4
	AND R0, R0, #0		; clear R0
MUL_LOOP
	ADD R0, R0, R4		; add R4 and R0 to R0
	ADD R3, R3, #-1		; decrement first value
	BRnp MUL_LOOP		; if R3 is not 0, loop back to MUL_LOOP
	JSR PUSH		; if R3 is 0, push result onto stack
	LD R7, SAVE_SEVEN	; load back saved R7
	RET			; return to calling function
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
;input R3, R4
;out R0
DIV	
	ST R7, SAVE_SEVEN	; store R7 to save current value
	AND R2, R2, #0		; clearing R2
	JSR POP			; pop first value from stack
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if underflow present must be invalid
	ADD R3, R0, #0		; store first value in R3
	BRz INVALID_LOOP	; if 0, then result will be undefined
	BRn IF_NEG_1		; if first value is already negative, skip negation
	NOT R3, R3		; negate first value
	ADD R3, R3, #1
SKIP_1
	JSR POP			; pop second value from stack
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if underflow present must be invalid
	ADD R4, R0, #0		; store second value in R4
	BRn IF_NEG_2		; if second value is negative, lets negate		
SKIP_2
	AND R0, R0, #0		; clear R0
DIV_LOOP
	ADD R4, R4, R3		; sum our negated first value and second value
	BRn DIV_DONE		; if sum is negative move to finish operation
	ADD R0, R0, #1		; add 1 to R0
	BRnzp DIV_LOOP		; loop back to repeat summing
DIV_DONE
	ADD R2, R2, #-1		; decrement our signal register
	BRnp #2
	NOT R0, R0		; if signal was 1, we negate our result
	ADD R0, R0, #1	
	JSR PUSH		; push result onto stack
	LD R7, SAVE_SEVEN	; load back saved R7
	RET			; return to calling function
IF_NEG_1
	ADD R2, R2, #1		; signal that first number was negative
	BRnzp SKIP_1
IF_NEG_2
	NOT R4, R4		; if second value is negative lets negate it
	ADD R4, R4, #1
	ADD R2, R2, #1		; signal that second number was negative
	BRnzp SKIP_2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
	ST R7, SAVE_SEVEN	; store R7 to save current value
	JSR POP			; pop first value
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if underflow present must be invalid
	ADD R3, R0, #0		; load first number to R3, to be exponent
	ADD R3, R3, #-1		; decrement exponent by one, to act as a counter
	BRz EXP_ONE		; if exponent is 1, we can loop to EXP_ONE
	JSR POP			; pop second value
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if underflow present must be invalid
	ADD R4, R0, #0		; load our base number to R4
	ADD R2, R4, #0		; copy base to R2
EXP_START
	AND R0, R0, #0		; clear R0
	ADD R5, R4, #0		; copy base to R5
EXP_LOOP
	ADD R0, R2, R0		; sum R0 and R2 and store in R0, 
	ADD R5, R5, #-1		; decrement counter, which is base number
	BRnp EXP_LOOP		; loop to EXP_LOOP if counter is not yet 0
EXP_LOOPTWO
	ADD R2, R0, #0		; store our new value to be summed in R2
	ADD R3, R3, #-1		; do the multiplication exponent-1 amount of times
	BRp EXP_START		; if our counter is not 0 lets continue multiplying
	JSR PUSH		; push result onto stack
	LD R7, SAVE_SEVEN	; load saved R7
	RET			; return to calling function
EXP_ONE
	JSR POP			; pop second value
	ADD R1, R5, #-1		; check for underflow
	BRz INVALID_LOOP	; if underflow present must be invalid
	JSR PUSH		; push second value to stack
	LD R7, SAVE_SEVEN	; load saved R7
	RET			; return to calling function
	
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		; clear R5
	LD R3, STACK_END	; load end of stack
	LD R4, STACK_TOP	; load top of stack
	ADD R3, R3, #-1		; add end of stack to #-1
	NOT R3, R3		; negate R3
	ADD R3, R3, #1		;
	ADD R3, R3, R4		; sum R3 and R4
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		; if overflow, set R5 to #1
DONE_PUSH
	LD R3, PUSH_SaveR3	; load back R3
	LD R4, PUSH_SaveR4	; load back R4
	RET			; return to calling function


PUSH_SaveR3	.BLKW #1	; saved spot for R3
PUSH_SaveR4	.BLKW #1	; saved spot for R4


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	; load start of stack
	LD R4, STACK_TOP	; load top of stack
	NOT R3, R3		; negate start of stack
	ADD R3, R3, #1		;
	ADD R3, R3, R4		; subtract top and start of stack
	BRz UNDERFLOW		; if the same then underflow is present
	ADD R4, R4, #1		; add R4 to 1
	LDR R0, R4, #0		; load R4 to R0
	ST R4, STACK_TOP	; store R4 to STACK_TOP
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		; if underflow then add #1 to R5
DONE_POP
	LD R3, POP_SaveR3	; load saved R3
	LD R4, POP_SaveR4	; load saved R4
	RET			; return to calling function

DONE	HALT

SAVE_SEVEN	.BLKW #1	; saved location to store R7
POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
INVALID		.STRINGZ "Invalid Expression" ; invalid expression to be printed
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
SPACE_CHAR	.FILL x0020	; ASCII equivalent to space

.END
