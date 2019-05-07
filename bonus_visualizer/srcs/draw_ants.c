/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:18:36 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/10 14:47:25 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	draw_ant_id(t_lem *lem, int ant_id, SDL_Rect ant_pos)
{
	char		*id;
	SDL_Surface	*id_surf;
	SDL_Texture	*id_text;

	ant_pos.x += 20;
	ant_pos.h = 15;
	ant_pos.w = 15;
	if (!(id = ft_itoa(ant_id)))
		error(lem);
	if (!(id_surf = TTF_RenderText_Shaded(lem->visual.font, id,
					lem->visual.colors[BLACK], lem->visual.colors[WHITE])))
		error(lem);
	free(id);
	id_text = SDL_CreateTextureFromSurface(lem->visual.rend, id_surf);
	SDL_FreeSurface(id_surf);
	if (!id_text)
		error(lem);
	if (SDL_RenderCopy(lem->visual.rend, id_text, NULL, &ant_pos))
		error(lem);
	SDL_DestroyTexture(id_text);
}

static void	draw_ant_and_id(t_lem *lem, int i, int anim_step)
{
	SDL_Rect	ant_pos;

	ant_pos.h = 25;
	ant_pos.w = 25;
	ant_pos.x = ft_round_double((double)
			(lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].x
			+ ((double)lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].last_x - lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].x) * ((double)anim_step / DIV_ANIM)));
	ant_pos.y = ft_round_double((double)
			(lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].y
			+ ((double)lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].last_y - lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].y) * ((double)anim_step / DIV_ANIM)));
	if (SDL_RenderCopy(lem->visual.rend, lem->visual.ant_text, NULL,
				&ant_pos))
		error(lem);
	if (lem->instr[lem->visual.step][i].i_room != 1 || anim_step != 0)
		draw_ant_id(lem, lem->instr[lem->visual.step][i].ant_id,
				ant_pos);
}

static void	init_ants_pos(t_lem *lem, int *anim_step)
{
	int		i;

	lem->visual.step = -1;
	*anim_step = DIV_ANIM;
	i = -1;
	while (++i < lem->nb_ants)
	{
		lem->ants[i].x = lem->rooms[0].x;
		lem->ants[i].y = lem->rooms[0].y;
		lem->ants[i].last_x = lem->rooms[0].x;
		lem->ants[i].last_y = lem->rooms[0].y;
	}
}

static void	update_pos_and_draw(t_lem *lem, int *anim_step)
{
	int			i;

	i = -1;
	while (lem->visual.step > -1 && lem->instr[lem->visual.step][++i].ant_id)
	{
		if (*anim_step == DIV_ANIM)
		{
			lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].last_x = lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].x;
			lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].last_y = lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].y;
			lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].x = lem->rooms[lem->instr[lem->visual.step][i].i_room].x;
			lem->ants[lem->instr[lem->visual.step][i].ant_id
				- 1].y = lem->rooms[lem->instr[lem->visual.step][i].i_room].y;
		}
		draw_ant_and_id(lem, i, *anim_step);
	}
	--(*anim_step);
}

void		draw_ants(t_lem *lem, SDL_Keycode key)
{
	static int	anim_step = DIV_ANIM;

	if (anim_step == -1)
		anim_step = DIV_ANIM;
	lem->visual.step += (key == SDLK_RIGHT && anim_step == DIV_ANIM) ? 1 : 0;
	if (key == SDLK_SPACE)
		init_ants_pos(lem, &anim_step);
	if (lem->visual.step < -1 || lem->visual.step >= lem->nb_instr)
	{
		lem->visual.step = (lem->visual.step < 0) ? -1 : lem->nb_instr - 1;
		return ;
	}
	if (SDL_RenderCopy(lem->visual.rend, lem->visual.anthill_text, NULL, NULL))
		error(lem);
	if (lem->visual.step != -1)
		update_pos_and_draw(lem, &anim_step);
	draw_start_ants(lem);
	draw_start_end_ant_nb(lem, lem->visual.step, anim_step + 1);
	render_menu(lem);
	SDL_RenderPresent(lem->visual.rend);
}
