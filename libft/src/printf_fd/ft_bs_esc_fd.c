/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bs_esc_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:42:55 by vlow              #+#    #+#             */
/*   Updated: 2025/02/22 16:02:40 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	bs_helper1_fd(int fd, const char *fptr);

int	bs_esc_fd(int fd, const char *fptr)
{
	if (*fptr == 'n' )
		ft_putchar_fd('\n', fd);
	else if (*fptr == 't')
		ft_putchar_fd('\t', fd);
	else if (*fptr == 'r')
		ft_putchar_fd('\r', fd);
	else if (*fptr == 'b')
		ft_putchar_fd('\b', fd);
	else if (*fptr == 'f')
		ft_putchar_fd('\f', fd);
	else if (*fptr == 'v')
		ft_putchar_fd('\v', fd);
	else if (*fptr == 'a')
		ft_putchar_fd('\a', fd);
	else if (*fptr == '\\')
		ft_putchar_fd('\\', fd);
	else if (*fptr == '\'')
		ft_putchar_fd('\'', fd);
	else if (*fptr == '\"')
		ft_putchar_fd('\"', fd);
	else if (*fptr == '?')
		ft_putchar_fd('?', fd);
	else
		return (bs_helper1_fd(fd, fptr));
	return (1);
}

static int	bs_helper1_fd(int fd, const char *fptr)
{
	ft_putchar_fd('\\', fd);
	ft_putchar_fd(*fptr, fd);
	return (2);
}
