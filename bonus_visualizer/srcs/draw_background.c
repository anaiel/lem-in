/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:50:14 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/10 18:14:45 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	draw_background(t_lem *lem)
{
	SDL_Surface *room_surf;
	SDL_Texture *room_text;
	SDL_Rect	room_pos;

	if (lem->option[0] == FANCY)
		room_surf = IMG_Load("bonus_visualizer/imgs/big_city.png");
	else if (lem->option[0] != '\0')
		room_surf = IMG_Load(lem->option);
	else
		room_surf = IMG_Load("bonus_visualizer/imgs/anthill.png");
	if (!room_surf)
		error(lem);
	room_text = SDL_CreateTextureFromSurface(lem->visual.rend, room_surf);
	SDL_FreeSurface(room_surf);
	if (!room_text)
		error(lem);
	room_pos.h = HEIGHT;
	room_pos.w = WIDTH;
	room_pos.x = 0;
	room_pos.y = 0;
	if (SDL_RenderCopy(lem->visual.rend, room_text, NULL, &room_pos))
		error(lem);
	SDL_DestroyTexture(room_text);
}
