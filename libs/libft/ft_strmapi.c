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
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		n;
	char				*str;

	n = 0;
	if (!s || !f)
		return (NULL);
	str = malloc(sizeof(*str) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[n])
	{
		str[n] = f(n, s[n]);
		n++;
	}
	str[n] = 0;
	return (str);
}
