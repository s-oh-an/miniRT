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

echo -en $YELLOW
echo "===========================NORM============================="
read ;
echo -en $PURPLE
echo "INCLUDES"
echo -en $RESTORE
cd includes/
norminette
read;
echo -en $PURPLE
echo "SOURCES"
echo -en $RESTORE
cd ../src
norminette
cd ..
echo -en $YELLOW
echo "=========================MAKEFILE==========================="
echo -en $GREEN
echo "make re"
echo -en $RESTORE
read;
make re
echo -e $GREEN
echo "check relink"
echo -en $RESTORE
read;
make
echo -e $GREEN
echo "make clean"
echo -en $RESTORE
read;
make clean
echo -e $GREEN
echo "make fclean"
echo -en $RESTORE
read;
make fclean
echo -e $GREEN
echo "make all"
echo -en $RESTORE
read;
make all
