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

char	*ft_strjoin(char *s1, char *s2)
{
	int		n;
	int		i;
	char	*newstr;

	n = 0;
	i = 0;
	newstr = malloc(sizeof(*newstr) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	while (s1[n])
	{
		newstr[n] = s1[n];
		n++;
	}
	while (s2[i])
	{
		newstr[n + i] = s2[i];
		i++;
	}
	newstr[n + i] = 0;
	return (newstr);
}
