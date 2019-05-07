/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:25:54 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 15:44:31 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		error(t_lem *lem)
{
	ft_putstr_fd("The process has been stopped.\n", 2);
	end(lem);
	exit(0);
}

static void	terminate_sdl(t_lem *lem)
{
	SDL_DestroyWindow(lem->visual.win);
	SDL_DestroyRenderer(lem->visual.rend);
	SDL_DestroyTexture(lem->visual.anthill_text);
	TTF_CloseFont(lem->visual.font);
	free(lem->visual.colors);
	SDL_DestroyTexture(lem->visual.ant_text);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

static void	free_starred(t_lem *lem)
{
	free(lem->input);
	free(lem->rooms);
	free(lem->links);
	free(lem->instr);
	free(lem->option);
}

void		end(t_lem *lem)
{
	int		i;

	if (lem->rooms)
	{
		i = -1;
		while (++i < lem->nb_rooms)
			free(lem->rooms[i].id);
	}
	if (lem->links && lem->links[0])
	{
		i = -1;
		while (++i < lem->nb_rooms)
			free(lem->links[i]);
	}
	if (lem->instr && lem->instr[0])
	{
		i = -1;
		while (++i < lem->nb_instr)
			free(lem->instr[i]);
	}
	free_starred(lem);
	terminate_sdl(lem);
}
