all:

target = problem

ifeq ($(SHELL),/bin/sh)

run:
	./$(target)

do-build:
	g++ -O2 $(defs) -l stdc++ -o $(target) $(target).cpp

clean:
	git clean -d -f

endif

build:
	$(MAKE) do-build defs=-DTESTING_

build-target: do-build

