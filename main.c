/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 10:12:58 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/27 12:27:39 by carlnysten       ###   ########.fr       */
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
	while (y < info->nrows)
	{
		x = 0;
		while (x < info->ncols)
		{
			if (info->map[y][x] == c)
				return (new_pos(x, y));
		}
		y++;
	}
	return (NULL);
}

void	think(t_info *info, t_piece *piece)
{
	(void) piece;
	if (!info->prev)
		info->prev = find_in_map(info, player_symbol_lower(info->player));
	printf("%d %d\n", info->prev->x + 1, info->prev->y + 1);
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
	info->heat = new_heatmap(info->nrows, info->ncols);
	while (1)
	{
		get_map_info(info);
		get_piece_info(piece, info);
		think(info, piece);
		//output_command(info);
		skip_opponent_info(info);
		break ;
	}
	return (0);
}
