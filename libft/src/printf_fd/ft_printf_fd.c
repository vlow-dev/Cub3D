/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:45:26 by vlow              #+#    #+#             */
/*   Updated: 2025/02/22 17:20:00 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

int		sp_fl_fd(int fd, va_list vlist, const char **fptr);
void	print_flags(t_flags *flags);

int	ft_printf_fd(int fd, const char *format, ...)
{
	int			count;
	va_list		vlist;
	const char	*fptr;

	count = 0;
	fptr = format;
	va_start(vlist, format);
	while (*fptr)
	{
		if (*fptr == '%')
		{
			count += sp_fl_fd(fd, vlist, &fptr);
			fptr++;
		}
		else if (*fptr == '\\')
			count += bs_esc_fd(fd, fptr++);
		else if (*fptr)
		{
			ft_putchar_fd(*fptr++, fd);
			count++;
		}
	}
	va_end(vlist);
	return (count);
}

int	sp_fl_fd(int fd, va_list vlist, const char **fptr)
{
	t_flags	flags;

	flags = fl_init_fd();
	if (!fl_set_fd(fptr, &flags))
		return (0);
	if (flags.specifier == '%')
	{
		ft_putchar_fd('%', fd);
		return (1);
	}
	return (fl_load_fd(fd, vlist, &flags));
}
