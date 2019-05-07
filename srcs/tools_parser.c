/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:16:52 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/29 13:29:59 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Checks if the information in str is compatible with a room line,
** starting from the last character. It returns the index of the first
** character which is not a space or a coordinate and is therefore the
** end of the name of the room.
*/

static int	is_room(char *str, int i)
{
	if (str[i] < '0' || str[i] > '9')
		return (ERROR);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (ERROR);
	if (i < 0 || str[i] < '0' || str[i] > '9')
		return (ERROR);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (ERROR);
	if (i < 0)
		return (ERROR);
	return (i);
}

/*
** Stores the name of the room if the line's characteristics are compatible
** with the definition of a room, and checks if the name already exists (in
** which case is returns an error).
*/

int			set_rooms(t_lem *lem, char *str, int current_room)
{
	int		i;
	int		i_end_id;

	if (!str || !*str)
		error(lem);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if ((i_end_id = is_room(str, i - 1)) == ERROR)
		return (ERROR);
	if (!(lem->rooms[current_room].id = ft_strsub(str, 0, i_end_id + 1)))
		return (ERROR);
	i = -1;
	while (++i < current_room)
		if (ft_strequ(lem->rooms[i].id, lem->rooms[current_room].id))
			return (ERROR);
	lem->o_links[in(current_room)][out(current_room)] = 1;
	lem->o_links[out(current_room)][in(current_room)] = 1;
	return (1);
}

/*
** Stores the number of ants if the characteristics of the line are compatible
** with the definition of the number of ants. If the number of ants is 0,
** returns an error.
*/

int			set_nb_ants(t_lem *lem, char *str)
{
	int				i;
	unsigned int	nb_ants;

	nb_ants = 0;
	i = -1;
	while (str[++i] && str[i] != '\n')
		if (!ft_isdigit(str[i]))
			return (ERROR);
		else
		{
			nb_ants = nb_ants * 10 + str[i] - '0';
			if (nb_ants > INT_MAX)
				return (ERROR);
		}
	if (i == 0 || (lem->nb_ants = (int)nb_ants) == 0)
		return (ERROR);
	return (1);
}
