/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_send_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:23:23 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 15:06:01 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_nbr_str(t_lem *lem, int nb, unsigned long *start)
{
	int		pow;

	pow = 1;
	while (nb / pow >= 10)
		pow *= 10;
	while (pow)
	{
		lem->instr[++(*start)] = nb / pow + '0';
		nb %= pow;
		pow /= 10;
	}
}

/*
** Places the pointer of each path on the room linked to the start room
*/

void	set_paths_to_start(t_path *paths)
{
	int		i;

	i = -1;
	if (!paths)
		return ;
	while (paths[++i].id_first)
	{
		while (paths[i].rooms->prev)
			paths[i].rooms = paths[i].rooms->prev;
	}
}
