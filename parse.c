/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:55:30 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/22 11:22:00 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "get_next_line.h"

void	get_player_number(t_info *info)
{
	int		gnl_ret;
	char	*line;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		die(info, ERROR_PLAYER_INFO);
	if (ft_strncmp(line, "$$$ exec p", 10) != 0)
		die(info, ERROR_PLAYER_INFO);
	info->player = ft_atoi(line + 10);
	if (!(info->player == 1 || info->player == 2))
		die(info, ERROR_PLAYER_INFO);
	if (ft_strncmp(line + 11, " : [", 4))
		die(info, ERROR_PLAYER_INFO);
	if (!ft_strstr(line + 12, "cnysten.filler"))
		die(info, ERROR_PLAYER_INFO);
	if (line[ft_strlen(line) - 1] != ']')
		die(info, ERROR_PLAYER_INFO);
	info->opponent = (info->player == 1) + 1;
	ft_strdel(&line);
}

void	get_map_dimensions(t_info *info)
{
	int		gnl_ret;
	char	*line;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		die(info, ERROR_MAP_DIMENSIONS);
	if (ft_strncmp(line, "Plateau ", 8) != 0)
		die(info, ERROR_MAP_DIMENSIONS);
	if (!ft_isdigit(*(line + 8)))
		die(info, ERROR_MAP_DIMENSIONS);
	info->nrows = ft_atoi(line + 8);
	if (info->nrows < 1)
		die(info, ERROR_MAP_DIMENSIONS);
	if (!ft_isdigit(*(line + 9 + ft_intlen(info->nrows))))
		die(info, ERROR_MAP_DIMENSIONS);
	info->ncols = ft_atoi(line + 9 + ft_intlen(info->nrows));
	if (info->ncols < 1)
		die(info, ERROR_MAP_DIMENSIONS);
	if (line[ft_strlen(line) - 1] != ':')
		die(info, ERROR_MAP_DIMENSIONS);
	ft_strdel(&line);
}
