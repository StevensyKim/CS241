; $28 is stdout
lis $28
.word 0xffff000c
lis $6
.word 32
; $2 is the address to stop looping at
add $2, $2, $2
add $2, $2, $2
add $2, $2, $1
; $4 is the loop variable
lis $4
.word 4
;loop
beq $1, $2, 7
; $5 = A[i]
lw $5, 0($1)

add $3, $5, $6
beq $5, $0, 1 ;; skips next line if it is a space 
add $3, $3, $6
sw $3, 0($28)


add $1, $1, $4
beq $0, $0, -8
;end
jr $31

