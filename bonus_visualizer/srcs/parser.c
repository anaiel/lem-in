/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:48:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/02 11:51:56 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	detect_command(t_lem *lem, int *i, int parse_step)
{
	if (ft_strnequ(lem->input + *i, "##start\n", 8))
	{
		*i += 8;
		if (parse_step != SET_ROOMS || lem->rooms[START].id
				|| (set_rooms(lem, lem->input + *i, START)) == ERROR)
			error(lem);
	}
	else if (ft_strnequ(lem->input + *i, "##end\n", 6))
	{
		*i += 6;
		if (parse_step != SET_ROOMS || lem->rooms[END].id
				|| (set_rooms(lem, lem->input + *i, END)) == -1)
			error(lem);
	}
}

static void	manage_rooms(t_lem *lem, int i)
{
	static int	current_room = END + 1;

	if ((lem->parse_step = set_rooms(lem, lem->input + i, current_room))
			== ERROR)
		error(lem);
	if (++current_room == lem->nb_rooms)
		lem->parse_step = SET_LINKS;
}

static void	set_ants_or_instr(t_lem *lem, int *i, int mode)
{
	static int	i_visu = -1;

	if (mode == ANTS)
	{
		if ((lem->parse_step = set_nb_ants(lem, lem->input + *i)) == ERROR)
			error(lem);
		if (!(lem->ants = (t_ant *)malloc(sizeof(t_ant) * (lem->nb_ants + 1))))
			error(lem);
		ft_bzero(lem->ants, sizeof(t_ant) * (lem->nb_ants + 1));
	}
	else
	{
		if ((lem->parse_step = set_instructions(lem, lem->input + *i, ++i_visu))
				== -1)
			error(lem);
	}
}

static void	parse_line_by_line(t_lem *lem, int *i)
{
	if (lem->input[*i] == '#')
		detect_command(lem, i, lem->parse_step);
	else if (lem->parse_step == SET_NB_ANTS)
		set_ants_or_instr(lem, i, ANTS);
	else if (lem->parse_step == SET_ROOMS && lem->input[*i] != 'L')
		manage_rooms(lem, *i);
	else if (lem->parse_step == SET_LINKS && lem->input[*i] != 'L'
			&& lem->input[*i] != '\n')
		lem->parse_step = fill_adjacency_matrix(lem, lem->input + *i);
	else if (lem->input[*i] == '\n' && lem->input[*i + 1] == 'L')
		lem->parse_step++;
	else if (lem->parse_step != SET_INSTR || lem->input[*i] != 'L')
		error(lem);
	else if (lem->parse_step == SET_INSTR && lem->input[*i] == 'L')
		set_ants_or_instr(lem, i, INSTR);
	else
		lem->parse_step = ERROR;
	if (lem->parse_step == ERROR)
		lem->input[--(*i)] = 0;
	while (lem->input[*i] && lem->input[*i] != '\n')
		(*i)++;
	if (lem->input[*i])
		(*i)++;
}

void		parser(t_lem *lem)
{
	int		i;

	i = 0;
	while (lem->input[i])
		parse_line_by_line(lem, &i);
	set_scale(lem);
	scale(lem);
}
