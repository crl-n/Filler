/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:39:39 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/27 00:40:50 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdio.h>

void	skip_line(void)
{
	int		gnl_ret;
	char	*line;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		return ;
	printf("SKIPPED: %s\n", line);
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
			printf("STOPPED AT: %s\n", line);
			ft_strdel(&line);
			break ;
		}
		printf("SKIPPED: %s\n", line);
		ft_strdel(&line);
	}
}
