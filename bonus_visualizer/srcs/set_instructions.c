/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:23:10 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/10 17:54:59 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	init_instr(t_lem *lem, char *str, int i_visu)
{
	int		i;
	int		count;

	i = -1;
	while (++i < lem->nb_ants)
	{
		lem->ants[i].x = lem->rooms[START].x;
		lem->ants[i].y = lem->rooms[START].y;
	}
	i = -1;
	count = 0;
	while (str[++i] && str[i] != '\n')
		count += (str[i] == 'L') ? 1 : 0;
	if (!(lem->instr[i_visu] = (t_instr *)malloc(sizeof(t_instr)
					* (++count))))
		error(lem);
	while (count--)
	{
		lem->instr[i_visu][count].i_room = 0;
		lem->instr[i_visu][count].ant_id = 0;
	}
}

static int	skip_digits(char *str, int *i)
{
	while (ft_isdigit(str[(*i)++]))
		;
	if (str[--(*i)] != '-')
		return (-1);
	return (0);
}

int			set_instructions(t_lem *lem, char *str, int i_visu)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = -1;
	k = -1;
	init_instr(lem, str, i_visu);
	while (str[++i] && str[i] != '\n')
	{
		if (str[i++] != 'L')
			return (-1);
		lem->instr[i_visu][++k].ant_id = ft_atoi(str + i);
		if (skip_digits(str, &i))
			return (-1);
		count = 0;
		while (str[++i] && str[i] != ' ' && str[i] != '\n')
			count++;
		j = -1;
		while (++j < lem->nb_rooms && !lem->instr[i_visu][k].i_room)
			if (ft_strnequ(lem->rooms[j].id, str + i - count, count))
				lem->instr[i_visu][k].i_room = j;
		i += (str[i] == '\n') ? -1 : 0;
	}
	return (3);
}
