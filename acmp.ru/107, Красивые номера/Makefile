all: build run

ifeq ($(SHELL),"/bin/sh")

build:
	g++ -o problem problem.cpp

run:
	./problem

else

build:
	call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat" x86 \
	&& cl /EHsc problem.cpp

run:
	problem

endif
