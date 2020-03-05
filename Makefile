
NAME = scop
CC = gcc

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./
INC_PATH = ./include/ $(LIB_PATH)libft/ $(LIB_PATH)glfw/include/

GCC_FLGS = -Werror -Wextra -Wall -pedantic -g3
GCC_LIBS = -lglfw3 -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo

SRC_NAME = main.c callback.c shader.c buffer.c utils.c \
		   coordinate_system.c movement.c camera.c parsing.c texture.c errors.c init_gl.c matrix_gen.c \
		   vectors.c matrix_mult.c matrix_utils.c init_manager.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft glfw/src

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L$(LIB_PATH),$(LIB_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)libft -j
	$(CC) $(GCC_FLGS) $(LIB) -lft $(INC) $(OBJ) $(GCC_LIBS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(GCC_FLGS) $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIB_PATH)libft fclean
	rm -fv $(NAME)

re: fclean all
