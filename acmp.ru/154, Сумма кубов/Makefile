all: build run

build:
	call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat" x86 \
	&& cl /O2 /EHsc problem.cpp

run:
	problem	test
