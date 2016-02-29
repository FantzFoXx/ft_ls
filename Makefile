# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: udelorme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/14 11:43:18 by udelorme          #+#    #+#              #
#    Updated: 2016/02/29 11:27:58 by udelorme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
FLAGS = -Wall -Werror -Wextra -O3 -g
NAME = ft_ls
SRC = main.c ft_ls.c					\
	  get_params.c toolkit.c			\
	  catch_errors.c t_dir_content_1.c	\
	  t_dir_content_2.c print_ls.c		\
	  sort_items.c option_l.c

OBJ = $(SRC:.c=.o)

SRCDIR = src/
OBJDIR = obj/
INCDIR = includes/
LIBDIR = libft/

all: $(NAME)

$(NAME):
	(cd $(LIBDIR); $(MAKE) all)
	(cd $(SRCDIR);$(CC) $(FLAGS) -c $(SRC) -I ../$(INCDIR) -I ../$(LIBDIR)includes/;mv $(OBJ) ../obj)
	(cd $(OBJDIR);$(CC) $(FLAGS) -o ../$(NAME) $(OBJ) -L ../$(LIBDIR) -lft)

clean:
	(cd $(OBJDIR); rm -rf $(OBJ))

fclean: clean
	rm -rf $(NAME)

re: fclean all

lftclean:
	(cd $(LIBDIR); $(MAKE) clean)

lftfclean:
	(cd $(LIBDIR); $(MAKE) fclean)

.PHONY: $(NAME) all clean fclean re
