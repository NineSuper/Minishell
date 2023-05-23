INC=/usr/include
INCLIB=$(INC)/../lib

NAME = minishell
SRC = main.c
OBJ = $(SRC:.c=.o)
CC = gcc

LFLAGS = -lreadline
FLAGS = -Wall -Werror -Wextra

# ------------------------------ Colors ------------------------------

BOLD_PURPLE     =       \033[1;35m

BOLD_CYAN       =       \033[1;36m

BOLD_YELLOW     =       \033[1;33m

NO_COLOR        =       \033[0m

# ------------------------------ Messages ------------------------------

HEADER_NAME		=		$(HEADER_TOP) $(HEADER_TOP_MID) $(HEADER_MID)$(HEADER_BOT)

HEADER_COMP     =       echo "\n🌐 $(BOLD_YELLOW)Minishell $(NO_COLOR)by ltressen & jcasades & alsaez & tde-los-\n"

COMP_START      =       echo "\n🚧 $(BOLD_YELLOW)Make: $(NO_COLOR)Debut de compilation...\n"

EXE_READY       =       echo "\n📟 Compilation de $(BOLD_YELLOW)MINISHELL$(NO_COLOR) reussi !\n"

CLEANED         =       echo "\n💧 $(BOLD_YELLOW)Clean: $(NO_COLOR)Suppression des fichiers .o et de l'executable \n"

FCLEANED        =       echo "\n🧼 $(BOLD_YELLOW)Fclean: $(NO_COLOR)Suppression des fichiers .o et de l'executable \n"

NORM			= 		echo "\n📢 $(BOLD_CYAN)NORMINETTE: $(BOLD_YELLOW)Verification de la norme de tous les fichiers en .c !\n$(BOLD_PURPLE)"

NORM_H			=		echo "\n📣 $(BOLD_CYAN)NORMINETTE: $(BOLD_YELLOW)Verification de la norme du .h\n$(BOLD_PURPLE)"

# ------------------------------ Rules ------------------------------
MAKEFLAGS += --silent

$(NAME): comp_start $(OBJ)
	@$(CC)  $(OBJ) $(LFLAGS) -o $(NAME)
	@$(EXE_READY)

all: $(NAME) norminette

norminette:
	$(NORM)
	norminette *.c
	$(NORM_H)
	norminette -R checkDefine minishell.h
	echo "\n"

comp_start:
	@$(HEADER_COMP)
	@$(COMP_START)

clean:
	$(CLEANED)
	rm -f $(NAME) $(OBJ) *~ core *.core

fclean: 
	rm -f $(NAME) $(OBJ) *~ core *.core
	$(FCLEANED)

re: clean all
