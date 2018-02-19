;$2 = 4 * $2 + $1
add $2, $2, $2
add $2, $2, $2
add $2, $2, $1

lis $4
.word 4


lw $3, 0($1)
add $1, $1, $4

;loop
beq $1, $2, 6
;$5 = A[i]
lw $5, 0($1)

slt $6, $3, $5
beq $6, $0, 1 ;;skips past the next line
add $3, $5, $0 

add $1, $1, $4
beq $0, $0, -7


end:
jr $31
