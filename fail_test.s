.name    "st"
.comment "Invincible"

#ld      %57679874, r1 #st with good encoding byte but bad register
#ld      %57221122, r1 #st with bad encoding byte, still consumes cycles and advances but how many?
ld      %57671939, r1 #working st
#ld      %50331648, r1 #st operation code and 00 00 00
#ld      %55582720, r1 #st with encoding byte = REG, REG but bad registers.
#ld      %60825600, r1 #st with bad encoding byte, still consumes cycles and advances but how many?
aff     r1
st      r1, 256
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
