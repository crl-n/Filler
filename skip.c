/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:39:39 by carlnysten        #+#    #+#             */
/*   Updated: 2022/04/13 21:29:50 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "get_next_line.h"

void	skip_line(t_info *info)
{
	int		gnl_ret;
	char	*line;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		die(info);
	ft_strdel(&line);
}

void	skip_opponent_info(t_info *info)
{
	int		gnl_ret;
	char	*line;

	line = NULL;
	while (1)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 1)
			die(info);
		if (ft_strstr(line, "got"))
		{
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
}
