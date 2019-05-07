# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 17:19:55 by anleclab          #+#    #+#              #
#    Updated: 2019/04/12 15:38:20 by dtrigalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Werror -Wextra -g3
INC = -I./inc
SRC_DIR = src
SRC_NAMES = ft_round_double.c \
	  ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memccpy.c \
	  ft_memmove.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strlen.c \
	  ft_strdup.c \
	  ft_strcpy.c \
	  ft_strncpy.c \
	  ft_strcat.c \
	  ft_strncat.c \
	  ft_strlcat.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strstr.c \
	  ft_strnstr.c \
	  ft_strcmp.c \
	  ft_strncmp.c \
	  ft_atoi.c \
	  ft_isalpha.c \
	  ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_memalloc.c \
	  ft_memdel.c \
	  ft_strnew.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strsub.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_strsplit.c \
	  ft_itoa.c \
	  ft_putchar.c \
	  ft_putstr.c \
	  ft_putendl.c \
	  ft_putnbr.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_lstnew.c \
	  ft_lstdelone.c \
	  ft_lstdel.c \
	  ft_lstadd.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_strsplitlst.c \
	  ft_putstrarray.c \
	  ft_putstrlst.c \
	  ft_putfile.c \
	  ft_filelinecount.c \
	  ft_putwchar.c \
	  ft_printbits.c \
	  ft_wchar_to_bytes.c \
	  ft_double_power.c \
	  ft_array_swap.c \
	  ft_itoa_base.c \
	  ft_litoa.c \
	  ft_llitoa.c \
	  ft_ldouble_power.c \
	  ft_tabdel.c \
	  ft_fopen.c \
	  ft_fclose.c \
	  ft_fgetc.c \
	  ft_char_realloc.c \
	  ft_intlen.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_NAMES))
OBJ_DIR = obj
OBJ_NAMES = $(SRC_NAMES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES))

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "[ $(GREEN)✔$(NONE) ] libft/$(NAME) library"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "[ $(GREEN)✔$(NONE) ] libft/$(OBJ_DIR) directory"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@gcc $(FLAGS) $(INC) -c $< -o $@

clean:
	@rm -Rf $(OBJ_DIR)
	@echo "[ $(RED)✗$(NONE) ] libft/$(OBJ_DIR) directory"

fclean: clean
	@rm -f $(NAME)
	@echo "[ $(RED)✗$(NONE) ] libft/$(NAME) library"

re: fclean all
