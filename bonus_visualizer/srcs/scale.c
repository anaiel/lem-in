/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:23:40 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/02 12:35:03 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	scale(t_lem *lem)
{
	int		i;

	i = -1;
	while (++i < lem->nb_rooms)
	{
		lem->rooms[i].x = (lem->rooms[i].x - lem->x_min) * lem->scale
			+ lem->x_offset;
		lem->rooms[i].y = (lem->rooms[i].y - lem->y_min) * lem->scale
			+ lem->y_offset;
	}
	i = -1;
	while (++i < lem->nb_ants)
	{
		lem->ants[i].x = (lem->ants[i].x - lem->x_min) * lem->scale
			+ lem->x_offset;
		lem->ants[i].y = (lem->ants[i].y - lem->y_min) * lem->scale
			+ lem->y_offset;
	}
}

void	set_scale(t_lem *lem)
{
	int		tmp;

	lem->scale = (HEIGHT - 2 * MARGIN) / (lem->y_max - lem->y_min);
	tmp = (WIDTH - 2 * MARGIN) / (lem->x_max - lem->x_min);
	if (tmp < lem->scale)
	{
		lem->scale = tmp;
		lem->x_offset = MARGIN;
		lem->y_offset = (HEIGHT - MARGIN - lem->scale * (lem->y_max
					- lem->y_min)) / 2;
	}
	else
	{
		lem->y_offset = MARGIN;
		lem->x_offset = (WIDTH - MARGIN - lem->scale * (lem->x_max
					- lem->x_min)) / 2;
	}
}
