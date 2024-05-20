particle_simulator: main.o simulator.o update_functions.o
	gcc -o particle_simulator main.o simulator.o update_functions.o -lraylib -lm -g -pg

main.o: main.c
	gcc main.c -c -g -pg

simulator.o: simulator.c
	gcc simulator.c -c -g -pg

update_functions.o: update_functions.c particles/*
	gcc update_functions.c -c -g -pg

