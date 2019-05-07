/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ants_per_room.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:05:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/18 14:33:25 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	initialize_nb_ants_paths(t_path *paths)
{
	int		i;

	i = -1;
	while (paths[++i].i_first != -1)
	{
		paths[i].nb_ants = 0;
		paths[i].nb_remaining = 0;
	}
	paths[i].nb_ants = -1;
	paths[i].nb_remaining = -1;
}

static void	put_ants_on_paths(t_path **paths, int *i, int *ants_left)
{
	int		max_capacity_reached;

	max_capacity_reached = 0;
	while (!max_capacity_reached && *ants_left)
		if ((*paths)[*i].w + (*paths)[*i].nb_ants + 1 <= (*paths)[0].w
				+ (*paths)[0].nb_ants)
		{
			(*ants_left)--;
			(*paths)[*i].nb_ants++;
			(*paths)[*i].nb_remaining++;
		}
		else
			max_capacity_reached = 1;
	(*i)++;
}

/*
** Sets the optimal number of ants to send in each available path depending
** on the length of the path and the total number of ants.
*/

void		set_ants_per_room(t_lem *lem, t_path *paths)
{
	int		ants_left;
	int		i;

	initialize_nb_ants_paths(paths);
	ants_left = lem->nb_ants;
	while (ants_left)
	{
		i = 1;
		while (ants_left && paths[i].i_first != -1)
			put_ants_on_paths(&paths, &i, &ants_left);
		if (ants_left)
		{
			ants_left--;
			paths[0].nb_ants++;
			paths[0].nb_remaining++;
		}
	}
}
