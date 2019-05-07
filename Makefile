# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 15:21:21 by anleclab          #+#    #+#              #
#    Updated: 2019/04/19 16:13:55 by anleclab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CFLAGS = -Wall -Wextra -Werror
SRC = main.c \
	  get_options.c \
	  count_rooms_and_fill_input.c \
	  end.c \
	  parser.c \
	  tools_parser.c \
	  send_all_ants.c \
	  find_paths.c \
	  setup_o_links.c \
	  set_ants_per_room.c \
	  send_ants.c \
	  tools_options.c \
	  tools_o_links.c \
	  tools_list.c \
	  tools_send_ants.c \
	  bfs.c
SRCSFD = srcs/
OBJSFD = objs/
OBJS = $(addprefix $(OBJSFD),$(SRC:.c=.o))

HDR = lem_in.h
HDRSFD = includes/
HDRS = $(addprefix $(HDRSFD),$(HDR))

HDR_INC = -I./includes
LIBFT_HDR = -I./libft/inc
LIB_BINARY = -L./libft -lft
LIBFT= libft/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m
BOLD_UNDERLINED = \033[1;4m

all: make_start check_libft project $(NAME) $(HDRS)
	@echo "\n\033[1;4;42m!! Success !!$(NONE)\n"

$(NAME): $(OBJSFD) $(OBJS) $(LIBFT) $(HDRS)
	@gcc $(CFLAGS) $(OBJS) $(LIB_BINARY) -o $@
	@echo "[ \033[0;32m✔\033[0m ] lem-in executable"

brewing:
	@brew install sdl2
	@brew install sdl2_gfx
	@brew install sdl2_image
	@brew install sdl2_mixer
	@brew install sdl2_net
	@brew install sdl2_ttf

make_start:
	@echo "\n\033[1;4;42mBeginning process...$(NONE)"

check_libft:
	@echo "\n$(BOLD_UNDERLINED)<| Checking libft |>$(NONE)\n"
	@make -C libft

project:
	@echo "\n$(BOLD_UNDERLINED)<| Checking project |>$(NONE)\n"

$(OBJSFD):
	@mkdir $@
	@echo "[ $(GREEN)✔$(NONE) ] objs/ directory"

$(OBJSFD)%.o: $(SRCSFD)%.c $(HDRS) $(LIBFT)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) -c $< -o $@
	@echo "[ $(GREEN)✔$(NONE) ] $@ object"

visualizer:
	@echo "\n$(BOLD_UNDERLINED)<| Adding visualizer |>$(NONE)"
	@make -C ./bonus_visualizer
	@cp bonus_visualizer/visualizer .

clean:
	@/bin/rm -rf $(OBJSFD)
	@echo "[ $(RED)✗$(NONE) ] $(OBJSFD) directory"
	@make -C ./libft clean
	@make -C ./bonus_visualizer clean

fclean: clean
	@/bin/rm -f $(NAME) visualizer
	@echo "[ $(RED)✗$(NONE) ] $(NAME) executable"
	@echo "[ $(RED)✗$(NONE) ] visualizer executable"
	@make -C ./libft fclean
	@make -C ./bonus_visualizer fclean

re: fclean all

.PHONY: make_start brewing all check_libft project clean fclean re visualizer
