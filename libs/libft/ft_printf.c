/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwinder <rwinder@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:37 by rwinder          #+#    #+#             */
/*   Updated: 2023/09/04 17:34:49 by rwinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_nbr(int nbr)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(nbr);
	len = ft_print_str(num);
	free(num);
	return (len);
}

int	ft_formats(va_list args, const char format)
{
	int	added_print_len;

	added_print_len = 0;
	if (format == 'c')
		added_print_len += ft_print_char(va_arg(args, int));
	else if (format == 's')
		added_print_len += ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		added_print_len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		added_print_len += ft_print_nbr(va_arg(args, int));
	else if (format == 'u')
		added_print_len += ft_print_unsigned_int(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		added_print_len += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		added_print_len += ft_print_percent();
	return (added_print_len);
}

int	ft_printf(const char *str, ...)
{
	int		printed_lenght;
	int		i;
	va_list	args;

	i = 0;
	printed_lenght = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			printed_lenght += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			printed_lenght += ft_print_char(str[i]);
		i++;
	}
	return (printed_lenght);
}
