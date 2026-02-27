CC = gcc
CFLAGS = -02 -Wall -Wextra -std=c11
LDFLLAGS = -lX11 -lGL

SRC = src/main.c
OUT = wallpaper

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
