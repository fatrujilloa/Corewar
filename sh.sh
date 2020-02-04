make
./corewar test.cor test.cor > a && ./corewar_r -v 7 test.cor test.cor > b
diff -a a b | less