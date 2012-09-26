all: build run

target = problem

ifeq ($(SHELL),/bin/sh)

run:
	./$(target)

do-build:
	g++ -O2 $(defs) -l stdc++ -o $(target) $(target).cpp

clean:
	git clean -d -f
else

run:
	$(target).exe

do-build:
	call "%VS100COMNTOOLS%\vsvars32.bat" && \
	cl /EHsc $(defs) /Fe$(target).exe $(target).cpp

files_to_delete = \
 *.user *.exe *.obj *.ncb *.pdb *.ilk *.suo *.lst \
 *.xml *.filters *.sdf *.lastcodeanalysissucceeded

folders_to_delete = debug ipch _UpgradeReport_Files

clean:
	-cmd /c del /a:h /a:- $(files_to_delete)
	-cmd /c rmdir /q /s $(folders_to_delete)

endif

build:
	$(MAKE) do-build defs=-DTESTING_

build-target: do-build
