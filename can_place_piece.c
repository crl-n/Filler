/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_place_piece.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:01:00 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/20 01:58:37 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

// Checks if a block can be placed in a cell.
//
// A block can be placed in any cell that is not already occupied
// by the opponent. A block can also be placed outside the map.

static int	is_free_cell(t_info *info, t_pos mpos)
{
	if (mpos.x >= info->ncols)
		return (0);
	if (mpos.y >= info->nrows)
		return (0);
	if (mpos.x < 0)
		mpos.x = info->ncols + mpos.x;
	if (mpos.y < 0)
		mpos.y = info->nrows + mpos.y;
	if (mpos.x < info->ncols && mpos.x >= 0
		&& mpos.y < info->nrows && mpos.y >= 0)
	{
		if (is_player(info->map[mpos.y][mpos.x], info->opponent))
			return (0);
		return (1);
	}
	return (1);
}

// Checks if a block would overlap with the player's own previously
// placed pieces.
//
// If a piece crosses the map border to the left, top or down, it wraps around.
// In these cases, it is necessary to check if the piece overlaps on the other
// side of the map.

static int	is_overlapping(t_info *info, t_pos mpos)
{
	if (mpos.x < 0)
		mpos.x = info->ncols + mpos.x;
	if (mpos.y < 0)
		mpos.y = info->nrows + mpos.y;
	if (mpos.x < info->ncols && mpos.x >= 0
		&& mpos.y < info->nrows && mpos.y >= 0)
	{
		if (is_player(info->map[mpos.y][mpos.x], info->player))
			return (1);
		return (0);
	}
	return (0);
}

// Checks if the piece can be placed at a specific position in the map.
//
// The row and col values for the map are stored in mpos,
// and the row and col values for the piece are stored
// in ppos.

int	can_place_piece(t_pos mpos, t_info *info, t_piece *piece, int overlap)
{
	t_pos	ppos;

	ppos.y = 0;
	while (ppos.y < piece->rows)
	{
		ppos.x = 0;
		while (ppos.x < piece->cols)
		{
			if (piece->data[ppos.y][ppos.x] == '*')
			{
				if (!is_free_cell(info, mpos) || overlap == 2)
					return (0);
				if (is_overlapping(info, mpos))
					overlap++;
			}
			mpos.x++;
			ppos.x++;
		}
		mpos.x -= piece->cols;
		mpos.y++;
		ppos.y++;
	}
	return (overlap == 1);
}
