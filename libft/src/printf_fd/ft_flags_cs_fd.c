/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_cs_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:24:32 by vlow              #+#    #+#             */
/*   Updated: 2025/02/22 17:01:15 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fl_if_w_fd(int fd, t_flags *flags, char *s, int s_len);

int	fl_sp_c_fd(int fd, va_list vlist, t_flags *flags)
{
	char	c;

	c = (char)va_arg(vlist, int);
	if (flags->width)
	{
		if (flags->left_align)
		{
			ft_putchar_fd(c, fd);
			ft_putnchar_fd(' ', flags->width - 1, fd);
		}
		else
		{
			ft_putnchar_fd(' ', flags->width - 1, fd);
			ft_putchar_fd(c, fd);
		}
		return (flags->width);
	}
	else
	{
		ft_putchar_fd(c, fd);
		return (1);
	}
}

int	fl_sp_s_fd(int fd, va_list vlist, t_flags *flags)
{
	char	*s;
	int		s_len;

	s = va_arg(vlist, char *);
	if (!s)
	{
		if (flags->precision == -1 || flags->precision >= 6)
			s = "(null)";
		else
			s = "";
	}
	s_len = (int)ft_strlen(s);
	if (flags->precision >= 0 && flags->precision < s_len)
		s_len = flags->precision;
	return (fl_if_w_fd(fd, flags, s, s_len));
}

static int	fl_if_w_fd(int fd, t_flags *flags, char *s, int s_len)
{
	if (flags->width > s_len)
	{
		if (flags->left_align)
		{
			ft_putnstr_fd(s, s_len, fd);
			ft_putnchar_fd(' ', flags->width - s_len, fd);
		}
		else
		{
			ft_putnchar_fd(' ', flags->width - s_len, fd);
			ft_putnstr_fd(s, s_len, fd);
		}
		return (flags->width);
	}
	else
	{
		ft_putnstr_fd(s, s_len, fd);
		return (s_len);
	}
}
