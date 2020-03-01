
NAME = scop
CC = gcc

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./
INC_PATH = ./include/ $(LIB_PATH)libft/ $(LIB_PATH)glfw/include/ \
			$(LIB_PATH)libmat4/include/

GCC_FLGS = -Werror -Wextra -Wall -pedantic -g3
GCC_LIBS = -lglfw3 -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo

SRC_NAME = main.c callback.c shader.c buffer.c utils.c \
		   coordinate_system.c movement.c camera.c parsing.c texture.c errors.c init_gl.c matrix.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft libmat4 glfw/src

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L$(LIB_PATH),$(LIB_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)libft -j
	make -C $(LIB_PATH)libmat4 -j
	$(CC) $(GCC_FLGS) $(LIB) -lft -lmat4 $(INC) $(OBJ) $(GCC_LIBS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(GCC_FLGS) $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIB_PATH)libft fclean
	make -C $(LIB_PATH)libmat4 fclean
	rm -fv $(NAME)

re: fclean all
