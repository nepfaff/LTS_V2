Dependent source test
*
V1 N001 0 10
R1 N002 N001 10k
R2 N003 0 10k
C1 N003 N002 100n
*
.tran 0.0001 .002 0 1
.end