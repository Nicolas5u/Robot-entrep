TARGET = main
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c Interface.c DeplacementDuRobot.c Calcul_Score.c SDL2_pour_affichage.c
OBJ = $(SRC:.c=.o)
LIBS = -lSDL2

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

run: all
	./$(TARGET)

