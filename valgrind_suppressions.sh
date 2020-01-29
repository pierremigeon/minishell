#!/bin/zsh


#executable name
if [ $# == 1 ]; then
    NAME=$1
else
    NAME="a.out"
fi
###############################################################################
# constant variables
###############################################################################
GCC=/usr/bin/gcc
VALGRIND=/usr/local/bin/valgrind
RMF=/bin/rm
SUPFILE="sup.txt"

###############################################################################
# generating fresh suppressions file
###############################################################################

# clear
if [ -a $SUPFILE ]; then
    echo valgrind will use $SUPFILE
else
    # name of the suppressions file
    SUPTEMP="sup_temp.txt"
    # temp main.c file
    MAINTEMP="mtemp.c"
    # temp bin file
    BINTEMP="mtemp"
    # creating main file
    echo "creating main file"
    echo "int main(void) {return 0;}" > $MAINTEMP
    # compiling main file
    echo "compiling main file"
    $GCC $MAINTEMP -o $BINTEMP
    # generating suppression file
    echo "generating suppression file"
    $VALGRIND --gen-suppressions=all --leak-check=full --show-leak-kinds=all ./$BINTEMP 2>./$SUPTEMP
    # cleaning suppression file: delete all == and --
    echo "cleaning suppression file"
    cat $SUPTEMP | grep -v "==" | grep -v "\-\-" | grep -v "warning" > $SUPFILE
    # deleting all temp files
    echo "deleting all temp files"
    $RMF $SUPTEMP
    $RMF $MAINTEMP
    $RMF $BINTEMP
fi
###############################################################################

#use valgrind again, with the suppressions file
if [ -a $NAME ]; then
    $VALGRIND --suppressions=./$SUPFILE ./$NAME
else
    echo $NAME not found
fi
