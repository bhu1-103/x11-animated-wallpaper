CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11
LDFLAGS = -lX11 -lGL

SRC = src/main.c
OUT = build/wallpaper

.PHONY: all clean

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
