ARGS ?= -g -pg

particle_simulator: main.o simulator.o update_functions.o drawing.o
	gcc -o particle_simulator main.o simulator.o update_functions.o drawing.o -lraylib -lm $(ARGS)

main.o: main.c
	gcc main.c -c $(ARGS)

simulator.o: simulator.c
	gcc simulator.c -c $(ARGS)

update_functions.o: update_functions.c particles/*
	gcc update_functions.c -c $(ARGS)
	
drawing.o: drawing.c
	gcc drawing.c -c $(ARGS)
