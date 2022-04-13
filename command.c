/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:08:42 by carlnysten        #+#    #+#             */
/*   Updated: 2022/04/13 15:23:51 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

void	send_command(t_info *info)
{
	ft_putnbr(info->cmd->y);
	ft_putchar(' ');
	ft_putnbr(info->cmd->x);
	ft_putchar('\n');
}
