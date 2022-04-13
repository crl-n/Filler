/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:08:42 by carlnysten        #+#    #+#             */
/*   Updated: 2022/04/13 21:23:29 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

void	send_command(t_pos *pos)
{
	ft_putnbr(pos->y);
	ft_putchar(' ');
	ft_putnbr(pos->x);
	ft_putchar('\n');
}
