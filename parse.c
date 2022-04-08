/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:55:30 by carlnysten        #+#    #+#             */
/*   Updated: 2022/04/08 10:55:58 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

void	get_player_number(t_info *info)
{
	int		player_known;
	int		gnl_ret;
	char	*line;

	line = NULL;
	player_known = 0;
	while (!player_known)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 1)
			break ;
		if (ft_strstr(line, "cnysten.filler"))
		{
			info->player = ft_atoi(ft_strchr(line, 'p') + 1);
			dprintf(info->fd, "GOT PLAYER NUMBER %d\n", info->player);
			info->opponent = (info->player == 1) + 1;
			dprintf(info->fd, "GOT OPPONENT NUMBER %d\n", info->opponent);
			player_known = 1;
		}
		ft_strdel(&line);
	}
}

void	get_map_dimensions(t_info *info)
{
	int		gnl_ret;
	char	*line;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		return ;
	info->nrows = ft_atoi(ft_strchr(line, ' ') + 1);
	info->ncols = ft_atoi(ft_strrchr(line, ' ') + 1);
	info->center = new_pos((info->nrows - 1) / 2, (info->ncols - 1) / 2);
	dprintf(info->fd, "GOT NROWS %d\n", info->nrows);
	dprintf(info->fd, "GOT NCOLS %d\n", info->ncols);
	dprintf(info->fd, "GOT CENTER %d %d\n", info->center->y, info->center->x);
	ft_strdel(&line);
}

void	get_map_info(t_info *info)
{
	int		gnl_ret;
	int		i;
	char	*line;

	skip_line(info);
	line = NULL;
	i = 0;
	while (i < info->nrows)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 1)
			break ;
		ft_strcpy(info->map[i], ft_strstr(line, " ") + 1);
		dprintf(info->fd, "MAP LINE %3d: %s\n", i, info->map[i]);
		ft_strdel(&line);
		i++;
	}
}

void	get_piece_info(t_piece *piece, t_info *info)
{
	int		gnl_ret;
	int		i;
	char	*line;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		return ;
	free_string_array(piece->data, piece->rows, piece->cols);
	piece->data = NULL;
	dprintf(info->fd, "PIECE DIMENSIONS %s\n", line);
	piece->rows = ft_atoi(ft_strchr(line, ' ') + 1);
	piece->cols = ft_atoi(ft_strrchr(line, ' ') + 1);
	ft_strdel(&line);
	piece->data = new_string_array(piece->rows, piece->cols);
	i = 0;
	while (i < piece->rows)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 1)
			break ;
		dprintf(info->fd, "PIECE LINE %3d: %s\n", i, line);
		ft_strncpy(piece->data[i], line, piece->cols);
		//dprintf(info->fd, "PIECE LINE (DATA): %s\n", piece->data[i]);
		ft_strdel(&line);
		i++;
	}
	dprintf(info->fd, "EXITING GET_PIECE_INFO\n");
}
