/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:30:33 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 15:46:45 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	usage(void)
{
	ft_putstr_fd("usage: ./visualizer\n", 2);
	ft_putstr_fd("(Nota Bene: visualizer reads the standard input, use ", 2);
	ft_putstr_fd("./lem_in < file | ./visualizer to read the output of ", 2);
	ft_putstr_fd("lem-in with a file)\n", 2);
	ft_putstr_fd("options: [--fancy | --corrector=<YearPseudo>]\n", 2);
	exit(0);
}

int			main(int ac, char **av)
{
	t_lem		lem;
	int			quit;
	int			option;

	ft_bzero(&lem, sizeof(t_lem));
	if ((option = get_option(&lem, ac, av)) == -1)
		usage();
	quit = 0;
	if (!(lem.nb_rooms = count_and_fill_input(&lem)))
		usage();
	initialize_lem(&lem);
	parser(&lem);
	if (SDL_SetRenderDrawColor(lem.visual.rend, BG_R, BG_G, BG_B, BG_A)
			|| SDL_RenderClear(lem.visual.rend))
		error(&lem);
	draw_anthill(&lem);
	if (SDL_RenderCopy(lem.visual.rend, lem.visual.anthill_text, NULL, NULL))
		error(&lem);
	draw_start_ants(&lem);
	draw_start_end_ant_nb(&lem, -1, DIV_ANIM);
	render_menu(&lem);
	SDL_RenderPresent(lem.visual.rend);
	event_manager(&lem);
	end(&lem);
	return (0);
}
