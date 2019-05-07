/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:39:56 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/19 15:47:54 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	nb_links_from(t_lem *lem, int index, int *current_w_list)
{
	int		nb_links;
	int		i;
	int		j;

	i = -1;
	nb_links = 0;
	if (current_w_list)
	{
		while (!nb_links && current_w_list[++i] != -1)
		{
			j = -1;
			while (++j < lem->nb_rooms * 2)
				nb_links += (lem->rooms[j / 2].w < 2)
					? lem->o_links[current_w_list[i]][j] : 0;
		}
	}
	else
	{
		while (++i < lem->nb_rooms * 2)
			nb_links += (lem->rooms[i / 2].w < 2) ? lem->o_links[index][i] : 0;
	}
	return (nb_links);
}

static void	set_orientations(t_lem *lem, int *current_w_list, int *j)
{
	int	i;

	i = -1;
	while (++i != -1 && current_w_list[i] != -1)
		if (lem->o_links[current_w_list[i]][*j])
		{
			lem->o_links[current_w_list[i]][*j] = 0;
			lem->o_links[*j][current_w_list[i]] = 1;
			*j = current_w_list[i];
			i = -2;
		}
}

static int	process(t_lem *lem, int *next_w_list, int *current_w_list, int i)
{
	int	j;

	j = -1;
	while (++j < lem->nb_rooms * 2)
		if (lem->o_links[current_w_list[i]][j] == 1
				&& lem->rooms[j / 2].w < 2)
		{
			if (j == in(START))
			{
				lem->o_links[current_w_list[i]][in(START)] = 0;
				lem->o_links[in(START)][current_w_list[i]] = 1;
				free(next_w_list);
				return (current_w_list[i]);
			}
			next_w_list[++(lem->count)] = j;
			lem->rooms[j / 2].w++;
		}
	return (-1);
}

/*
** Recursively returns the the index of the room with the cuurent
** weight which is included in the shortest path from start to end. In the
** return process it also sets the orientation of the links.
*/

static int	bfs_recursive(t_lem *lem, int *current_w_list)
{
	int		*next_w_list;
	int		i;
	int		j;

	j = -1;
	if (nb_links_from(lem, 0, current_w_list))
	{
		if (!(next_w_list = (int *)malloc(sizeof(int) * (lem->nb_rooms - 1)
				* (lem->nb_rooms - 1))))
			return (-2);
		lem->count = -1;
		i = -1;
		while (current_w_list[++i] != -1)
			if ((j = process(lem, next_w_list, current_w_list, i)) != -1)
				return (j);
		next_w_list[++(lem->count)] = -1;
		j = bfs_recursive(lem, next_w_list);
		if (j >= 0)
			set_orientations(lem, current_w_list, &j);
		free(next_w_list);
	}
	return (j);
}

/*
** Returns -2 in case of error, -1 if no path was found or 0 if a path was
** found. Initializes the recursive bfs algorithm with the list of rooms
** linked to the end room. It then sets the orientation of the link between
** the end and the last room of the path.
*/

int			bfs(t_lem *lem)
{
	int		*start_list;
	int		count;
	int		i;
	int		path_index;

	if (!(start_list = (int *)malloc(sizeof(int)
			* (nb_links_from(lem, out(END), NULL) + 1))))
		error(lem);
	count = -1;
	i = 1;
	while (++i < lem->nb_rooms * 2)
		if (lem->o_links[out(END)][i] == 1)
		{
			start_list[++count] = i;
			lem->rooms[i / 2].w++;
		}
	start_list[++count] = -1;
	if ((path_index = bfs_recursive(lem, start_list)) >= 0)
	{
		lem->o_links[out(END)][path_index] = 0;
		lem->o_links[path_index][out(END)] = 1;
		path_index = 0;
	}
	free(start_list);
	return (path_index);
}
