/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:17:34 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 15:11:23 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		get_path(t_lem *lem, t_plist **rooms, int current_index)
{
	int		next_index;
	t_plist	*link;
	int		rval;

	if (current_index != END && current_index != START)
	{
		if (!(link = new_link(lem->rooms + current_index)))
			return (-1);
		*rooms = add_link(link, *rooms);
	}
	if (current_index == END)
		return (0);
	next_index = -1;
	while (++next_index < lem->nb_rooms)
		if (lem->o_links[in(current_index)][out(next_index)])
		{
			if ((rval = get_path(lem, rooms, next_index)) == -1)
				return (-1);
			return (1 + rval);
		}
	return (-1);
}

static void		fill_path(t_lem *lem, t_path *paths, int nb_paths)
{
	int	count;
	int	i;

	count = -1;
	i = 1;
	while (++i < lem->nb_rooms)
		if (lem->o_links[in(START)][out(i)])
		{
			paths[++count].id_first = lem->rooms[i].id;
			paths[count].i_first = i;
			paths[count].rooms = NULL;
			paths[count].w = get_path(lem, &(paths[count].rooms), i);
		}
	paths[nb_paths].id_first = NULL;
	paths[nb_paths].i_first = -1;
	paths[nb_paths].w = 0;
}

/*
** Returns a list of paths containing the information about the index and id of
** the first rooms of the paths and their length (weight). Sorts the list by
** length.
*/

static t_path	*set_path_len_list(t_lem *lem)
{
	int		nb_paths;
	int		i;
	t_path	*paths;
	t_path	tmp;

	nb_paths = 0;
	i = 1;
	while (++i < lem->nb_rooms)
		if (lem->o_links[in(START)][out(i)])
			nb_paths++;
	if (!(paths = (t_path *)malloc(sizeof(t_path) * (nb_paths + 1))))
		return (NULL);
	fill_path(lem, paths, nb_paths);
	while (nb_paths-- > 0)
	{
		i = -1;
		while (paths[++i + 1].i_first != -1)
			if (paths[i].w > paths[i + 1].w)
			{
				tmp = paths[i + 1];
				paths[i + 1] = paths[i];
				paths[i] = tmp;
			}
	}
	return (paths);
}

/*
** Resets the weight of the rooms to 0.
*/

static int		clear_weights(t_lem *lem)
{
	int		i;

	i = -1;
	while (++i < lem->nb_rooms)
		lem->rooms[i].w = 0;
	return (1);
}

/*
** Uses the Edmonds-Karp algorithm with all the vertices capacities at 1 to
** find paths of incrementing lengths as long as the new paths allow for a
** quicker flow of ants.
*/

void			find_paths(t_lem *lem)
{
	int		stop;
	t_path	*current_paths;

	stop = 0;
	while (!stop && clear_weights(lem))
		if ((stop = bfs(lem)) == -2)
			error(lem);
		else if (!stop)
		{
			if (!(current_paths = set_path_len_list(lem)))
				error(lem);
			set_ants_per_room(lem, current_paths);
			if (!lem->paths || current_paths[0].nb_ants + current_paths[0].w
					< lem->paths[0].nb_ants + lem->paths[0].w)
			{
				free_path(&lem->paths);
				lem->paths = current_paths;
			}
			else
			{
				free_path(&current_paths);
				stop = 1;
			}
		}
}
