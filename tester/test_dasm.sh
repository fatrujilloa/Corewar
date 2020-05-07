#!/bin/bash

program=../dasm
program2=../asm
map_good=0
map_total=0
go=0

echo "\033[0;33mBienvenue dans le checker leaks - auteur : gmoindro && ftrujill && rbeaufre && auguyon\033[0m\n"

for rep in $*
do
	go=$((1))
	echo
	l=$((${#rep} - 4))
	map_valid=${rep:0:$l}
	autre="_dasm"
	map_valid_2="$map_valid$autre"
	map_total=$(($map_total + 1))
	$program $map_valid.cor 1>/dev/null 2>/dev/null
	$program2 $map_valid_2.s 1>/dev/null 2>/dev/null
	resultat=$(cmp $map_valid_2.cor $map_valid.cor) 2>/dev/null
	if [ -z "$resultat" ]; then
		echo "\033[0;32m\t[OK] $map_valid.cor \033[0m"
		map_good=$(($map_good + 1))
	else
		echo "\033[0;31m\t[KO] $map_valid.cor \033[0m"
	fi
done

rm maps_dasm/*_dasm.s 2>/dev/null
rm maps_dasm/*_dasm.cor 2>/dev/null

if [ $go != 0 ]; then
	echo "\n\033[0;35mResult : [$map_good / $map_total] \033[0m"
else
	echo "Write in test.sh the path to your asm\nusage: sh test.sh [file ...]"
fi
