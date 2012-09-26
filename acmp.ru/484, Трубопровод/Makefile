all: build run

ifeq ($(SHELL),/bin/sh)
python = python
else
python = c:/python26/python
endif

py:
	$(python) problem.py

build:
ifeq ($(SHELL),/bin/sh)
	g++ -o problem problem.cpp
else
	cl2010.cmd && cl /EHsc problem.cpp
endif

run:
	./problem

