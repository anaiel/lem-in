/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_realloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:22:18 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/03 19:23:53 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_char_realloc(char *ptr, size_t size)
{
	char	*p;

	if (ptr && size == 0)
	{
		if (!(p = (char *)malloc(sizeof(char))))
			return (NULL);
		*p = 0;
	}
	else
	{
		if (!(p = ft_strnew(size)))
			return (NULL);
		p = ft_strncpy(p, ptr, size);
	}
	ft_strdel(&ptr);
	return (p);
}
