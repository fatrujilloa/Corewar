make
./corewar $1 $2 > A && ./corewar_r -v 7 $1 $2 > B
diff -a a b > diffset
diff -a a b | less