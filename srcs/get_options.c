/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:04:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/29 11:54:04 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_map_rules(void)
{
	ft_putstr("======================== MAP RULES ========================\n");
	ft_putstr("Maps should contain the following information in order:\n");
	ft_putstr("\t1/ The number of ants, between 1 and 2147483647.\n");
	ft_putstr("\t2/ The rooms and their coordinates (separated with a\n");
	ft_putstr("\t   single space). Rooms may not have the same name and\n");
	ft_putstr("\t   may not start with 'L'. Two of the rooms should be\n");
	ft_putstr("\t   denoted as the starting and ending rooms by being\n");
	ft_putstr("\t   preceded (on the previous line) with the commands\n");
	ft_putstr("\t   '##start' and '##end' respectively.\n");
	ft_putstr("\t3/ The links between the rooms, written as the name of\n");
	ft_putstr("\t   the two rooms separated with a '-', without spaces.\n");
	ft_putstr("There should not be any empty lines.\n");
	ft_putstr("Lines starting with '#' are ignored.\n");
	ft_putstr("If 1 and 2 are not valid, or if there is no path between\n");
	ft_putstr("end  and start, the program will return an error. If one\n");
	ft_putstr("link is invalid, the program will stop reading the map and\n");
	ft_putstr("only take the information it has already read into account.\n");
	exit(0);
}

static void	print_help(void)
{
	ft_putstr("usage: ./lem-in [options] [< file]\n");
	ft_putstr("available options:\n");
	ft_putstr("\t--silent: do not print the regular output of the program\n");
	ft_putstr("\t--show-paths: prints the name of the rooms in the paths the ");
	ft_putstr("ants follow\n");
	ft_putstr("\t--line-count: prints the number of lines of instructions ");
	ft_putstr("necessary for all the ants to get to the end room\n");
	ft_putstr("\t--ant-number: prints the number of ants\n");
	ft_putstr("\t--ants-per-room: prints how many ants are sent in each ");
	ft_putstr("path\n");
	ft_putstr("\t--full-info: activates --line-count --ants-per-room ");
	ft_putstr("--ant-number\n");
	ft_putstr("\t--help: you are here\n");
	exit(0);
}

static void	add_option(int *options, char c)
{
	if (c < 'a' || c > 'z')
		return ;
	*options += (*options & (1 << (c - 'a'))) ? 0 : 1 << (c - 'a');
}

static int	apply_option(char *av, int *options)
{
	if (ft_strequ(av, "silent"))
		add_option(options, 's');
	else if (ft_strequ(av, "show-paths"))
		add_option(options, 'p');
	else if (ft_strequ(av, "line-count"))
		add_option(options, 'l');
	else if (ft_strequ(av, "ant-number"))
		add_option(options, 'a');
	else if (ft_strequ(av, "ants-per-room"))
		add_option(options, 'r');
	else if (ft_strequ(av, "help"))
		print_help();
	else if (ft_strequ(av, "map-rules"))
		print_map_rules();
	else if (ft_strequ(av, "full-info"))
	{
		add_option(options, 'l');
		add_option(options, 'a');
		add_option(options, 'r');
	}
	else
		return (ERROR);
	return (0);
}

/*
** Checks program parameters againts a number of available commands. The
** different options are stored as an activated bit in an int.
*/

int			get_options(int *ac, char ***av)
{
	int		options;

	options = 0;
	(*ac)--;
	(*av)++;
	while (*ac)
	{
		if (!ft_strnequ(**av, "--", 2))
			return (-1);
		else
		{
			**av += 2;
			if (apply_option(**av, &options))
				return (ERROR);
		}
		(*ac)--;
		(*av)++;
	}
	return (options);
}
