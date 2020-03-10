# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smanta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/08 20:42:22 by smanta            #+#    #+#              #
#    Updated: 2020/02/08 20:42:38 by smanta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FILE_C = ft_extra_csp.c ft_isdigit.c ft_lltoa_base.c ft_printf.c \
ft_putnbrull.c ft_putstr.c ft_strchr.c ft_strjoin.c \
ft_strlen.c ft_strmap.c ft_strnew.c ft_tolower.c \
ft_ulltoa_base.c ft_unumlen.c is_whats.c letspars_what.c \
letsprint.c letsprint_percent.c print_csp.c print_diu.c \
print_f.c print_ox.c utils_f.c utils.c

OBJ = $(FILE_C:.c=.o)

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ): %.o: %.c
	@gcc -c -Wall -Wextra -Werror -I . $< -o $@

clean:
	$(RM) -rf $(OBJ)

fclean: clean
	$(RM) -rf $(NAME)

re: fclean all
