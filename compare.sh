make
./corewar $1 $2 > a && ./corewar_r -v 7 $1 $2 > b
diff -a a b | less