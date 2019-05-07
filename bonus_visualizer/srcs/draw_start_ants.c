/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_start_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 12:52:02 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/10 15:13:08 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	draw_start_ants(t_lem *lem)
{
	static int	marker = -1;
	SDL_Rect	start_ant_pos;
	int			i;

	i = -1;
	if (lem->visual.step != -1 && lem->visual.step < lem->nb_instr)
	{
		while (lem->instr[lem->visual.step][++i].ant_id)
		{
			marker = (lem->visual.step == marker) ? -1 : marker;
			if (lem->instr[lem->visual.step][i].ant_id == lem->nb_ants
					|| marker != -1)
			{
				marker = (marker == -1) ? lem->visual.step - 1 : marker;
				return ;
			}
		}
	}
	start_ant_pos.h = 25;
	start_ant_pos.w = 25;
	start_ant_pos.x = lem->rooms[0].x;
	start_ant_pos.y = lem->rooms[0].y;
	if (SDL_RenderCopy(lem->visual.rend, lem->visual.ant_text, NULL,
				&start_ant_pos))
		error(lem);
}
