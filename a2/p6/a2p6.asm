lis $28
.word 0xffff000c
lis $2 ;where the ascii for nums start
.word 48
lis $6 ;this is the negative sign
.word 45 
lis $20
.word 10
lis $10
.word 4

;this prints the negative if it is
slt $3, $1, $0 ;if 3 is 1 then register 1 holds a negative
beq $3, $0, 2
sw $6, 0($28)
sub $1, $0, $1 ; makes it positive now
add $8, $1, $0 ;puts it into 8

bne $8, $0, 6
add $9, $10, $9
div $8, $20
mfhi $7
sw $7, 0($9)
mflo $8
bne $0, $0, -7
 
bne $9, $0, 5
lw $11, 0($9)
add $11, $11, $2
sw $11, 0($28)
sub $9, $9, $10
bne $0, $0, -6
sw $20, 0($28)
jr $31
