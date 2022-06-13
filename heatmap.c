/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:53:02 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/13 14:10:13 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	are_valid_ids(t_info *info, int i, int j)
{
	if (i < 0 || i >= info->nrows)
		return (0);
	if (j < 0 || j >= info->ncols)
		return (0);
	return (1);
}

static void	breadth_first_search(t_info *info, int i, int j, unsigned int current_heat)
{
	if (current_heat == MAX_HEAT || current_heat > info->heatmap[i][j])
		return ;
	info->heatmap[i][j] = current_heat;
	if (are_valid_ids(info, i - 1, j))
		breadth_first_search(info, i - 1, j, current_heat + 1);
	if (are_valid_ids(info, i - 1, j + 1))
		breadth_first_search(info, i - 1, j + 1, current_heat + 1);
	if (are_valid_ids(info, i, j + 1))
		breadth_first_search(info, i, j + 1, current_heat + 1);
	if (are_valid_ids(info, i + 1, j + 1))
		breadth_first_search(info, i + 1, j + 1, current_heat + 1);
	if (are_valid_ids(info, i + 1, j))
		breadth_first_search(info, i + 1, j, current_heat + 1);
	if (are_valid_ids(info, i + 1, j - 1))
		breadth_first_search(info, i + 1, j - 1, current_heat + 1);
	if (are_valid_ids(info, i, j - 1))
		breadth_first_search(info, i, j - 1, current_heat + 1);
	if (are_valid_ids(info, i - 1, j - 1))
		breadth_first_search(info, i - 1, j - 1, current_heat + 1);
}

// 1. Iterate through map, set all NEW opponent cells to 0.
// 2. BFS from each NEW opponent cell.
// 3. During BFS, update each cell with the distance from the cell 
//    the search started from IF the value is smaller than it was.

void	update_heatmap(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->nrows)
	{
		j = 0;
		while (j < info-> ncols)
		{
			if (info->map[i][j] == player_symbol_lower(info->opponent))
				breadth_first_search(info, i, j, 0);
			j++;
		}
		i++;
	}
}
