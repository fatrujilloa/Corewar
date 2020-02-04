.name    "Minitest2"
.comment "Invincible"

zjmp    %410
ld      %1, r2
ld      %16711680, r3
ld      %511, r4
ld      %4278780400, r5 #copy next jump
ld      %57672961, r6   #copy the st that copies next jump
ld      %57673217, r7   #copy the st that copies copy jump
ld      %255, r8            #part 2
st      r5, 511
st      r6, 502
st      r8, 493
st      r7, 487
ld      %0, r9
zjmp    %473
