/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:08:08 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 16:25:51 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_instr(t_lem *lem, t_plist *curr_room, int *mem)
{
	int				len_next;
	unsigned long	len;

	len_next = (curr_room->next) ? ft_strlen(curr_room->next->room->id)
			: ft_strlen(lem->rooms[END].id);
	len = lem->instr_len;
	lem->instr_len += ft_intlen(curr_room->room->ant_id) + len_next + 3;
	if (lem->instr_len > (unsigned long)(*mem * BUFF_SIZE))
		if (!(lem->instr = ft_char_realloc(lem->instr, ++(*mem) * BUFF_SIZE)))
			error(lem);
	lem->instr[len] = 'L';
	add_nbr_str(lem, curr_room->room->ant_id, &len);
	lem->instr[++len] = '-';
	if (curr_room->next)
	{
		ft_strcpy(lem->instr + ++len, curr_room->next->room->id);
		len += ft_strlen(curr_room->next->room->id);
	}
	else
	{
		ft_strcpy(lem->instr + ++len, lem->rooms[END].id);
		len += ft_strlen(lem->rooms[END].id);
	}
	lem->instr[len] = ' ';
}

static int	make_ants_move(t_lem *lem, int *mem)
{
	int		i;
	t_plist	*cache;
	int		rval;

	rval = 0;
	i = -1;
	while (lem->paths[++i].id_first)
	{
		cache = lem->paths[i].rooms;
		while (cache->room->ant_id)
		{
			add_instr(lem, cache, mem);
			if (cache->next)
				cache->next->room->ant_id = cache->room->ant_id;
			cache->room->ant_id = 0;
			if (cache->prev)
				cache = cache->prev;
			rval = 1;
		}
		if (rval && lem->paths[i].rooms->next)
			lem->paths[i].rooms = lem->paths[i].rooms->next;
	}
	return (rval);
}

static void	process_sending(t_lem *lem, int i, int *ants_left, int *mem)
{
	unsigned long	len;
	int				j;

	if (lem->paths[i].nb_remaining > 0)
	{
		lem->rooms[lem->paths[i].i_first].ant_id = lem->nb_ants
				- *ants_left + 1;
		len = lem->instr_len;
		lem->instr_len += ft_intlen(lem->nb_ants - *ants_left + 1)
				+ ft_strlen(lem->paths[i].id_first) + 3;
		if (lem->instr_len > (unsigned long)(*mem * BUFF_SIZE))
			if (!(lem->instr = ft_char_realloc(lem->instr,
					++(*mem) * BUFF_SIZE)))
				error(lem);
		lem->instr[len] = 'L';
		add_nbr_str(lem, lem->nb_ants - *ants_left + 1, &len);
		lem->instr[++len] = '-';
		j = -1;
		while (lem->paths[i].id_first[++j])
			lem->instr[++len] = lem->paths[i].id_first[j];
		lem->instr[++len] = ' ';
		(*ants_left)--;
		lem->paths[i].nb_remaining--;
	}
}

/*
** Builds the instructions in lem->instr. For each line, it makes the ants
** already in the rooms to the next rooms, and then sends the remaining ants
** in the different paths.
*/

void		send_ants(t_lem *lem)
{
	static int	mem = 0;
	int			i;
	int			ants_left;
	int			first_line;

	ants_left = lem->nb_ants;
	first_line = 1;
	set_paths_to_start(lem->paths);
	while (first_line || make_ants_move(lem, &mem))
	{
		first_line = 0;
		i = -1;
		while (lem->paths[++i].i_first != -1 && ants_left)
			process_sending(lem, i, &ants_left, &mem);
		lem->instr[lem->instr_len - 1] = '\n';
	}
	lem->instr[lem->instr_len - 1] = '\0';
}
