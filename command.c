/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:08:42 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/22 18:01:28 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

void	send_command(t_info *info, t_pos *pos)
{
	ft_putnbr(pos->y - info->piece->row_offset);
	ft_putchar(' ');
	ft_putnbr(pos->x - info->piece->col_offset);
	ft_putchar('\n');
}
