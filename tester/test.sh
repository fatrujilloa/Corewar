#!/bin/bash

program=../asm
map_good=0
map_total=0
go=0

echo "\033[0;33mBienvenue dans le checker - auteur : gmoindro && ftrujill && rbeaufre && auguyon\033[0m\n"

if [ -d "42" ];then
	echo "Next time, let the program run until the end or put some champions in it\n"
else
	mkdir 42 our
fi

for rep in $*
do
	go=$((1))
	echo
	l=$((${#rep} - 2))
	map_valid=${rep:0:$l}
	map_total=$(($map_total + 1))
	b=$(42binaire/./asm $map_valid.s)
	if [ "$b" == "Writing output program to $map_valid.cor" ]; then
		mv $map_valid.cor 42
		a=$($program $map_valid.s)
		if [ "$a" != "Writing output program to $map_valid.cor" ]; then
			echo "\033[0;31m\t[KO] $map_valid.s\t\t#problem on your map_checker\033[0m"
		else
			mv $map_valid.cor our
			echo $map_valid > b
			x=`awk -F / '{print $NF}' b`
			rm b
			resultat=$(cmp 42/$x.cor our/$x.cor)
			if [ -z "$resultat" ]; then
				echo "\033[0;32m\t[OK] $map_valid.s \033[0m"
				map_good=$(($map_good + 1))
			else
				cmp 42/$x.cor our/$x.cor
				echo "\033[0;31m\t[KO] $map_valid.s\t\t#problem inside the .cor\033[0m"
			fi
		fi
	else
		a=$($program $map_valid.s 2>/dev/null)
		if [ "$a" != "Writing output program to $map_valid.cor" ]; then
			echo "\033[0;32m\t[OK] $map_valid.s \033[0m"
			map_good=$(($map_good + 1))
		else
			echo "\033[0;31m\t[KO] $map_valid.s      #you write the .cor even if it's a wrong map\033[0m"
			rm $map_valid.cor
		fi
	fi
done

if [ $go != 0 ]; then
	rm -r 42 our
	echo "\n\033[0;35mResult : [$map_good / $map_total] \033[0m"
else
	echo "Write in test.sh the path to your asm\nusage: sh test.sh [file ...]"
fi
