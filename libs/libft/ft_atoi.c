/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwinder <rwinder@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:34:44 by rwinder           #+#    #+#             */
/*   Updated: 2022/10/12 13:51:29 by rwinder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int	ft_atoi(const char *value)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*value && (*value == ' ' || *value == '\n' || *value == '\t'
			|| *value == '\f' || *value == '\r' || *value == '\v'))
	{
		++value;
	}
	if (*value == '-')
	{
		negative = -1;
	}
	if (*value == '-' || *value == '+')
	{
		++value;
	}
	while (*value && *value >= '0' && *value <= '9')
	{
		res = res * 10 + (*value - 48);
		++value;
	}
	return ((int)(res * negative));
}
