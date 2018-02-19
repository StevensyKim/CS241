bne $0, $2, 3
lis $3
.word -1
jr $31
lis $5
.word 4
mult $5, $2
mflo $6
sub $6, $6, $5
add $4, $1, $6
lw $3, 0($4)
jr $31
