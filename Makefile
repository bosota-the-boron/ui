CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lncurses

TARGET = panel
SRCS = main.c ui.c processor.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
