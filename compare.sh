make
touch a b diffset
rm a b diffset
./corewar $1 $2 $3 $4 > A && ./corewar_r -a -v 7 $1 $2 $3 $4 > B
diff -a a b > diffset
diff -a a b | less