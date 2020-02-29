/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:25:01 by okupin            #+#    #+#             */
/*   Updated: 2017/10/27 18:25:17 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	int		i;
	int		sign;
	float	n;
	float	k;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		++i;
	sign = (str[i] == '-' ? -1 : 1);
	if (str[i] == '-' || str[i] == '+')
		++i;
	if (!(str[i] >= '0' && str[i] <= '9') && \
		(str[i] != '.' || !(str[i + 1] >= '0' && str[i + 1] <= '9')))
		return (0);
	n = 0.0;
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10.0 + (str[i++] - '0');
	if (str[i++] != '.')
		return (n * (float)sign);
	k = 1.0;
	while (str[i] >= '0' && str[i] <= '9' && (k *= 10.0))
		n += ((float)(str[i++] - '0') / k);
	return (n * (float)sign);
}
