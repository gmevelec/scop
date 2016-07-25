# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/10 13:48:10 by gmevelec          #+#    #+#              #
#    Updated: 2016/03/17 13:08:46 by gmevelec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

SRCDIR = src
LIB_FOLD = libft/
LIB_PRINT = /nfs/2013/g/gmevelec/perso/libs/libprint
LIB_IMG = /nfs/2013/g/gmevelec/perso/libs/libloadimage
LIB_MLX = /nfs/2013/g/gmevelec/lib/mlx
LIB_PNG = /nfs/2013/g/gmevelec/lib
LIBDIR = obj/
HEADDIR = inc
CFLAGS = -Wall -Wextra -I$(HEADDIR) -I$(HOME)/include -O3
LIB = -L$(HOME)/lib -lglfw3 -L$(LIB_MLX) -lmlx\
	  -framework OpenGL -framework AppKit -framework IOKit -framework CoreVideo \
	  -framework Carbon -L$(LIB_FOLD) -lft -L$(LIB_PRINT) -lprint \
	  -L$(LIB_IMG) -lloadimage -L$(LIB_PNG) -lpng


SRC = $(SRCDIR)/main.c \
	$(SRCDIR)/loader.c \
	$(SRCDIR)/renderer.c \
	$(SRCDIR)/shader.c \
	$(SRCDIR)/get_shaders.c \
	$(SRCDIR)/maths.c \
	$(SRCDIR)/matrix.c \
	$(SRCDIR)/load_matrix.c \
	$(SRCDIR)/entity.c \
	$(SRCDIR)/camera.c \
	$(SRCDIR)/parser.c \
	$(SRCDIR)/parser_obj.c \
	$(SRCDIR)/init_env.c \
	$(SRCDIR)/init_glfw.c \
	$(SRCDIR)/init_model.c \

TSRC=$(subst src/,../src/,$(SRC))

TMP=$(subst src/,obj/,$(SRC))

OBJ = $(TMP:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIB_FOLD)
		make -C $(LIB_PRINT)
		make -C $(LIB_IMG)
		clang -o $(NAME) $(OBJ) $(CFLAGS) $(LIB)
		@echo "Creating $(NAME)"

$(OBJ) : $(SRC)
		@mkdir -p $(LIBDIR)
		(cd obj;clang $(CFLAGS) -c $(TSRC))
		@echo "Creating .o"

clean:
		@rm -f $(OBJ)
		@echo "Suppressing all .o"

fclean: clean
		@rm -f $(NAME)
		@echo "Suppressing $(NAME)"
		make -C $(LIB_FOLD) fclean
		make -C $(LIB_PRINT) fclean
		make -C $(LIB_IMG) fclean
		make -C $(LIB_MLX) clean

re: fclean all

.PHONY: all clean fclean re
