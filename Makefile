TARGET = main
CC = gcc

# Utilisation correcte de pkg-config avec SDL2 (avec backticks ou $())
CFLAGS = -Wall -Wextra -std=c11 $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)

SRC = main.c Interface.c DeplacementDuRobot.c Calcul_Score.c SDL2_pour_affichage.c Fichier_commande.c deplacement_elargie.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

run: all
	./$(TARGET)

