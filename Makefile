#
# Makefile for CS 2620 Assignment 2
#
# Author: Howard Cheng
# Oct 10, 2007
#

# some settings
CXX=/opt/centos/devtoolset-1.1/root/usr/bin/g++
CXXFLAGS=-Wall -g -std=c++11

all: stringTest

stringTest: stringTest.o myString.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# default rule for compiling .o
%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $<

stringTest.o: stringTest.cc myString.h
myString.o: myString.cc myString.h

clean:
	rm -rf *.o *~

clean-all: clean
	rm -rf stringTest
