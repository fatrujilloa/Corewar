i=1
touch diff.txt
rm diff.txt
touch diff.txt
./corewar $1 $2 > a && ./corewar_r $1 $2 > b
while ! [ -s diff.txt ]
do
    sed -n "$ip" a > c
    sed -n "$ip" b > d
    diff c d > diff.txt
    echo "$i-th cycle"
    i=$(( $i + 1 ))
done