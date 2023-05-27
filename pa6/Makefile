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

all: ListTest Arithmetic BigIntegerTest

ListTest: ListTest.o List.o
    $(CC) -o $@ $^

BigIntegerTest: BigIntegerTest.o BigInteger.o List.o
    $(CC) -o $@ $^

Arithmetic: Arithmetic.o BigInteger.o List.o
    $(CC) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c $<

clean:
    rm -f ListTest Arithmetic BigIntegerTest List *.o

cleanText:
    rm -f *.txt

cleandir:
    rm -r backup

checkMath:
    valgrind --leak-check=full ./Arithmetic in out

checkInteger:
    valgrind --leak-check=full ./BigIntegerTest

checkList:
    valgrind --leak-check=full ./ListTest