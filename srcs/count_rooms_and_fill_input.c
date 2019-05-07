/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_rooms_and_fill_input.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:56:17 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 14:50:19 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*add_buffer(t_lem *lem, char *buff, int rval)
{
	int	i;

	if (!(lem->input = ft_char_realloc(lem->input, sizeof(char)
					* (lem->input_len + rval))))
		return (NULL);
	i = -1;
	while (buff[++i] && i < rval)
		lem->input[lem->input_len + i] = buff[i];
	lem->input[lem->input_len + i] = '\0';
	lem->input_len += rval;
	return (lem->input);
}

/*
** Checks if the line preceding the '\n' in the input is a room with its
** coordinates by checking each character from the end to the start.
*/

static int	is_room(char *str, int i)
{
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (0);
	if (i < 0 || str[i] < '0' || str[i] > '9')
		return (0);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (0);
	if (i < 0)
		return (0);
	return (1);
}

/*
** Stores the input in a string and counts the number of rooms.
*/

void		count_rooms_and_fill_input(t_lem *lem)
{
	int		i;
	int		stop;
	int		rval;
	char	buff[BUFF_SIZE + 1];

	stop = -1;
	lem->input_len = 0;
	while ((rval = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[rval] = 0;
		i = lem->input_len - 1;
		lem->input = add_buffer(lem, buff, rval);
		while (stop < 1 && lem->input[++i])
			if (lem->input[i] == '#')
				while (lem->input[i] && lem->input[i] != '\n')
					i++;
			else if (lem->input[i] == '\n')
			{
				if (stop != -1 && is_room(lem->input, i - 1))
					lem->nb_rooms++;
				else
					stop += 1;
			}
	}
	lem->nb_rooms = (rval < 0) ? 0 : lem->nb_rooms;
}
