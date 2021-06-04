/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 13:33:16 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/01 12:54:15 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_countchr(const char *s, int c)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			q++;
		i++;
	}
	return (q);
}
