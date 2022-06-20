/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_place_piece.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:01:00 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/20 23:46:05 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

static int	is_free_cell(t_info *info, t_pos mpos)
{
	if (mpos.x >= info->ncols)
		return (0);
	if (mpos.y >= info->nrows)
		return (0);
	if (is_player(info->map[mpos.y][mpos.x], info->opponent))
		return (0);
	return (1);
}

// Checks if a block would overlap with the player's own previously
// placed pieces.

static int	is_overlapping(t_info *info, t_pos mpos)
{
	if (is_player(info->map[mpos.y][mpos.x], info->player))
		return (1);
	return (0);
}

// Checks if the piece can be placed at a specific position in the map.
//
// The row and col values for the map are stored in mpos,
// and the row and col values for the piece are stored
// in ppos.

int	can_place_piece(t_pos mpos, t_info *info, t_pos ppos, int overlap)
{
	while (ppos.y < info->piece->rows)
	{
		ppos.x = 0;
		while (ppos.x < info->piece->cols)
		{
			if (info->piece->data[ppos.y][ppos.x] == '*')
			{
				if (!is_free_cell(info, mpos))
					return (0);
				if (is_overlapping(info, mpos))
				{
					overlap++;
					if (overlap == 2)
						return (0);
				}
			}
			mpos.x++;
			ppos.x++;
		}
		mpos.x -= info->piece->cols;
		mpos.y++;
		ppos.y++;
	}
	return (overlap == 1);
}
