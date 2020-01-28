.name    "st"
.comment "Invincible"

ld      %255, r1
aff     r1
#st      r1, 65
ld      %100, r2
aff     r2
add     r1, r2, r3
aff     r3
sub     r3, r1, r2
aff     r2
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
or      r4, r5, r6
aff     r6
xor     r4, r5, r6
aff     r6
ldi     %20, %2, r6
aff     r6
ld      %100, r2
aff     r2
sti     r2, %20, %4
live    %1
