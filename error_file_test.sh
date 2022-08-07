#!/bin/zsh
RESTORE='\033[0m'

RED='\033[00;31m'
GREEN='\033[00;32m'
YELLOW='\033[00;33m'
BLUE='\033[00;34m'
PURPLE='\033[00;35m'
CYAN='\033[00;36m'
GRAY='\033[00;30m'
LIGHTGRAY='\033[01;30m'

LRED='\033[01;31m'
LGREEN='\033[01;32m'
LYELLOW='\033[01;33m'
LBLUE='\033[01;34m'
LPURPLE='\033[01;35m'
LCYAN='\033[01;36m'
WHITE='\033[01;37m'

clear
chmod -r scene/error/not_readable.rt
search_dir=scene/error
for entry in "$search_dir"/*
do
	echo -en $GRAY
	echo "============================================================"
	echo -n "> ./miniRT "
	echo -en $LRED
	echo -n $entry | cut -d'/' -f3-
	echo -e $RESTORE
	./miniRT $entry
	echo ""
	echo -en $LPURPLE
	cat $entry
	echo -en $RESTORE
	echo ""
	echo ""
done
chmod +r scene/error/not_readable.rt
