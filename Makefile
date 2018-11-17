CC := gcc

CFLAGS := -lSDL -lSDL_image -lSDL_ttf

HDRS :=

SRCS :=	main.c		\
		game.c

OBJS := $(SRCS:.c=.o)

EXEC := bomberman

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean