NAME = pipex

LIBNAME = pipex.a

LIBFT = libft

CC = gcc

CFLAGS = -Wall -Wextra -Werror

AR = ar -rcs

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC_FILES = pipex pipex_utils

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

BONUS_SRC_DIR = src_bonus/

BONUS_SRC_FILES = pipex_bonus pipex_utils_bonus

BONUS_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BONUS_SRC_FILES)))

BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(addsuffix .c, $(BONUS_SRC_FILES)))

HEAD = ./include/

all : $(NAME)

$(NAME) : $(LIBNAME)
	$(CC) $(CFLAGS) $(LIBNAME) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

$(LIBNAME)	: $(OBJ)
	@make -C $(LIBFT)
	@cp libft/libft.a .
	@rm libft/libft.a
	@mv libft.a $(LIBNAME)
	$(AR) $(LIBNAME) $(OBJ)
	@echo "pipex compiled!"

bonus : $(BONUS_OBJ)
	@make -C $(LIBFT)
	@cp libft/libft.a .
	@rm libft/libft.a
	@mv libft.a $(LIBNAME)
	@$(AR) $(LIBNAME) $(BONUS_OBJ)
	@echo "pipex compiled!"
	$(CC) $(CFLAGS) $(LIBNAME) -o $(NAME)

$(OBJ_DIR)%.o : $(BONUS_SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling bonus: $<"
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

clean :
	$(RM) $(OBJ_DIR)
	$(RM) $(LIBFT)/$(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(LIBNAME)

re : fclean all