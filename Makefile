CC := gcc

CFLAGS := -lSDL -lSDL_image -lSDL_ttf -w -Wall -Wextra -Werror

HDRS :=

SRCS :=	main.c		\
		game.c		\
		bomb.c		\
		character.c	\
		map.c		\
		menu.c

OBJS := $(SRCS:.c=.o)

EXEC := bomberman

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean