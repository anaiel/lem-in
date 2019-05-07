/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:58:22 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/18 17:05:00 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_plist	*new_link(t_room *current)
{
	t_plist	*link;

	if (!(link = (t_plist *)malloc(sizeof(t_plist))))
		return (NULL);
	link->room = current;
	link->prev = NULL;
	link->next = NULL;
	return (link);
}

void	delete_list(t_plist **list)
{
	t_plist	*current;
	t_plist	*next;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
}

t_plist	*add_link(t_plist *link, t_plist *list)
{
	if (!link)
		return (list);
	if (!list)
		return (link);
	list->next = link;
	link->prev = list;
	return (link);
}
