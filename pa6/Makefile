#// ========== Name ========== //
#// Manikantanagasai H. Illuri //
#// milluri@ucsc.edu           //
#// 2023 Spring CSE101         //
#// PA: 6                      //
#// Makefile			       //
#// ========================== //

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                     makes Arithmetic
#  make BigIntegerClient    makes BigIntegerClient
#  make ListClient          makes ListClient
#  make clean               removes all binaries
#  make ArithmeticCheck     runs Arithmetic in valgrind on in4 junk4
#  make BigIntegerCheck     runs BigIntegerTest in valgrind
#  make ListCheck           runs ListTest in valgrind
#------------------------------------------------------------------------------
CC = g++
CFLAGS = -std=c++17 -Wall

all: ListTest Shuffle

Shuffle: Shuffle.o List.o
    $(CC) -o $@ $^

ListTest: ListTest.o List.o
    $(CC) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c $<

clean:
    rm -f ListTest Shuffle List *.o

cleanText:
    rm -f *.txt

cleandir:
    rm -r backup

checkShuffle:
    valgrind --leak-check=full ./Shuffle 50

checkTest:
    valgrind --leak-check=full ./ListTest