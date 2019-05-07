/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:56:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/18 18:09:12 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_line_count(t_lem lem)
{
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (lem.instr[++i])
		if (lem.instr[i] == '\n')
			count++;
	ft_putstr("line count: ");
	ft_putnbr(count);
	ft_putchar('\n');
}

void		print_paths(t_lem lem)
{
	int		i;
	t_plist	*cache;

	if ((i = -1) && lem.o_links[out(START)][in(END)])
		return ;
	set_paths_to_start(lem.paths);
	while (lem.paths[++i].id_first)
	{
		ft_putstr("#paths ");
		ft_putnbr(i + 1);
		ft_putstr(" (");
		ft_putnbr(lem.paths[i].w);
		ft_putstr(" rooms, ");
		ft_putnbr(lem.paths[i].nb_ants);
		ft_putstr(" ants): ");
		cache = lem.paths[i].rooms;
		while (cache)
		{
			ft_putstr(cache->room->id);
			if (cache->next)
				ft_putstr(" -> ");
			cache = cache->next;
		}
		ft_putchar('\n');
	}
}

void		print_ant_nb(t_lem lem)
{
	ft_putstr("ant number: ");
	ft_putnbr(lem.nb_ants);
	ft_putchar('\n');
}

void		print_ants_per_room(t_lem lem)
{
	int		i;

	if (lem.o_links[out(START)][in(END)])
	{
		ft_putstr("all ants go directly to the end room\n");
		return ;
	}
	i = -1;
	ft_putstr("ants per room:");
	while (lem.paths[++i].i_first != -1)
	{
		if (i != 0)
			ft_putstr(", ");
		else
			ft_putchar(' ');
		ft_putnbr(lem.paths[i].nb_ants);
		ft_putstr(" in ");
		ft_putstr(lem.paths[i].id_first);
		ft_putstr(" (");
		ft_putnbr(lem.paths[i].w);
		ft_putstr(")");
	}
	ft_putchar('\n');
}
