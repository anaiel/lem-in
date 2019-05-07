/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_start_end_ant_nb.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:00:57 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/10 17:21:24 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	count_start(t_lem *lem, int step, int i, int count)
{
	int		j;

	while (lem->instr[step][++i].ant_id)
	{
		j = -1;
		while (lem->instr[START][++j].ant_id)
			if (lem->instr[step][i].i_room == lem->instr[START][j].i_room)
				count++;
	}
	lem->rooms[START].ant_nb -= count;
}

static void	set_start_end_ant_nb(t_lem *lem, int step, int anim_step)
{
	int		i;
	int		count;

	if (step == -1)
	{
		lem->rooms[START].ant_nb = lem->nb_ants;
		lem->rooms[END].ant_nb = 0;
		return ;
	}
	i = -1;
	count = 0;
	if (anim_step == DIV_ANIM)
		count_start(lem, step, i, count);
	else if (anim_step == 0)
	{
		while (lem->instr[step][++i].ant_id)
			if (lem->instr[step][i].i_room == END)
				count++;
		lem->rooms[END].ant_nb += count;
	}
}

static void	draw_start_nb(t_lem *lem, SDL_Rect text_pos)
{
	SDL_Surface	*text_surf;
	SDL_Texture *text_text;
	char		*res;

	if (!(res = ft_itoa(lem->rooms[START].ant_nb)))
		error(lem);
	if (!(text_surf = TTF_RenderText_Shaded(lem->visual.font,
					res, lem->visual.colors[WHITE],
					lem->visual.colors[BLACK])))
	{
		ft_strdel(&res);
		error(lem);
	}
	ft_strdel(&res);
	text_pos.x = lem->rooms[START].x + 20;
	text_pos.y = lem->rooms[START].y + 10;
	text_text = SDL_CreateTextureFromSurface(lem->visual.rend, text_surf);
	if (!text_text)
		error(lem);
	SDL_FreeSurface(text_surf);
	if (SDL_RenderCopy(lem->visual.rend, text_text, NULL, &text_pos))
		error(lem);
	SDL_DestroyTexture(text_text);
}

static void	draw_end_nb(t_lem *lem, SDL_Rect text_pos)
{
	SDL_Surface	*text_surf;
	SDL_Texture *text_text;
	char		*res;

	if (!(res = ft_itoa(lem->rooms[END].ant_nb)))
		error(lem);
	if (!(text_surf = TTF_RenderText_Shaded(lem->visual.font,
					res, lem->visual.colors[WHITE],
					lem->visual.colors[BLACK])))
	{
		ft_strdel(&res);
		error(lem);
	}
	ft_strdel(&res);
	text_pos.x = lem->rooms[END].x + 20;
	text_pos.y = lem->rooms[END].y + 20;
	text_text = SDL_CreateTextureFromSurface(lem->visual.rend, text_surf);
	SDL_FreeSurface(text_surf);
	if (!text_text)
		error(lem);
	if (SDL_RenderCopy(lem->visual.rend, text_text, NULL, &text_pos))
		error(lem);
	SDL_DestroyTexture(text_text);
}

void		draw_start_end_ant_nb(t_lem *lem, int step, int anim_step)
{
	SDL_Rect	text_pos;

	set_start_end_ant_nb(lem, step, anim_step);
	text_pos.h = 30;
	text_pos.w = 30;
	draw_start_nb(lem, text_pos);
	draw_end_nb(lem, text_pos);
}
