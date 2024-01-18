NAME = pipex

LIBNAME = pipex.a

LIBFT = libft

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MINIFLAGS = -lmlx -framework OpenGL -framework AppKit

AR = ar -rcs

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC_FILES = pipex pipex_utils

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

HEAD = ./include/

all : $(NAME)

$(NAME) : $(LIBNAME)
	$(CC) $(CFLAGS) $(MINIFLAGS) $(LIBNAME) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

$(LIBNAME)	: $(OBJ)
	@make -C $(LIBFT)
	@cp libft/libft.a .
	@rm libft/libft.a
	@mv libft.a $(LIBNAME)
	@$(AR) $(LIBNAME) $(OBJ)
	@echo "so_long compiled!"

clean :
	$(RM) $(OBJ_DIR)
	$(RM) $(LIBFT)/$(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(LIBNAME)

re : fclean all