/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_x_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:23:58 by vlow              #+#    #+#             */
/*   Updated: 2025/02/22 17:14:15 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdarg.h>

static int	fl_if_zero_fd(int fd, t_flags *flags);
static void	fl_if_la_fd(int fd, t_flags *flags, int *pvar);
static void	fl_if_nw_fd(int fd, t_flags *flags, int *pvar, unsigned int val);
static void	fl_if_w_fd(int fd, t_flags *flags, int *pvar, unsigned int val);

// 0 = n_len, 1 = p_len, 2 = n_size, 3 = pfix.
int	fl_sp_x_fd(int fd, va_list vlist, t_flags *flags)
{
	unsigned int	val;
	int				pvar[4];

	val = va_arg(vlist, unsigned int);
	if (!val && !flags->precision)
		return (fl_if_zero_fd(fd, flags));
	pvar[0] = ft_countdigits_hex(val);
	pvar[1] = 0;
	pvar[3] = 0;
	if (flags->precision > pvar[0])
		pvar[1] = flags->precision - pvar[0];
	if (flags->hash_hex && val != 0)
		pvar[3] = 2;
	pvar[2] = pvar[0] + pvar[1] + pvar[3];
	flags->buffer = ft_itoa_hex(val);
	if (!flags->buffer)
		return (0);
	if (flags->specifier == 'X')
		ft_struppercase(flags->buffer);
	fl_if_w_fd(fd, flags, pvar, val);
	free(flags->buffer);
	if (flags->width > pvar[2])
		return (flags->width);
	return (pvar[2]);
}

static void	fl_if_w_fd(int fd, t_flags *flags, int *pvar, unsigned int val)
{
	if (flags->width > pvar[2])
		fl_if_la_fd(fd, flags, pvar);
	else
		fl_if_nw_fd(fd, flags, pvar, val);
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

static void	fl_if_la_fd(int fd, t_flags *flags, int *pvar)
{
	if (flags->left_align)
	{
		if (pvar[3] && flags->specifier == 'x')
			ft_putstr_fd("0x", fd);
		else if (pvar[3] && flags->specifier == 'X')
			ft_putstr_fd("0X", fd);
		if (pvar[1])
			ft_putnchar_fd('0', pvar[1], fd);
		ft_putstr_fd(flags->buffer, fd);
		ft_putnchar_fd(' ', flags->width - pvar[2], fd);
	}
	else
	{
		if (flags->precision >= 0 || !flags->zero_pad)
			ft_putnchar_fd(' ', flags->width - pvar[2], fd);
		if (pvar[3] && flags->specifier == 'x')
			ft_putstr_fd("0x", fd);
		else if (pvar[3] && flags->specifier == 'X')
			ft_putstr_fd("0X", fd);
		if (pvar[1])
			ft_putnchar_fd('0', pvar[1], fd);
		else if (flags->zero_pad && flags->precision == -1)
			ft_putnchar_fd('0', flags->width - pvar[2], fd);
		ft_putstr_fd(flags->buffer, fd);
	}
}

static void	fl_if_nw_fd(int fd, t_flags *flags, int *pvar, unsigned int val)
{
	if (pvar[3] && val != 0 && flags->specifier == 'x')
		ft_putstr_fd("0x", fd);
	else if (pvar[3] && val != 0 && flags->specifier == 'X')
		ft_putstr_fd("0X", fd);
	if (pvar[1])
		ft_putnchar_fd('0', pvar[1], fd);
	ft_putstr_fd(flags->buffer, fd);
}
