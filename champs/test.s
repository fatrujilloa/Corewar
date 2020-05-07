.name    "NoName"
.comment "Invincible"
#lldi     -20495, %209, r3
#aff     r3
#sti     r1, %1, r3
lqldi    20495, %209, r3
aff     r3
sti     r1, %1, r3
lldi    %342049, %2049, r3
aff     r3
sti     r1, 88, r3
lldi    r1, r3, r3
aff     r3
sti     r1, %10, r3
lldi    r1, %2049, r3
aff     r3
sti     r1, %1000, r3
lld     %-41, r4
sti     r1, %128, r4
lld     %0, r4
sti     r1, %128, r4
live    %4294967295
#fork    %514
st      r1, r15
aff     r15
ldi     -20495, %209, r3
aff     r3
sti     r1, %1, r3
ldi     20495, %209, r3
aff     r3
sti     r1, %1, r3
ldi     %342049, %2049, r3
aff     r3
sti     r1, 88, r3
ldi     r1, r3, r3
aff     r3
sti     r1, %10, r3
ldi     r1, %2049, r3
aff     r3
sti     r1, %1000, r3
lld     %2049, r4
sti     r1, %128, r4
lld     2049, r4
aff     r4
sti     r1, %128, r4
sti     r1, %120, r15
ld      2049, r2
ld      %4294967195, r14
and     10, r2, r3
aff     r3
sti     r2, r14, r14
st      r1, 10;
aff     r15
sti     r1, 14, r2
ld      100, r2
fork    %1
#lld     2049, r4
#sti     r1, %128, r4
lld     %2049, r4
#sti     r1, %128, r4
ld     2049, r4
#sti     r1, %128, r4
ld     %2049, r4
#sti     r1, %128, r4
ld      %12345, r5
#sti     r9, 256, r5
aff     r4
#sti     r2, 60, r2
live    %2
ld      %256, r10
aff     r10
#sti     r10, %128, r4
#aff     r1
ld      %255, r1
aff     r1
st      r1, 65
add     r1, r2, r3
aff     r3
sti     r1, %100, r3
aff     r3
sub     r3, r1, r2
aff     r2
#sti     r1, %100, r3
aff     r3
ld      %1000, r1
aff     r1
sub     r2, r1, r2
aff     r2
ld      %263, r4
aff     r4
ld      %11, r5
aff     r5
and     r4, r5, r6
aff     r6
and     1, %123, r6
aff     r6
or      r4, r5, r6
aff     r6
xor     r4, r5, r6
aff     r6
ldi     %20, %2, r6
aff     r6
ld      %100, r2
aff     r2
ld      %0, r10 
zjmp    %511
sti     r2, %20, %4
live    %1
