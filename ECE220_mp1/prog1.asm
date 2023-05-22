;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; The code below prints the histogram. The approach I took was to divide our tasks 
; into sections printing the label, then a space, then the hexadecimal number, 
; and finally a newline. The label was printed by starting with the ASCII 
; character '@', and using a pointer to print the rest of the labels. 
; Next I printed a single space. To print the hexadecimal number I used the pointer 
; to identify the current bin. I then copied the most significant 4 bits to R0, 
; identified if it was a 0-9 or A-F, printed accordingly, and continued doing this 
; 3 more times. I followed this up by printing a newline and then repeated the 
; process 26 more times.

; table of registers used in this part of the program
; R0 held the character being printed
; R1 acted as the loop count for all 27 bins
; R2 was used as a temporary register
; R3 held the pointer for both our label and our hexadecimal number
; R4 held the hexadecimal number at our current histogram address
; R5 acted as the loop count for the 4 bits of a hexadecimal character
; also was used as a temporary register
; R6 held the loop count for the 4 hexadecimal characters being printed
	AND R3, R3, #0		; clearing register 3
	AND R4, R4, #0		; clearing register 4
	AND R5, R5, #0		; clearing register 5
	AND R6, R6, #0		; clearing register 6
	LD R1, NUM_BINS		; loading number of bins into R1
PRINT_LABEL
	LD R2, NUM_AT		; loading the number equal to ASCII '@'
	ADD R2, R2, R3		; pointing R2 towards our current label
	AND R0, R0, #0		; clearing R0
	ADD R0, R2, #0		; putting value of R2 into Ro
	OUT			; printing the value
PRINT_SPACE
	LD R0, SPACE		; loading the ASCII space to R0
	OUT			; printing the space
	ADD R6, R6, #4		; setting our loop counter to 4 (all hex characters)
PRINT_NUM
	LD R4, HIST_ADDR	; load the histogram address to R4 (x3F00)
	ADD R4, R4, R3		; point R4 to the current histogram address
	LDR R4, R4, #0		; load the value at our current address
DEVELOP_NUM
	AND R5, R5, #0		; clearing register 5
	AND R0, R0, #0		; clearing register 0
	ADD R5, R5, #4		; set our bit counter to 4 (1 hex character)
INNER_LOOP			; start of our loop of moving our hex number in R4 to R0 to print
	BRz NUM_OUT		; checks R5, if R5 is 0 we have finished copying one hex char
	ADD R0, R0, R0		; left shift R0
	ADD R4, R4, #0		; restate the value of R4
	BRzp #1			; check if R4 is non-negative, if so skips one line
	ADD R0, R0, #1		; if R4 is negative add one to R0
	ADD R4, R4, R4		; left shift R4
	ADD R5, R5, #-1		; decrement our digit counter
	BRnzp INNER_LOOP	; go back to start of our loop
NUM_OUT
	LD R2, OFF2		; load our offset2 (#48) to R2
	ADD R5, R0, #0		; copy R0 to R5
	ADD R5, R5, #-9		; add #-9 to R5
	BRnz #1			; if R5 is now not positive we skip one line
	ADD R0, R0, #7		; if R5 is positive we add #7 to R0
	ADD R0, R0, R2		; add offset2 stored in R2 to R0
	OUT			; print our hex character
	ADD R6, R6, #-1		; decrement hex characters counter
	BRp DEVELOP_NUM		; if not 0, go to start of loop

PRINT_NEWLINE
	LD R0, NEWLINE		; load newline to R0
	OUT			; print the newline
	ADD R3, R3, #1		; increment our pointer to next character
	ADD R1, R1, #-1		; decrement our bin counter
	BRp PRINT_LABEL		; if our bin counter is not 0 lets loop back to top


DONE	HALT			; done


; the data needed by the program
OFF1		.FILL x0011	; our first offset
OFF2		.FILL #48	; our second offset
NEWLINE		.FILL x000A	; the hexadecimal equivalent of ASCII newline
SPACE		.FILL xFF20	; the hexadecimal equivalent of ASCII space
NUM_AT		.FILL #64	; the decimal equivalent of ASCII '@' 
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
