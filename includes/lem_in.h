/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:00:52 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/29 13:43:30 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define BUFF_SIZE 4096

# define START 0
# define END 1

# define SET_NB_ANTS 0
# define SET_ROOMS 1
# define SET_LINKS 2

# define INT_MAX 2147483647

# define ERROR -1

typedef struct	s_room
{
	char	*id;
	int		w;
	int		ant_id;
}				t_room;

typedef struct	s_link
{
	int		st;
	int		nd;
}				t_link;

typedef struct	s_plist
{
	t_room			*room;
	struct s_plist	*next;
	struct s_plist	*prev;
}				t_plist;

typedef struct	s_path
{
	char	*id_first;
	int		i_first;
	int		w;
	int		nb_ants;
	int		nb_remaining;
	t_plist	*rooms;
}				t_path;

typedef struct	s_lem
{
	char			*input;
	int				input_len;
	int				nb_rooms;
	int				nb_ants;
	t_room			*rooms;
	int				**o_links;
	char			*instr;
	t_path			*paths;
	unsigned long	instr_len;
	int				count;
}				t_lem;

int				get_options(int *ac, char ***av);

void			count_rooms_and_fill_input(t_lem *lem);

void			initialize_o_links(t_lem *lem);

void			parser(t_lem *lem);
int				set_rooms(t_lem *lem, char *str, int current_room);
int				set_nb_ants(t_lem *lem, char *str);
int				setup_o_links(t_lem *lem, char *str);

void			send_all_ants(t_lem *lem);

void			find_paths(t_lem *lem);
int				bfs(t_lem *lem);
void			set_ants_per_room(t_lem *lem, t_path *paths);

t_plist			*new_link(t_room *current);
void			delete_list(t_plist **list);
t_plist			*add_link(t_plist *link, t_plist *list);

int				in(int index);
int				out(int index);

void			error(t_lem *lem);
void			end(t_lem *lem);
void			pre_init_error(t_lem lem);
void			free_path(t_path **paths);

void			send_ants(t_lem *lem);
void			add_nbr_str(t_lem *lem, int nb, unsigned long *start);
void			set_paths_to_start(t_path *paths);

void			print_line_count(t_lem lem);
void			print_paths(t_lem lem);
void			print_ant_nb(t_lem lem);
void			print_ants_per_room(t_lem lem);

#endif
