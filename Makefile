TARGET = main
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c Interface.c DeplacementDuRobot.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

run: all
	./$(TARGET)

