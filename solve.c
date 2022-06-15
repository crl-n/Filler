/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:31:03 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/15 10:21:52 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

// Checks if a block can be placed in a cell.
//
// A block can be placed in any cell that is not already occupied
// by the opponent. A block can also be placed outside the map.

static int	is_free_cell(t_info *info, t_pos mpos, t_pos ppos, t_piece *piece)
{
	if (mpos.x < 0)
		mpos.x = info->ncols + mpos.x;
	if (mpos.y < 0)
		mpos.y = info->nrows + mpos.y;
	if (mpos.x < info->ncols && mpos.x >= 0
		&& mpos.y < info->nrows && mpos.y >= 0)
	{
		if (is_player(info->map[mpos.y][mpos.x], info->opponent)
				&& piece->data[ppos.y][ppos.x] == '*')
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

static int	is_overlapping(t_info *info, t_pos mpos, t_pos ppos, t_piece *piece)
{
	if (mpos.x < 0)
		mpos.x = info->ncols + mpos.x;
	if (mpos.y < 0)
		mpos.y = info->nrows + mpos.y;
	if (mpos.x < info->ncols && mpos.x >= 0
		&& mpos.y < info->nrows && mpos.y >= 0)
	{
		if (is_player(info->map[mpos.y][mpos.x], info->player)
				&& piece->data[ppos.y][ppos.x] == '*')
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
		if (mpos.y >= info->nrows)
			return (0);
		ppos.x = 0;
		while (ppos.x < piece->cols)
		{
			if (!is_free_cell(info, mpos, ppos, piece))
				return (0);
			if (is_overlapping(info, mpos, ppos, piece))
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
			if (x >= 0 && x < info->ncols && y >= 0
				&& piece->data[i][j] == '*')
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

// TODO
// Fix bug, where the algorithm places pieces outside of the map, with only
// one piece (the overlapping one) on the board. This is an invalid move.

int	search_within_map(t_info *info, t_piece *piece, t_pos *minpos)
{
	t_pos			pos;
	unsigned int	min_heatsum;
	unsigned int	heatsum;
	int				place_found;

	min_heatsum = MAX_HEATSUM;
	place_found = FALSE;
	pos.y = 0;
	while (pos.y < info->nrows)
	{
		pos.x = 0;
		while (pos.x < info->ncols - piece->cols)
		{
			if (can_place_piece(pos, info, piece, 0))
			{
				place_found = TRUE;
				heatsum = get_heatsum(pos.x, pos.y, info, piece);
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

void	search_outside_map(t_info *info, t_piece *piece, t_pos *minpos)
{
	t_pos			pos;
	unsigned int	min_heatsum;
	unsigned int	heatsum;

	min_heatsum = MAX_HEATSUM;
	pos.y = -piece->rows + 1;
	while (pos.y < info->nrows + piece->rows)
	{
		pos.x = -piece->cols + 1;
		while (pos.x < info->ncols - piece->cols)
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

// Search for a place to put the piece within the map.
// If none can be found, search outside the map.

void	solve(t_piece *piece, t_info *info)
{
	t_pos	pos;
	int		place_found;

	pos.x = 0;
	pos.y = 0;
	place_found = 0;
	place_found = search_within_map(info, piece, &pos);
	if (!place_found)
		search_outside_map(info, piece, &pos);
	send_command(&pos);
}
