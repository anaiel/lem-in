/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_and_fill_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:42:17 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/10 17:37:36 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	add_buffer(t_lem *lem, char *buff, int rd_size)
{
	if (!(lem->input = ft_char_realloc(lem->input, sizeof(char)
					* (ft_strlen(lem->input) + rd_size))))
		error(lem);
	lem->input = ft_strncat(lem->input, buff, rd_size);
}

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

static void	count_rooms(t_lem *lem, int *i, int *flag, int *count)
{
	if (lem->input[*i] == '#')
		while (lem->input[*i] && lem->input[*i] != '\n')
			(*i)++;
	else if (lem->input[*i] == '\n')
	{
		if (*flag == -1)
			*flag = 0;
		else if (is_room(lem->input, *i - 1))
			(*count)++;
		else
			*flag = 1;
	}
}

static void	count_instr(t_lem *lem, int i, int *flag)
{
	while (lem->input[++i])
		if (lem->input[i] != '\n' && lem->input[i + 1] != '\n'
				&& (*flag = 2))
			break ;
	while (*flag == 2 && lem->input[++i])
		if (lem->input[i] == '\n' && lem->input[i + 1] == 'L')
			lem->nb_instr++;
}

int			count_and_fill_input(t_lem *lem)
{
	int		i;
	int		count;
	int		flag;
	int		rd_size;
	char	buff[BUFF_SIZE + 1];

	rd_size = 0;
	count = 0;
	flag = -1;
	lem->input = NULL;
	while ((rd_size = read(0, buff, BUFF_SIZE)) > 0)
		add_buffer(lem, buff, rd_size);
	i = -1;
	if (!lem->input)
	{
		ft_putstr_fd("Nothing to read.\n", 2);
		error(lem);
	}
	while ((flag == 0 || flag == -1) && lem->input[++i])
		count_rooms(lem, &i, &flag, &count);
	count_instr(lem, i, &flag);
	count = (rd_size < 0) ? 0 : count;
	return (count);
}
