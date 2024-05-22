CC ?= gcc
CFLAGS ?= -g -pg
LDFLAGS ?= -lraylib -lm

OUTDIR=out

SOURCES=$(wildcard *.c)

OBJECTS=$(patsubst %.c,$(OUTDIR)/%.o,$(SOURCES))

all: $(OUTDIR)/parsim

$(OUTDIR)/parsim: $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(shell mkdir -p $(OUTDIR))

clean:
	rm -rf $(OUTDIR)/*.o $(OUTDIR)/parsim
