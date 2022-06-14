/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:55:30 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/14 10:43:14 by cnysten          ###   ########.fr       */
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
			die(info, ERROR_MAP_INFO);
		ft_strcpy(info->map[i], ft_strstr(line, " ") + 1);
		ft_strdel(&line);
		i++;
	}
}

void	get_piece_info(t_piece *piece, t_info *info, int i)
{
	int		gnl_ret;
	char	*line;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		die(info, ERROR_PIECE_INFO);
	free_string_array(piece->data, piece->rows, piece->cols);
	piece->data = NULL;
	piece->rows = ft_atoi(ft_strchr(line, ' ') + 1); // Seg on invalid input
	piece->cols = ft_atoi(ft_strrchr(line, ' ') + 1);
	ft_strdel(&line);
	piece->data = new_string_array(piece->rows, piece->cols);
	if (!piece->data)
		die(info, ERROR_PIECE_INFO);
	while (i < piece->rows)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 1)
			die(info, ERROR_PIECE_INFO);
		ft_strncpy(piece->data[i], line, piece->cols);
		ft_strdel(&line);
		i++;
	}
}
