#!/bin/bash

program=../dasm
map_good=0
map_total=0
go=0

echo "\033[0;33mBienvenue dans le checker leaks - auteur : gmoindro && ftrujill && rbeaufre && auguyon\033[0m\n"

if [ -d "trace_val" ];then
	rm -rf trace_val/*
else
	mkdir trace_val
fi

for rep in $*
do
	go=$((1))
	echo
	l=$((${#rep} - 4))
	map_valid=${rep:0:$l}
	map_total=$(($map_total + 1))
	b=$(valgrind $program $map_valid.cor 2>trace_val/$map_total)
	grep "definitely lost:" trace_val/$map_total 1>trace_val/.$map_total.txt
	cut -d = -f 5 trace_val/.$map_total.txt 1>trace_val/.$map_total.t
	rm trace_val/.$map_total.txt 2>/dev/null
	a=$(cut -d ' ' -f 7 trace_val/.$map_total.t)
	c=$(cut -d ' ' -f 10 trace_val/.$map_total.t)
	rm trace_val/.$map_total.t 2>/dev/null
	if [[ "$a" == "0" && "$c" == "0" ]]; then
		echo "\033[0;32m\t[OK] $map_total : $map_valid.s \033[0m"
		map_good=$(($map_good + 1))
	else
		echo "\033[0;31m\t[KO] $map_total : $map_valid.s \033[0m"
	fi
done

rm maps_dasm/*_dasm.s
if [ $go != 0 ]; then
	echo "\n\033[0;35mResult : [$map_good / $map_total] \033[0m"
else
	echo "Write in test.sh the path to your asm\nusage: sh test.sh [file ...]"
fi
