/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_di_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:12:08 by vlow              #+#    #+#             */
/*   Updated: 2025/02/22 17:04:20 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	fl_if_zero_fd(int fd, t_flags *flags);
static void	fl_if_w_fd(int fd, t_flags *flags, int *pvar);
static void	fl_if_la_fd(int fd, t_flags *flags, int *pvar);
static void	fl_if_ra_fd(int fd, t_flags *flags, int *pvar);

// pvar: 0 = val, 1 = n_len, 2 = p_len, 3 = n_size, 4 = neg.
int	fl_sp_di_fd(int fd, va_list vlist, t_flags *flags)
{
	int	pvar[5];

	pvar[0] = va_arg(vlist, int);
	if (!pvar[0] && !flags->precision)
		return (fl_if_zero_fd(fd, flags));
	pvar[4] = 0;
	pvar[2] = 0;
	if (pvar[0] < 0)
	{
		pvar[4] = 1;
		if (pvar[0] != -2147483648)
			pvar[0] = -pvar[0];
	}
	pvar[1] = ft_countdigits(pvar[0]);
	if (flags->precision > pvar[1])
		pvar[2] = flags->precision - pvar[1];
	flags->buffer = ft_itoa(pvar[0]);
	if (!flags->buffer)
		return (0);
	pvar[3] = pvar[1] + pvar[2] + (pvar[4] || flags->show_sign || flags->space);
	fl_if_w_fd(fd, flags, pvar);
	free(flags->buffer);
	if (flags->width > pvar[3])
		return (flags->width);
	return (pvar[3]);
}

static void	fl_if_w_fd(int fd, t_flags *flags, int *pvar)
{
	if (flags->width > pvar[3])
	{
		if (flags->left_align)
			fl_if_la_fd(fd, flags, pvar);
		else
			fl_if_ra_fd(fd, flags, pvar);
	}
	else
	{
		if (pvar[4])
			ft_putchar_fd('-', fd);
		else if (flags->show_sign)
			ft_putchar_fd('+', fd);
		else if (flags->space)
			ft_putchar_fd(' ', fd);
		if (pvar[2])
			ft_putnchar_fd('0', pvar[2], fd);
		if (pvar[0] == -2147483648)
			ft_putstr_fd("2147483648", fd);
		else
			ft_putstr_fd(flags->buffer, fd);
	}
}

static void	fl_if_la_fd(int fd, t_flags *flags, int *pvar)
{
	if (pvar[4])
		ft_putchar_fd('-', fd);
	else if (flags->show_sign)
		ft_putchar_fd('+', fd);
	else if (flags->space)
		ft_putchar_fd(' ', fd);
	if (pvar[2])
		ft_putnchar_fd('0', pvar[2], fd);
	if (pvar[0] == -2147483648)
		ft_putstr_fd("2147483648", fd);
	else
		ft_putstr_fd(flags->buffer, fd);
	ft_putnchar_fd(' ', flags->width - pvar[3], fd);
}

static void	fl_if_ra_fd(int fd, t_flags *flags, int *pvar)
{
	if (flags->precision >= 0 || !flags->zero_pad)
		ft_putnchar_fd(' ', flags->width - pvar[3], fd);
	if (pvar[4])
		ft_putchar_fd('-', fd);
	else if (flags->show_sign)
		ft_putchar_fd('+', fd);
	else if (flags->space)
		ft_putchar_fd(' ', fd);
	if (pvar[2])
		ft_putnchar_fd('0', pvar[2], fd);
	else if (flags->zero_pad && flags->precision == -1)
		ft_putnchar_fd('0', flags->width - pvar[3], fd);
	if (pvar[0] == -2147483648)
		ft_putstr_fd("2147483648", fd);
	else
		ft_putstr_fd(flags->buffer, fd);
}

static int	fl_if_zero_fd(int fd, t_flags *flags)
{
	if (flags->width)
	{
		ft_putnchar_fd(' ', flags->width, fd);
		return (flags->width);
	}
	return (0);
}
