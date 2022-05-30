/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:31:03 by carlnysten        #+#    #+#             */
/*   Updated: 2022/05/30 15:31:02 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

// TODO
// Make it work with negative indices

int	can_place_piece(t_pos mpos, t_info *info, t_piece *piece, int overlap)
{
	t_pos	ppos;

	ppos.y = 0;
	while (ppos.y < piece->rows)
	{
		if (mpos.y >= info->nrows)
			return (0);
		ppos.x = 0;
		while (ppos.x < piece->cols)
		{
			if (mpos.x >= info->ncols
				|| (is_player(info->map[mpos.y][mpos.x], info->opponent)
				&& piece->data[ppos.y][ppos.x] == '*'))
				return (0);
			if (is_player(info->map[mpos.y][mpos.x], info->player)
				&& piece->data[ppos.y][ppos.x] == '*')
				overlap++;
			mpos.x++;
			ppos.x++;
		}
		mpos.x -= piece->cols;
		mpos.y++;
		ppos.y++;
	}
	return (overlap == 1);
}

unsigned int	get_heatsum(int x, int y, t_info *info, t_piece *piece)
{
	int				i;
	int				j;
	unsigned int	heatsum;

	heatsum = 0;
	i = 0;
	while (i < piece->rows && y < info->nrows)
	{
		j = 0;
		while (j < piece->cols)
		{
			if (x >= info->ncols)
				break ;
			if (piece->data[i][j] == '*')
				heatsum += info->heatmap[y][x];
			x++;
			j++;
		}
		x -= piece->cols;
		y++;
		i++;
	}
	return (heatsum);
}

void	find_min_heatsum(t_info *info, t_piece *piece, t_pos *minpos)
{
	t_pos			pos;
	unsigned int	min_heatsum;
	unsigned int	heatsum;

	min_heatsum = MAX_HEATSUM;
	pos.y = 0;
	while (pos.y < info->nrows)
	{
		pos.x = 0;
		while (pos.x < info->ncols)
		{
			if (can_place_piece(pos, info, piece, 0))
			{
				heatsum = get_heatsum(pos.x, pos.y, info, piece);
				if (heatsum < min_heatsum)
				{
					min_heatsum = heatsum;
					minpos->x = pos.x;
					minpos->y = pos.y;
				}
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	think(t_piece *piece, t_info *info)
{
	t_pos	pos;

	find_min_heatsum(info, piece, &pos);
	send_command(&pos);
}
