all: build run

target = problem

ifeq ($(SHELL),/bin/sh)

build:
	g++ -o $(target) $(target).cpp

run:
	./$(target)

else

build:
	call "%VS100COMNTOOLS%..\..\vc\vcvarsall.bat" x86 \
	&& cl /EHsc $(target).cpp

run:
	$(target)

endif
	