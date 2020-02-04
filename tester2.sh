i=3300
touch diff.txt
rm diff.txt
./corewar -dump $i $2 $3 | tail -64 > a && ./corewar_r -d $i $2 $3 | tail -n +4 | cut -c 10- > b && diff a b > diff.txt
while ! [ -s diff.txt ] && [ $i -le $1 ]
do
    echo "$i-th cycle"
    i=$(( $i + 1 ))
    ./corewar -dump $i $2 $3 | tail -64 > a && ./corewar_r -d $i $2 $3| tail -n +4 | cut -c 10- > b && diff -a a b > diff.txt
done
cat diff.txt