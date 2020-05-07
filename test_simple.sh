make
touch a b
rm a b
touch diff
rm diff
./corewar $1 $2 > a
./corewar_r -v 7 $1 $2 > b
diff -a a b > diff
cat diff | less