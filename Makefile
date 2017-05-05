# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbenning <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/29 12:30:47 by sbenning          #+#    #+#              #
#*   Updated: 2017/05/04 23:10:01 by                  ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME =			test_mlx_math

SRC =			main.c\
				get_next_line.c\
				setup.c\
				mlx_hook.c\
				lexem_handler.c\
				key.c\
				refresh.c\
				select.c

SRC_DIR =		srcs/

OBJ_DIR =		obj/

OBJ =			$(SRC:.c=.o)

COR_SRC =		$(addprefix $(SRC_DIR), %.c)

COR_OBJ =		$(addprefix $(OBJ_DIR), %.o)

ABS_OBJ =		$(addprefix $(OBJ_DIR), $(OBJ))

HEADER =		includes

ABS_DEPEND =	$(addprefix $(HEADER)/, $(DEPEND))

CC =			gcc

FLAG =			-Wall -Wextra -Werror

all : $(NAME)

$(NAME) :  $(ABS_OBJ)
	$(CC) $(FLAG) -o $@ $^ -Llibftmath -lftmath -Llibft -lft -Lmlx -lmlx -lm -lXext -lX11

$(COR_OBJ) : $(COR_SRC) $(ABS_DEPEND)
	@mkdir -p obj
	$(CC) $(FLAG) -o $@ -c $< -I$(HEADER) -Ilibftmath/include -Ilibft/includes -Imlx

clean :
	rm -rf $(OBJ_DIR)
	rm -f $(ABS_OBJ)

fclean :
	rm -f $(NAME)

re : fclean all
