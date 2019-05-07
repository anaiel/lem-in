/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_beginning.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:57:21 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/19 15:45:22 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		initialize_instr_and_visual(t_lem *lem)
{
	lem->x_max = INT_MIN;
	lem->x_min = INT_MAX;
	lem->y_max = INT_MIN;
	lem->y_min = INT_MAX;
	if (!(lem->instr = (t_instr **)malloc(sizeof(t_instr *) * lem->nb_instr)))
		error(lem);
	ft_bzero(lem->instr, sizeof(t_instr *) * lem->nb_instr);
	ft_bzero(&(lem->visual), sizeof(t_visual));
	if (!(lem->visual.colors = (SDL_Color *)malloc(sizeof(SDL_Color) * 2)))
		error(lem);
	lem->visual.colors[WHITE].r = 255;
	lem->visual.colors[WHITE].g = 255;
	lem->visual.colors[WHITE].b = 255;
	lem->visual.colors[WHITE].a = 255;
	lem->visual.colors[BLACK].r = 0;
	lem->visual.colors[BLACK].g = 0;
	lem->visual.colors[BLACK].b = 0;
	lem->visual.colors[BLACK].a = 255;
	lem->visual.ant_text = NULL;
	lem->visual.step = -1;
	lem->parse_step = SET_NB_ANTS;
}

static void	set_ant_surf(t_lem *lem, SDL_Surface **ant_surf)
{
	if (lem->option[0] == FANCY)
		*ant_surf = IMG_Load("bonus_visualizer/imgs/spiderman.jpeg");
	else if (lem->option[0] != '\0')
		*ant_surf = IMG_Load(lem->option);
	else
		*ant_surf = IMG_Load("bonus_visualizer/imgs/one_ant.png");
	if (!(*ant_surf))
	{
		ft_putstr_fd("Tip: The option parameter might not be well written.", 2);
		ft_putstr_fd(" Use the year of your picture and your pseudonym.\n", 2);
		ft_putstr_fd("(Nota Bene : Make sure your picture is in /sgoinfre/", 2);
		ft_putstr_fd("photos_students/<Year>/<Pseudonym>)\n", 2);
		error(lem);
	}
}

void		initialize_sdl(t_lem *lem)
{
	SDL_Surface	*ant_surf;

	if (SDL_Init(SDL_INIT_VIDEO) || TTF_Init()
			|| (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)))
		error(lem);
	if (!(lem->visual.win = SDL_CreateWindow("lem-in", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)))
		error(lem);
	if (!(lem->visual.rend = SDL_CreateRenderer(lem->visual.win, -1,
			SDL_RENDERER_ACCELERATED)))
		error(lem);
	lem->visual.font = TTF_OpenFont("bonus_visualizer/fonts/Lato-Regular.ttf",
			50);
	if (!lem->visual.font)
		error(lem);
	if (!(lem->visual.anthill_text = SDL_CreateTexture(lem->visual.rend,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
		error(lem);
	set_ant_surf(lem, &ant_surf);
	lem->visual.ant_text = SDL_CreateTextureFromSurface(lem->visual.rend,
			ant_surf);
	SDL_FreeSurface(ant_surf);
	if (!lem->visual.ant_text)
		error(lem);
}

void		initialize_lem(t_lem *lem)
{
	int		i;

	initialize_instr_and_visual(lem);
	if (!(lem->rooms = (t_room *)malloc(sizeof(t_room) * lem->nb_rooms)))
		error(lem);
	i = -1;
	while (++i < lem->nb_rooms)
		lem->rooms[i].id = NULL;
	if (!(lem->links = (int **)malloc(sizeof(int *) * lem->nb_rooms)))
		error(lem);
	lem->rooms[START].ant_nb = lem->nb_ants;
	lem->rooms[END].ant_nb = 0;
	i = -1;
	while (++i < lem->nb_rooms)
		if (!(lem->links[i] = (int *)malloc(sizeof(int) * lem->nb_rooms)))
		{
			while (--i >= 0)
				free(lem->links[i]);
			i = lem->nb_rooms;
		}
		else
			ft_bzero(lem->links[i], lem->nb_rooms * sizeof(int));
	if (!lem->links[0])
		error(lem);
	initialize_sdl(lem);
}
