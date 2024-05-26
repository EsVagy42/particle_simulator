# Platform and Build type configuration
PLATFORM ?= PLATFORM_DESKTOP
BUILD ?= DEBUG

# Default compiler to use if not specified
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
	override CC = gcc
	OUTPUT = $(OUTDIR)/parsim
else ifeq ($(PLATFORM),PLATFORM_WEB)
	override CC = emcc
	OUTPUT = $(OUTDIR)/index.html
endif

# Compiler flags
ifeq ($(BUILD),DEBUG)
	CFLAGS ?= -g -pg
else ifeq ($(BUILD),RELEASE)
	CFLAGS ?= -O3
endif

# Linker flags, -lraylib for the raylib graphics library, -lm for the math library
LDFLAGS ?= -lraylib -lm

# Additional flags for emcc
ifeq ($(PLATFORM),PLATFORM_WEB)
	override LDFLAGS = -s USE_GLFW=3 --shell-file minshell.html -L/usr/local/lib -lraylibweb -lm
	CFLAGS += -I/usr/local/include -DPLATFORMWEB 
endif

# Output directory for compiled files
OUTDIR=out

# Collect all .c source files from the current directory and the /particles directory
SOURCES=$(wildcard *.c) $(wildcard particles/*.c)

# Transform the list of source files into a list of object files
OBJECTS=$(patsubst %.c,$(OUTDIR)/%.o,$(SOURCES))

# The default target: build the executable
all: $(OUTPUT)

# Link the object files into the executable
$(OUTPUT): $(OBJECTS)
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
	rm -rf $(OUTDIR)/*.o $(OUTDIR)/parsim $(OUTDIR)/index.html $(OUTDIR)/index.js $(OUTDIR)/index.wasm $(OUTDIR)/particles/*.o
