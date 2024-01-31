NAME = pipex
LIBFT = libft
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -rf
HEAD = ./include/

SRC_DIR = src/
OBJ_DIR = obj/
SRC_FILES = pipex pipex_utils
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

BONUS_SRC_DIR = src_bonus/
BONUS_SRC_FILES = pipex_bonus pipex_utils_bonus
BONUS_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BONUS_SRC_FILES)))
BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(addsuffix .c, $(BONUS_SRC_FILES)))

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./Libft -lft

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

$(LIBFT)	: $(OBJ)
	@echo "Compiling Libft"
	@make -C $(LIBFT)

bonus : $(LIBFT) $(BONUS_OBJ)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME) -L./Libft -lft

$(OBJ_DIR)%.o : $(BONUS_SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling bonus: $<"
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

clean :
	$(RM) $(OBJ_DIR)
	$(RM) $(LIBFT)/$(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)
	$(RM) libft/libft.a

re : fclean all