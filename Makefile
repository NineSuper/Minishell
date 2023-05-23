INC=/usr/include
INCLIB=$(INC)/../lib

NAME = philo
SRC = main.c error.c header.c ft_utils.c init_philo.c ft_usleep.c ft_routine.c
OBJ = $(SRC:.c=.o)
CC = gcc

FLAGS = -Wall -Werror -Wextra

# ------------------------------ Colors ------------------------------

BOLD_PURPLE     =       \033[1;35m

BOLD_CYAN       =       \033[1;36m

BOLD_YELLOW     =       \033[1;33m

NO_COLOR        =       \033[0m

# ------------------------------ Messages ------------------------------

HEADER_TOP		=		echo "$(BOLD_YELLOW)  ____  ____  ____      __     __   ____     \n"

HEADER_TOP_MID  =		"$(BOLD_CYAN)(_  _)(    \(  __)___ (  )   /  \ / ___) ___ \n"

HEADER_MID		=		"$(BOLD_PURPLE)  )(   ) D ( ) _)(___)/ (_/\(  O )\___ \(___)\n"

HEADER_BOT		=		"$(NO_COLOR)  (__) (____/(____)    \____/ \__/ (____/    \n"

HEADER_NAME		=		$(HEADER_TOP) $(HEADER_TOP_MID) $(HEADER_MID)$(HEADER_BOT)

HEADER_COMP     =       echo "\n🌐 $(BOLD_YELLOW)Philosophers $(NO_COLOR)by tde-los-\n"

COMP_START      =       echo "\n🚧 $(BOLD_YELLOW)Make: $(NO_COLOR)Debut de compilation...\n"

EXE_READY       =       echo "\n📟 Compilation de $(BOLD_YELLOW)PHILOSOPHERS$(NO_COLOR) reussi !\n"

CLEANED         =       echo "\n💧 $(BOLD_YELLOW)Clean: $(NO_COLOR)Suppression des fichiers .o et de l'executable \n"

FCLEANED        =       echo "\n🧼 $(BOLD_YELLOW)Fclean: $(NO_COLOR)Suppression des fichiers .o et de l'executable \n"

NORM			= 		echo "\n📢 $(BOLD_CYAN)NORMINETTE: $(BOLD_YELLOW)Verification de la norme de tous les fichiers en .c !\n$(BOLD_PURPLE)"

NORM_H			=		echo "\n📣 $(BOLD_CYAN)NORMINETTE: $(BOLD_YELLOW)Verification de la norme du .h\n$(BOLD_PURPLE)"

# ------------------------------ Rules ------------------------------
MAKEFLAGS += --silent

$(NAME): comp_start $(OBJ)
	@$(CC) -pthread $(OBJ) -o $(NAME)
	@$(EXE_READY)

all: $(NAME) norminette

norminette:
	$(NORM)
	norminette *.c
	$(NORM_H)
	norminette -R CheckDefine philo.h
	echo "\n"

comp_start:
	@$(HEADER_NAME)
	@$(HEADER_COMP)
	@$(COMP_START)

clean:
	$(CLEANED)
	rm -f $(NAME) $(OBJ) *~ core *.core

fclean: 
	rm -f $(NAME) $(OBJ) *~ core *.core
	$(FCLEANED)

re: clean all
