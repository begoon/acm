all: build run

target = problem

build:
	call "%VS100COMNTOOLS%\..\..\VC\vcvarsall.bat" x86 && cl /EHsc $(target).cpp

run:
	$(target)

clean:
	-del *.exe *.obj OUTPUT.TXT	