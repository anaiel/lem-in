/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rooms_and_ants.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:38:30 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/02 11:47:55 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int			set_nb_ants(t_lem *lem, char *str)
{
	int		i;

	i = -1;
	while (str[++i] && str[i] != '\n')
		if (!ft_isdigit(str[i]))
			return (-1);
	if (i == 0 || (lem->nb_ants = ft_atoi(str)) <= 0)
		return (-1);
	return (1);
}

static void	update_min_max(t_lem *lem, int current_room)
{
	if (lem->x_min > lem->rooms[current_room].x)
		lem->x_min = lem->rooms[current_room].x;
	if (lem->x_max < lem->rooms[current_room].x)
		lem->x_max = lem->rooms[current_room].x;
	if (lem->y_min > lem->rooms[current_room].y)
		lem->y_min = lem->rooms[current_room].y;
	if (lem->y_max < lem->rooms[current_room].y)
		lem->y_max = lem->rooms[current_room].y;
}

static int	is_room(char *str, int i, t_lem *lem, int current_room)
{
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	(lem->rooms + current_room)->y = ft_atoi(str + i + 1);
	if (i < 0 || str[i--] != ' ')
		return (-1);
	if (i < 0 || str[i] < '0' || str[i] > '9')
		return (-1);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	(lem->rooms + current_room)->x = ft_atoi(str + i + 1);
	if (i < 0 || str[i--] != ' ')
		return (-1);
	if (i < 0)
		return (-1);
	update_min_max(lem, current_room);
	return (i);
}

int			set_rooms(t_lem *lem, char *str, int current_room)
{
	int		i;
	int		i_end_id;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if ((i_end_id = is_room(str, i - 1, lem, current_room)) == -1
			&& current_room != lem->nb_rooms - 1)
		return (-1);
	if (!(lem->rooms[current_room].id = ft_strsub(str, 0, i_end_id + 1)))
		error(lem);
	i = -1;
	while (++i < current_room)
		if (ft_strequ(lem->rooms[i].id, lem->rooms[current_room].id))
			error(lem);
	lem->rooms[current_room].is_full = 0;
	lem->rooms[current_room].w = 0;
	return (1);
}
