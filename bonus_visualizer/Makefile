# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 15:21:21 by anleclab          #+#    #+#              #
#    Updated: 2019/04/18 14:26:54 by dtrigalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

CFLAGS = -Wall -Wextra -Werror
SRC = main.c \
	  parser.c \
	  set_rooms_and_ants.c \
	  count_and_fill_input.c \
	  draw_anthill.c \
	  draw_ants.c \
	  end.c \
	  fill_adjacency_matrix.c \
	  set_instructions.c \
	  event_manager.c \
	  scale.c \
	  draw_start_ants.c \
	  draw_start_end_ant_nb.c \
	  render_menu.c \
	  option.c \
	  draw_background.c \
	  initialize_beginning.c
SRCSFD = srcs/
OBJSFD = objs/
OBJS = $(addprefix $(OBJSFD),$(SRC:.c=.o))

HDR = visualizer.h
HDRSFD = includes/
HDRS = $(addprefix $(HDRSFD),$(HDR))

HDR_INC = -I./includes
LIBFT_HDR = -I../libft/inc
LIB_BINARY = -L../libft -lft
LIBFT= ../libft/libft.a

SDL_HDR=$(shell sdl2-config --cflags | cut -d' ' -f1)
SDL_IMAGE_HDR=$(SDL_HDR)_image
SDL_TTF_HDR=$(SDL_HDR)_ttf
SDL_GFX_HDR=$(SDL_HDR)_gfx
SDL_BINARY=$(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_gfx

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m
BOLD_UNDERLINED = \033[1;4m

all: make_start check_libft project $(NAME) $(HDRS)
	@echo "\n\033[1;4;42m!! Success !!$(NONE)\n"

$(NAME): $(OBJSFD) $(OBJS) $(LIBFT) $(HDRS)
	@gcc $(CFLAGS) $(OBJS) $(LIB_BINARY) $(SDL_BINARY) -o $@
	@echo "[ \033[0;32m✔\033[0m ] visualizer executable"

check_libft:
	@echo "\n$(BOLD_UNDERLINED)<| Checking libft |>$(NONE)\n"
	@make -C ../libft

make_start:
	@echo "\n\033[1;4;42mBeginning process...$(NONE)"

project:
	@echo "\n$(BOLD_UNDERLINED)<| Checking project |>$(NONE)\n"

$(OBJSFD):
	@mkdir $@
	@echo "[ $(GREEN)✔$(NONE) ] bonus_visualizer/objs/ directory"

$(OBJSFD)%.o: $(SRCSFD)%.c $(HDRS) $(LIBFT)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) $(SDL_HDR) $(SDL_IMAGE_HDR) $(SDL_TTF_HDR) $(SDL_GFX_HDR) -c $< -o $@
	@echo "[ $(GREEN)✔$(NONE) ] $@ object"

clean:
	@rm -rf $(OBJSFD)
	@echo "[ $(RED)✗$(NONE) ] bonus_visualizer/$(OBJSFD) directory"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "[ $(RED)✗$(NONE) ] $(NAME) executable"

re: fclean all

.PHONY: make_start all project clean fclean re check_libft
