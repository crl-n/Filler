/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:39:39 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/27 12:28:06 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

void	skip_line(t_info *info)
{
	int		gnl_ret;
	char	*line;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		return ;
	dprintf(info->fd, "SKIPPED: %s\n", line);
	ft_strdel(&line);
}

void	skip_opponent_info(t_info *info)
{
	int		gnl_ret;
	char	*line;

	(void) info;
	line = NULL;
	while (1)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 1)
			break ;
		if (ft_strstr(line, "got"))
		{
			dprintf(info->fd, "STOPPED AT: %s\n", line);
			ft_strdel(&line);
			break ;
		}
		dprintf(info->fd, "SKIPPED: %s\n", line);
		ft_strdel(&line);
	}
}
