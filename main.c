/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 10:12:58 by carlnysten        #+#    #+#             */
/*   Updated: 2022/04/06 14:17:25 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

t_pos	*find_in_map(t_info *info, char c)
{
	int	x;
	int	y;

	y = 0;
	dprintf(info->fd, "FINDING %c IN MAP\n", c);
	while (y < info->nrows)
	{
		x = 0;
		while (x < info->ncols)
		{
			if (info->map[y][x] == c)
			{
				dprintf(info->fd, "FOUND %c AT Y: %d X: %d\n", c, y, x);
				return (new_pos(x, y));
			}
			x++;
		}
		y++;
	}
	dprintf(info->fd, "EXITING FIND_IN_MAP\n");
	return (NULL);
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
	info->heatmap = new_heatmap(info->nrows, info->ncols);
	while (1)
	{
		get_map_info(info);
		update_heatmap(info);
		print_heatmap(info);
		get_piece_info(piece, info);
		think(info, piece);
		skip_line(info);
		//skip_line(info);
		//send_command(info);
		//skip_opponent_info(info);
	}
	return (0);
}
