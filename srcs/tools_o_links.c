/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_o_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:42:54 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 14:59:48 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Returns the index of the 'in' subroom of the room with the index in
** parameter.
*/

int		in(int index)
{
	return (2 * index);
}

/*
** Returns the index of the 'out' subroom of the room with the index
** in parameter.
*/

int		out(int index)
{
	return (2 * index + 1);
}

void	initialize_o_links(t_lem *lem)
{
	int		i;

	if (lem->o_links)
	{
		i = -1;
		while (++i < lem->nb_rooms * 2)
			if (!(lem->o_links[i] = (int *)malloc(sizeof(int)
					* (lem->nb_rooms * 2))))
			{
				while (--i >= 0)
					free(lem->o_links[i]);
				free(lem->o_links);
				lem->o_links = NULL;
				return ;
			}
			else
				ft_bzero(lem->o_links[i], (lem->nb_rooms * 2) * sizeof(int));
	}
}
