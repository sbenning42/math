# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbenning <sbenning@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/09/08 20:00:17 by sbenning          #+#    #+#              #
#*   Updated: 2017/05/02 05:34:30 by                  ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME =	libftmath.a

SRC =	m_color.c\
		m_vertex.c\
		m_vector.c

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

all : $(NAME) include/ft_math.h

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
