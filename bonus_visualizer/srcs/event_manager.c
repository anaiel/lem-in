/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:32:13 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/10 16:04:56 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	key_down_event(t_lem *lem, SDL_Event *event, int *i)
{
	if (event->key.keysym.sym == SDLK_RIGHT
			|| event->key.keysym.sym == SDLK_SPACE)
	{
		draw_ants(lem, event->key.keysym.sym);
		if (*i != NO_ANIM)
			*i = lem->visual.step;
	}
	else if (event->key.keysym.sym == SDLK_a)
	{
		if (lem->visual.step == lem->nb_instr - 1)
			draw_ants(lem, SDLK_SPACE);
		if (*i == NO_ANIM)
			*i = lem->visual.step;
		else
			*i = NO_ANIM;
	}
}

static void	process_anim(t_lem *lem, int *i)
{
	draw_ants(lem, SDLK_RIGHT);
	(*i)++;
	if (*i >= lem->nb_instr * (DIV_ANIM + 1))
	{
		lem->visual.step = lem->nb_instr - 1;
		draw_ants(lem, SDLK_RIGHT);
		*i = NO_ANIM;
	}
}

void		event_manager(t_lem *lem)
{
	int			quit;
	SDL_Event	event;
	int			i;

	quit = 0;
	i = NO_ANIM;
	while (!quit)
	{
		if (SDL_PollEvent(&event) || i != NO_ANIM)
		{
			if ((event.type == SDL_WINDOWEVENT
						&& event.window.event == SDL_WINDOWEVENT_CLOSE)
					|| (event.type == SDL_KEYUP
						&& event.key.keysym.sym == SDLK_ESCAPE))
				quit = 1;
			else if (event.type == SDL_KEYDOWN)
				key_down_event(lem, &event, &i);
			if (i != NO_ANIM && i < lem->nb_instr * (DIV_ANIM + 1))
				process_anim(lem, &i);
		}
	}
}
