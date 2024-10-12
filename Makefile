CC = g++

run: compilator.exe run.exe
	compilator.exe
	run.exe

compilator.exe: compilator.cpp Proccessor.h Assembler.h
	$(CC) compilator.cpp -o compilator

run.exe: run.cpp Proccessor.h Assembler.h
	$(CC) run.cpp -o run


