#NAME
NAME = philo

# SOURCE FILES
SRC_DIR		=	src/

SRC_FILES	=	philo.c \

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

#OBJECT FILES
OBJ_DIR		= objs/
OBJ_FILES 	= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#COMPILER
CC		= cc
FLAGS	= -Wall -Wextra -Werror -g3 #-fsanitize=address
INCLUDE	= -I includes
RM		= rm -rf
LIBFT	= libft/libft.a

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

#MAKEFILE RULES
all: $(NAME)

$(NAME) : $(OBJ_FILES)
	@make -sC libft
	@echo "$(GREEN)\nCompiling the philo program.$(CLEAR)"
	@$(CC) $(FLAGS) $(OBJ_FILES) $(INCLUDE) -o $(NAME)
	@echo "$(GREEN)	      [OK]\n$(CLEAR)$(GREEN)      	    Success!$(CLEAR)\n"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	@echo "$(RED)\nRemoving compiled files.$(CLEAR)"
	@$(RM) $(OBJ_DIR)
	@make clean -sC libft
	@echo "$(RED)	[OK]\n$(CLEAR)$(RED)      Success!$(CLEAR)\n"
	@echo "$(RED)Object files removed correctly\n$(CLEAR)"

fclean: 
	@make clean >/dev/null 2>&1
	@echo "$(RED)\nRemoving exec. files.$(CLEAR)"
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo "$(RED)	[OK]\n$(CLEAR)$(RED)      Success!$(CLEAR)\n"
	@echo "$(RED)Everything removed correctly\n$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re
