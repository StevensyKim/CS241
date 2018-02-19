;1 is the one we need to convert
;2 controls the 2^n addition
;3 is remainder
;4 will be the answer
;5 will be the quotient tracker
lis $10
.word 10
lis $28
.word 0xffff000c
lis $2
.word 1
lis $6
.word 2

add $4, $0, $0
add $5, $10, $0 ;starts non 0 so loop starts

loop:

beq $5, $0, 9
div $1, $10
mfhi $3 ;; remainder 
mflo $5 ;; quotient 
beq $0, $3, 1 
add $4, $4, $2

mult $2, $6
mflo $2
add $4, $2, $4

beq $0, $0, -10

end:
sw $4, 0($28)
jr $31
 
