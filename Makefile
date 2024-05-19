particle_simulator: main.o simulator.o update_functions.o
	gcc -o particle_simulator main.o simulator.o update_functions.o -lraylib -lm -g

main.o: main.c
	gcc main.c -c -g

simulator.o: simulator.c
	gcc simulator.c -c -g

update_functions.o: update_functions.c
	gcc update_functions.c -c -g

