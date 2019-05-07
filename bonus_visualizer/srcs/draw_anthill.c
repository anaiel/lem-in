/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_anthill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:25:38 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/10 18:14:33 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	draw_tunnels(t_lem *lem)
{
	int	i;
	int	j;

	i = -1;
	while (++i < lem->nb_rooms - 1)
	{
		j = i;
		while (++j < lem->nb_rooms)
			if (lem->links[i][j] == 1)
				if (thickLineRGBA(lem->visual.rend, lem->rooms[i].x,
						lem->rooms[i].y, lem->rooms[j].x, lem->rooms[j].y, 15,
						255, 255, 255, rand() % 150 + 105))
					error(lem);
	}
}

static void	draw_room_names(t_lem *lem)
{
	SDL_Surface	*text_surf;
	SDL_Texture *text_text;
	SDL_Rect	text_pos;
	int			i;

	i = -1;
	while (++i < lem->nb_rooms)
	{
		if (!(text_surf = TTF_RenderText_Shaded(lem->visual.font,
						lem->rooms[i].id, lem->visual.colors[BLACK],
						lem->visual.colors[WHITE])))
			error(lem);
		text_pos.x = lem->rooms[i].x - 20;
		text_pos.y = lem->rooms[i].y - 20;
		text_pos.h = 25;
		text_pos.w = 25;
		text_text = SDL_CreateTextureFromSurface(lem->visual.rend, text_surf);
		SDL_FreeSurface(text_surf);
		if (!text_text)
			error(lem);
		if (SDL_RenderCopy(lem->visual.rend, text_text, NULL, &text_pos))
			error(lem);
		SDL_DestroyTexture(text_text);
	}
}

static void	set_room_surf(t_lem *lem, SDL_Surface **room_surf)
{
	if (lem->option[0] == FANCY)
		*room_surf = IMG_Load("bonus_visualizer/imgs/building.jpg");
	else if (lem->option[0] != '\0')
		*room_surf = IMG_Load("bonus_visualizer/imgs/room_corr.png");
	else
		*room_surf = IMG_Load("bonus_visualizer/imgs/room_ant.png");
	if (!(*room_surf))
		error(lem);
}

static void	draw_rooms(t_lem *lem)
{
	SDL_Surface *room_surf;
	SDL_Texture *room_text;
	int			i;
	SDL_Rect	room_pos;

	set_room_surf(lem, &room_surf);
	room_text = SDL_CreateTextureFromSurface(lem->visual.rend, room_surf);
	SDL_FreeSurface(room_surf);
	if (!room_text)
		error(lem);
	room_pos.h = 40;
	room_pos.w = 60;
	i = -1;
	while (++i < lem->nb_rooms)
	{
		room_pos.x = lem->rooms[i].x - 15;
		room_pos.y = lem->rooms[i].y - 15;
		if (SDL_RenderCopy(lem->visual.rend, room_text, NULL, &room_pos))
			error(lem);
	}
	SDL_DestroyTexture(room_text);
}

void		draw_anthill(t_lem *lem)
{
	if (SDL_SetRenderTarget(lem->visual.rend, lem->visual.anthill_text))
		error(lem);
	if (SDL_SetRenderDrawColor(lem->visual.rend, BG_R, BG_G, BG_B, BG_A)
			|| SDL_RenderClear(lem->visual.rend))
		error(lem);
	draw_background(lem);
	draw_tunnels(lem);
	draw_rooms(lem);
	draw_room_names(lem);
	if (SDL_SetRenderTarget(lem->visual.rend, NULL))
		error(lem);
}
