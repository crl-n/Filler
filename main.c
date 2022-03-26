/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 10:12:58 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/27 00:40:31 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
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
			printf("GOT PLAYER NUMBER %d\n", info->player);
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
	ft_putstr(line);
	info->nrows = ft_atoi(ft_strchr(line, ' ') + 1);
	info->ncols = ft_atoi(ft_strrchr(line, ' ') + 1);
	ft_putstr("\nNROWS ");
	ft_putnbr(info->nrows);
	ft_putstr("\nNCOLS ");
	ft_putnbr(info->ncols);
	ft_putstr("\n");
	ft_strdel(&line);
}

void	get_map_info(t_info *info)
{
	int		gnl_ret;
	int		i;
	char	*line;

	skip_line();
	line = NULL;
	i = 0;
	while (i < info->nrows)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 1)
			break ;
		ft_strcpy(info->map[i], ft_strstr(line, " ") + 1);
		printf("MAP LINE: %s\n", info->map[i]);
		ft_strdel(&line);
		i++;
	}
}

void	get_piece_info(t_piece *piece)
{
	int		gnl_ret;
	int		i;
	char	*line;

	line = NULL;
	gnl_ret = get_next_line(0, &line);
	if (gnl_ret < 1)
		return ;
	free_string_array(piece->data, piece->rows, piece->cols);
	printf("PIECE DIMENSIONS %s\n", line);
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
		printf("PIECE LINE: %s\n", line);
		ft_strncpy(piece->data[i], line, piece->cols);
		printf("PIECE LINE (DATA): %s\n", piece->data[i]);
		ft_strdel(&line);
		i++;
	}
}

int	main(void)
{
	t_info	*info;
	t_piece	*piece;

	info = new_info();
	piece = new_piece();
	info->fd = open("temp", O_TRUNC | O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (info->fd < 0)
		return (0);
	get_player_number(info);
	if (info->player == 1)
		skip_opponent_info(info);
	get_map_dimensions(info);
	info->map = new_string_array(info->nrows, info->ncols);
	while (1)
	{
		get_map_info(info);
		get_piece_info(piece);
		skip_opponent_info(info);
		break ;
	}
	return (0);
}
