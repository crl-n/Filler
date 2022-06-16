/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:59:27 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/16 23:18:41 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

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

// Try to place the piece so that it is completely within the map.

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
		while (pos.x < info->ncols)
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

// Try to place the piece on the top and left borders.
// Placing the piece on right and bottom borders often causes
// issues with the filler_vm, therefore I avoid doing that.

void	search_outside_map(t_info *info, t_piece *piece, t_pos *minpos)
{
	t_pos			pos;
	unsigned int	min_heatsum;
	unsigned int	heatsum;

	min_heatsum = MAX_HEATSUM;
	pos.y = -piece->rows + 1;
	while (pos.y < info->nrows)
	{
		pos.x = -piece->cols + 1;
		while (pos.x < info->ncols)
		{
			if (!are_valid_ids(info, pos.y, pos.x)
				&& can_place_piece(pos, info, piece, 0))
			{
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
}

// Search for a place to put the piece within the map.
// If none can be found, search outside the map.

void	solve(t_piece *piece, t_info *info)
{
	t_pos	pos;
	int		place_found;

	pos = (t_pos){0, 0};
	place_found = FALSE;
	place_found = search_within_map(info, piece, &pos);
	if (!place_found)
		search_outside_map(info, piece, &pos);
	send_command(&pos);
	if (!place_found)
		die(info, NULL);
}
