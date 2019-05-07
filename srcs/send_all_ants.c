/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_all_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:15:35 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/18 18:01:09 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		send_all_ants(t_lem *lem)
{
	int		ant_id;
	int		len_ant_id;
	int		endid_strlen;

	endid_strlen = ft_strlen(lem->rooms[END].id);
	ant_id = 0;
	while (++ant_id <= lem->nb_ants)
	{
		len_ant_id = ft_intlen(ant_id);
		if (!(lem->instr = ft_char_realloc(lem->instr, lem->instr_len
				+ len_ant_id + endid_strlen + 3)))
			error(lem);
		lem->instr[lem->instr_len] = 'L';
		add_nbr_str(lem, ant_id, &(lem->instr_len));
		lem->instr_len++;
		lem->instr[lem->instr_len++] = '-';
		ft_strcpy(lem->instr + lem->instr_len, lem->rooms[END].id);
		lem->instr_len += endid_strlen;
		if (ant_id != lem->nb_ants)
			ft_strcpy(lem->instr + lem->instr_len++, " ");
		else
			ft_strcpy(lem->instr + lem->instr_len++, "\0");
	}
}
