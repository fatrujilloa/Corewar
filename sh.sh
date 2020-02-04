make
touch a b
rm a b
./corewar test.cor test.cor > a && ./corewar_r -v 7 test.cor test.cor > b
diff -a a b | less