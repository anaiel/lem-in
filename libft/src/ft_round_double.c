/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:01:58 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/18 17:09:58 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_round_double(double n)
{
	if (n >= 2147483647.5 || n <= -2147483648.5)
		return (0);
	if (n >= 0)
	{
		if ((double)(n - (int)n) >= 0.5)
			return ((int)n + 1);
		else
			return ((int)n);
	}
	else
	{
		if ((double)(n - (int)n) <= -0.5)
			return ((int)n - 1);
		else
			return ((int)n);
	}
}
