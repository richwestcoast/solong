# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rwinder <marvin@42.fr>                      +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 16:20:00 by rwinder            #+#    #+#             #
#    Updated: 2023/01/03 16:20:00 by rwinder           ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Werror -Wextra
SRC = ft_printf.c ft_print_hex.c ft_print_ptr.c ft_print_unsigned_int.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strstr.c ft_tolower.c ft_toupper.c ft_strchr.c ft_strrchr.c ft_memcmp.c ft_memset.c ft_memcpy.c ft_memmove.c ft_strnstr.c ft_strdup.c ft_substr.c ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_putnbr_fd.c ft_striteri.c

all: $(NAME)

$(NAME):
	gcc -c $(FLAGS) $(SRC)
	ar rc libft.a *.o
	ranlib libft.a
clean:
	/bin/rm -f *.o
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all