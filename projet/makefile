CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
INCDIR	= inc/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers TD 04
GLOB_OBJ_TD= $(OBJDIR)3D_tools.o

# Fichiers exercice 01
OBJ_PROJET= $(GLOB_OBJ_TD) $(OBJDIR)draw_scene.o  $(OBJDIR)corridor.o $(OBJDIR)main.o
EXEC_PROJET= projet.out

# Regles compilation TD 04

all : projet

projet : $(OBJ_PROJET)
	$(CC) $(CFLAGS) $(OBJ_PROJET) -o $(BINDIR)$(EXEC_PROJET) $(LDFLAGS)

clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCDIR)*.h
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(INCDIR) -c $< $(CFLAGS)
