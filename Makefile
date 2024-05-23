# Default compiler to use if not specified
CC ?= gcc

# Compiler flags, -g for debugging, -pg for profiling
CFLAGS ?= -g -pg

# Linker flags, -lraylib for the raylib graphics library, -lm for the math library
LDFLAGS ?= -lraylib -lm

# Output directory for compiled files
OUTDIR=out

# Collect all .c source files from the current directory and the /particles directory
SOURCES=$(wildcard *.c) $(wildcard particles/*.c)

# Transform the list of source files into a list of object files
OBJECTS=$(patsubst %.c,$(OUTDIR)/%.o,$(SOURCES))

# The default target: build the parsim executable
all: $(OUTDIR)/parsim

# Link the object files into the parsim executable
$(OUTDIR)/parsim: $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

# Compile each .c file into an .o object file in the OUTDIR
$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile .c files from the /particles directory into .o object files in the OUTDIR
$(OUTDIR)/%.o: particles/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the output directory exists
$(shell mkdir -p $(OUTDIR))

# Clean up the build: remove object files and the executable
clean:
	rm -rf $(OUTDIR)/*.o $(OUTDIR)/parsim
