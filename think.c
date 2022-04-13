/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:31:03 by carlnysten        #+#    #+#             */
/*   Updated: 2022/04/13 16:31:47 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

static int can_place_piece2(t_pos pos, int i, t_info *info, int *overlap)
{
	int	j;
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	j = 0;
	while (j < info->piece->cols)
	{
		if (x >= info->ncols)
			return (0);
		if (is_player(info->map[y][x], info->player)
				&& info->piece->data[i][j] == '*')
			*overlap += 1;
		if (is_player(info->map[y][x], info->opponent)
				&& info->piece->data[i][j] == '*')
			return (0);
		x++;
		j++;
	}
	return (0);
}

int	can_place_piece(t_pos pos, t_info *info, t_piece *piece)
{
	int	i;
	int	overlap;

	overlap = 0;
	i = 0;
	while (i < piece->rows)
	{
		if (pos.y >= info->nrows)
			return (0);
		if (can_place_piece2(pos, i, info, &overlap))
			return (1);
		//x -= piece->cols;
		pos.y++;
		i++;
	}
	if (overlap == 1)
		return (1);
	return (0);
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
		if (y >= info->nrows)
			break ;
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
			if (can_place_piece(pos, info, piece))
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
	info->cmd->y = pos.y;
	info->cmd->x = pos.x;
	send_command(info);
}
