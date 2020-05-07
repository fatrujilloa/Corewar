# Corewar

corewar_r = VM du sujet

Notre VM affiche les mêmes choses que corewar_r avec l'option -v 7 (modulo un dernier "It is now cycle xxxxx")

test_simple.sh = script pour comparer notre VM avec celle du sujet. Exemple: sh test_simple.sh champs/Gagnant.cor champs/jumper.cor

dump_test.sh = script pour comparer le dump des deux VM's. Exemple sh dump_test.sh 10000 champs/Gagnant.cor champs/Gagnant.cor champs/jumper.cor

Je ne suis pas sur si le format d'affichage de la memoire pour l'option -dump est le bon format...