all: build run

target = Main

build:
	javac $(target).java

run:
	java $(target)

run-test:
	java $(target) test

clean:
	-rm *.class
	-rm -rf out/
