/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:58:18 by vlow              #+#    #+#             */
/*   Updated: 2025/02/22 17:19:01 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fl_set_precision(const char **c, t_flags *flags);
static void	fl_set_width(const char **c, t_flags *flags);

int	fl_load_fd(int fd, va_list vlist, t_flags *flags)
{
	if (flags->specifier == 'c')
		return (fl_sp_c_fd(fd, vlist, flags));
	else if (flags->specifier == 's')
		return (fl_sp_s_fd(fd, vlist, flags));
	else if (flags->specifier == 'd' || flags->specifier == 'i')
		return (fl_sp_di_fd(fd, vlist, flags));
	else if (flags->specifier == 'u')
		return (fl_sp_u_fd(fd, vlist, flags));
	else if (flags->specifier == 'x' || flags->specifier == 'X')
		return (fl_sp_x_fd(fd, vlist, flags));
	else if (flags->specifier == 'p')
		return (fl_sp_p_fd(fd, vlist, flags));
	return (0);
}

int	fl_set_fd(const char **c, t_flags *flags)
{
	while (*++(*c))
	{
		if (**c == 'c' || **c == 's' || **c == 'p' || **c == 'd' || **c == 'i'
			|| **c == 'u' || **c == 'x' || **c == 'X' || **c == '%')
		{
			flags->specifier = **c;
			return (**c);
		}
		if (**c == '-')
			flags->left_align = 1;
		else if (**c == '0' && !flags->width && flags->precision == -1
			&& !flags->left_align)
			flags->zero_pad = 1;
		else if (**c == ' ')
			flags->space = 1;
		else if (**c == '#')
			flags->hash_hex = 1;
		else if (**c == '+')
			flags->show_sign = 1;
		else if (**c == '.')
			fl_set_precision(c, flags);
		else if (ft_isdigit(**c))
			fl_set_width(c, flags);
	}
	return (0);
}

static void	fl_set_precision(const char **c, t_flags *flags)
{
	if (**c == '.')
		(*c)++;
	if (ft_isdigit(**c))
	{
		flags->precision = ft_atoi(*c);
		while (ft_isdigit(**c))
			(*c)++;
		(*c)--;
	}
	else
	{
		flags->precision = 0;
		(*c)--;
	}
}

static void	fl_set_width(const char **c, t_flags *flags)
{
	if (**c >= '1' && **c <= '9')
	{
		flags->width = ft_atoi(*c);
		while (ft_isdigit(**c))
			(*c)++;
		(*c)--;
	}
}

t_flags	fl_init_fd(void)
{
	t_flags	flags;

	flags.left_align = 0;
	flags.zero_pad = 0;
	flags.hash_hex = 0;
	flags.show_sign = 0;
	flags.space = 0;
	flags.width = 0;
	flags.precision = -1;
	flags.specifier = '\0';
	return (flags);
}
