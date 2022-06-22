/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prune_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:01:43 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/22 18:03:29 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	get_boundaries(t_info *info, t_bool min_y_found,
		t_pos *min, t_pos *max)
{
	int		y;
	int		x;

	y = 0;
	while (y < info->piece->rows)
	{
		x = 0;
		while (x < info->piece->cols)
		{
			if (info->piece->data[y][x] == '*')
			{
				max->y = y;
				if (!min_y_found)
					min->y = y;
				min_y_found = TRUE;
				if (x > max->x)
					max->x = x;
				if (x < min->x)
					min->x = x;
			}
			x++;
		}
		y++;
	}
}

void	prune_piece(t_info *info)
{
	char	**temp;
	t_pos	min;
	t_pos	max;
	int		i;
	int		j;

	min = (t_pos){0, info->piece->cols - 1};
	max = (t_pos){0, 0};
	get_boundaries(info, FALSE, &min, &max);
	temp = new_string_array(max.y + 1 - min.y, max.x + 1 - min.x);
	i = min.y;
	j = 0;
	while (i <= max.y)
	{
		ft_strncpy(temp[j++], info->piece->data[i] + min.x, max.x + 1 - min.x);
		i++;
	}
	free_string_array(info->piece->data, info->piece->rows, info->piece->cols);
	info->piece->data = temp;
	info->piece->rows = max.y + 1 - min.y;
	info->piece->cols = max.x + 1 - min.x;
	info->piece->row_offset = min.y;
	info->piece->col_offset = min.x;
}
