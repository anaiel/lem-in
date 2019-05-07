/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_o_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:13:52 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 15:39:20 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Returns a t_link variable containing the index of the rooms before and after
** the separator (-). If no matching room is found, the index is -1.
*/

static t_link	get_linked_rooms(t_lem *lem, int i_separator, char *str)
{
	int		i;
	int		i_endl;
	t_link	res;

	i_endl = i_separator;
	while (str[i_endl] && str[i_endl] != '\n')
		i_endl++;
	str[i_separator] = 0;
	str[i_endl] = 0;
	res.st = -1;
	res.nd = -1;
	i = -1;
	while (++i < lem->nb_rooms)
	{
		if (ft_strequ(str, lem->rooms[i].id))
			res.st = i;
		if (ft_strequ(str + i_separator + 1, lem->rooms[i].id))
			res.nd = i;
	}
	str[i_separator] = '-';
	str[i_endl] = '\n';
	return (res);
}

static void		init_links(t_link *link1, t_link *link2)
{
	link1->st = -1;
	link1->nd = -1;
	link2->st = -1;
	link2->nd = -1;
}

/*
** Returns an error if the first link has already been set. Returns 0 if the
** second link is not valid (the first or second index is missing). Otherwise
** it copies the values of the second link in the first link.
*/

static int		check_and_replace(t_link *link, t_link *tmp)
{
	if (tmp->st != -1 && tmp->nd != -1)
	{
		if (link->st != -1)
			return (ERROR);
		link->st = tmp->st;
		link->nd = tmp->nd;
	}
	return (0);
}

/*
** For each '-' in the line, checks if the first (st) and second (nd) term
** are valid rooms. If there is no valid combination or more than one, returns
** error. Otherwise, stores the information in the adjacency matrix and returns
** the current parser step.
*/

int				setup_o_links(t_lem *lem, char *str)
{
	int		i;
	t_link	link;
	t_link	tmp;

	init_links(&link, &tmp);
	i = -1;
	while (str[++i] && str[i] != '\n')
	{
		if (str[i] == '-')
		{
			tmp = get_linked_rooms(lem, i, str);
			if ((check_and_replace(&link, &tmp)) == ERROR)
				return (ERROR);
		}
	}
	if (link.st == -1 || link.nd == -1)
		return (ERROR);
	lem->o_links[out(link.st)][in(link.nd)] = 1;
	lem->o_links[out(link.nd)][in(link.st)] = 1;
	return (SET_LINKS);
}
