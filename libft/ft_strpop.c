/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:19:46 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/17 19:19:46 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpop(char *str, size_t i)
{
	if (str && i <= ft_strlen(str))
	{
		str[i] = 0;
		if (str[i + 1])
			str = ft_fstrjoin(str, &str[i + 1]);
	}
	return (str);
}
