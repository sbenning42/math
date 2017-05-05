# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbenning <sbenning@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/09/08 20:00:17 by sbenning          #+#    #+#              #
#*   Updated: 2017/05/04 17:06:45 by                  ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME =	libftmath.a

SRC =	m_color.c\
		m_vertex.c\
		m_triangle.c\
		m_mesh.c\
		m_vector.c\
		m_matrix.c\
		m_camera.c\
		m_preset.c\
		m_render.c

OBJ =	$(SRC:.c=.o)

SRC_DIR	= src/

OBJ_DIR	= obj/

SRC_ =	$(addprefix $(SRC_DIR), %.c)

OBJ_ =	$(addprefix $(OBJ_DIR), %.o)
OBJ_L =	$(addprefix $(OBJ_DIR), $(OBJ))

HEADERS =	include

LIBHPATH = libhdir

CC =		gcc

FLAGS =		-Wall -Wextra -Werror 

all : $(NAME)

$(NAME) : $(OBJ_L)
	ar cr $@ $^
	ranlib $@

$(OBJ_) : $(SRC_)
	$(CC) $(FLAGS) -o $@ -c $< -I $(HEADERS) -I $(LIBHPATH)

clean:
	rm -f $(OBJ_L)

fclean: clean
	rm -f $(NAME)

re: fclean all
