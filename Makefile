NAME = pipex
BONUS_NAME = pipex_bonus

LIBFT = ./libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MINIFLAGS = -lmlx -framework OpenGL -framework AppKit

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/
BONUS_SRC_DIR = src_bonus/
BONUS_OBJ_DIR = obj_bonus/

SRC_FILES = pipex pipex_utils
BONUS_SRC_FILES = pipex pipex_utils

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(addsuffix _bonus.o, $(BONUS_SRC_FILES)))
BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(addsuffix _bonus.c, $(BONUS_SRC_FILES)))

HEAD = ./include/

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[0;33m\nCOMPILING PIPEX...\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[1;32m./pipex created\n"

$(BONUS_NAME) : $(BONUS_OBJ) $(LIBFT)
	@echo "\033[0;33m\nCOMPILING PIPEX_BONUS...\n"
	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_NAME)
	@echo "\033[1;32m./pipex_bonus created\n"

$(LIBFT)	:
	@echo "\033[0;33m\nCOMPILING LIBFT\n"
	@make -C ./libft
	@echo "\033[1;32mLIBFT created\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

$(BONUS_OBJ_DIR)%.o : $(BONUS_SRC_DIR)%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

bonus : $(BONUS_NAME)

clean :
	$(RM) ./libft/$(OBJ_DIR)
	$(RM) $(OBJ_DIR) $(BONUS_OBJ_DIR)

fclean : clean
	$(RM) ./libft/libft.a
	$(RM) $(NAME) $(BONUS_NAME)

re : fclean all