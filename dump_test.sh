touch diff
rm diff
./corewar -dump $1 $2 $3 | tail -64 > a && ./corewar_r -d $1 $2 $3 | tail -n +4 | cut -c 10- > b && diff a b > diff
cat diff