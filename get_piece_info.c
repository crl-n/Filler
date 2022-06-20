/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_piece_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:50:58 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/20 16:28:44 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "get_next_line.h"

static void	validate_piece_dimensions(t_info *info, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len < 10)
		die(info, ERROR_PIECE_INFO);
	if (ft_strncmp(line, "Piece ", 6) != 0 || line[len - 1] != ':')
		die(info, ERROR_PIECE_INFO);
	line += 6;
	while (*line != ' ')
	{
		if (!ft_isdigit(*line))
			die(info, ERROR_PIECE_INFO);
		line++;
	}
	line++;
	while (*line != ':')
	{
		if (!ft_isdigit(*line))
			die(info, ERROR_PIECE_INFO);
		line++;
	}
}

static void	get_piece_dimensions(t_info *info)
{
	char	*line;
	int		gnl_ret;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		die(info, ERROR_PIECE_INFO);
	validate_piece_dimensions(info, line);
	info->piece->rows = ft_atoi(ft_strchr(line, ' ') + 1);
	info->piece->cols = ft_atoi(ft_strrchr(line, ' ') + 1);
	ft_strdel(&line);
}

static void	get_piece_data(t_info *info)
{
	int		i;
	char	*line;
	int		gnl_ret;

	line = NULL;
	i = 0;
	while (i < info->piece->rows)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 1)
			die(info, ERROR_PIECE_INFO);
		ft_strncpy(info->piece->data[i], line, info->piece->cols);
		ft_strdel(&line);
		i++;
	}
}

// Frees previous piece data and gets the next piece.

void	get_piece_info(t_info *info)
{
	free_string_array(info->piece->data, info->piece->rows,
		info->piece->cols);
	info->piece->data = NULL;
	get_piece_dimensions(info);
	info->piece->data = new_string_array(info->piece->rows,
			info->piece->cols);
	get_piece_data(info);
	if (!info->piece->data)
		die(info, ERROR_PIECE_INFO);
}
