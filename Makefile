CC = g++

run: compilator.exe run.exe
	compilator.exe
	run.exe

compilator.exe: Compilator.cpp Proccessor.h Assembler.h
	$(CC) Compilator.cpp -o compilator

run.exe: Run.cpp Proccessor.h Assembler.h
	$(CC) Run.cpp -o run


