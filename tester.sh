i=0
if [ "$#" -le 1 ]
then
    while [ $i -lt $1 ]
    do
        ./corewar -dump $i test.cor test.cor | tail -64 > a && ./corewar_r -d $i test.cor test.cor | tail -n +4 | cut -c 10- > b && diff a b
        echo "$i-th cycle"
        i=$(( $i + 1 ))
    done
else
        ./corewar -dump $2 $3 $4 | tail -64 > a && ./corewar_r -d $2 $3 $4 | tail -n +4 | cut -c 10- > b && diff a b
        echo "$2-th cycle"
fi