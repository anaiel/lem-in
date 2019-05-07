/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:25:54 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 15:07:57 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	end(t_lem *lem)
{
	int		i;

	free(lem->input);
	if (lem->rooms)
	{
		i = -1;
		while (++i < lem->nb_rooms)
			free(lem->rooms[i].id);
	}
	free(lem->rooms);
	if (lem->o_links)
	{
		i = -1;
		while (++i < 2 * lem->nb_rooms)
			free(lem->o_links[i]);
	}
	free(lem->o_links);
	free(lem->instr);
	if (lem->paths)
		free_path(&lem->paths);
}

void	free_path(t_path **paths)
{
	int		i;

	set_paths_to_start(*paths);
	if (*paths)
	{
		i = -1;
		while ((*paths)[++i].id_first)
			delete_list(&(*paths)[i].rooms);
		free(*paths);
	}
	*paths = NULL;
}

void	error(t_lem *lem)
{
	end(lem);
	ft_putstr_fd("Please feed me a decent map.\n", 2);
	exit(0);
}

void	pre_init_error(t_lem lem)
{
	free(lem.input);
	ft_putstr_fd("Please feed me a decent map.\n", 2);
	exit(0);
}
