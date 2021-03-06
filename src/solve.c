/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:59:27 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/30 14:48:16 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

static unsigned int	get_heatsum(int x, int y, t_info *info)
{
	int				i;
	int				j;
	unsigned int	heatsum;

	heatsum = 0;
	i = 0;
	while (i < info->piece.rows && y < info->nrows)
	{
		j = 0;
		while (j < info->piece.cols)
		{
			if (x >= 0 && x < info->ncols && y >= 0
				&& info->piece.data[i][j] == '*')
				heatsum += info->heatmap[y][x];
			x++;
			j++;
		}
		x -= info->piece.cols;
		y++;
		i++;
	}
	return (heatsum);
}

static int	search_map(t_info *info, t_pos *minpos,
				t_bool place_found, unsigned int min_heatsum)
{
	unsigned int	heatsum;
	t_pos			pos;

	pos.y = 0;
	while (pos.y < info->nrows)
	{
		pos.x = 0;
		while (pos.x < info->ncols)
		{
			if (can_place_piece(pos, info, (t_pos){0, 0}, 0))
			{
				place_found = TRUE;
				heatsum = get_heatsum(pos.x, pos.y, info);
				if (heatsum < min_heatsum)
				{
					min_heatsum = heatsum;
					*minpos = (t_pos){pos.x, pos.y};
				}
			}
			pos.x++;
		}
		pos.y++;
	}
	return (place_found);
}

void	solve(t_info *info)
{
	t_pos	pos;
	int		place_found;

	pos = (t_pos){0, 0};
	place_found = FALSE;
	place_found = search_map(info, &pos, FALSE, MAX_HEATSUM);
	send_command(&pos);
	if (!place_found)
		die(info, NULL);
}
