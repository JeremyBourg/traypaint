CC=gcc
INCLUDES=
LDFLAGS=-lraylib -lm
WARNINGS=-Wall

CFLAGS=$(INCLUDES) $(LDFLAGS) $(WARNINGS)

TARGET=traypaint
SOURCES=traypaint.c

$(TARGET): $(SOURCES)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(TARGET)
