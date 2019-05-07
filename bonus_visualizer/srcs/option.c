/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:05:33 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/10 16:15:01 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	usage(t_lem *lem)
{
	free(lem->option);
	ft_putstr_fd("Only one option is awaited for visualizer.\n", 2);
	exit(0);
}

static void	set_option(t_lem *lem, char **av)
{
	int		i;
	char	*res;

	if (!(res = ft_strdup("/sgoinfre/photos_students/")))
		error(lem);
	if (!(res = ft_char_realloc(res, sizeof(char) * 39)))
		error(lem);
	i = -1;
	while (++i < 4)
		res[26 + i] = av[1][12 + i];
	res[26 + i] = '/';
	i = -1;
	while (av[1][16 + ++i] && i < 8)
		res[31 + i] = av[1][16 + i];
	ft_strcpy(lem->option, res);
	ft_strdel(&res);
	ft_strcat(lem->option, ".JPG");
}

int			get_option(t_lem *lem, int ac, char **av)
{
	if (!(lem->option = (char *)malloc(sizeof(char) * 44)))
		error(lem);
	ft_bzero(lem->option, sizeof(char) * 44);
	if (ac == 1)
		return (0);
	if (ac > 2)
		usage(lem);
	if (av[1][0] == '-' && av[1][1] == '-')
	{
		if (ft_strequ(av[1], "--fancy"))
		{
			lem->option[0] = 'f';
			return (0);
		}
		else if (ft_strnequ(av[1], "--corrector=", 12))
		{
			set_option(lem, av);
			return (0);
		}
		else
			return (-1);
	}
	else
		return (-1);
}
