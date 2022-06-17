/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_heatmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:58:37 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/17 23:58:49 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

// Checks if a pair of map indices are valid.

int	are_valid_ids(t_info *info, int i, int j)
{
	if (i < 0 || i >= info->nrows)
		return (0);
	if (j < 0 || j >= info->ncols)
		return (0);
	return (1);
}

static void	queue_children_nodes(t_info *info, int i, int j)
{
	if (are_valid_ids(info, i - 1, j) && !info->visited[i - 1][j])
	{
		push_to_queue(info, i - 1, j);
		info->visited[i - 1][j] = 1;
	}
	if (are_valid_ids(info, i, j + 1) && !info->visited[i][j + 1])
	{
		push_to_queue(info, i, j + 1);
		info->visited[i][j + 1] = 1;
	}
	if (are_valid_ids(info, i + 1, j) && !info->visited[i + 1][j])
	{
		push_to_queue(info, i + 1, j);
		info->visited[i + 1][j] = 1;
	}
	if (are_valid_ids(info, i, j - 1) && !info->visited[i][j - 1])
	{
		push_to_queue(info, i, j - 1);
		info->visited[i][j - 1] = 1;
	}
}

// Breadth first search. First, the start cell is added to the queue.
// Then the heatmap value is updated if needed. Then the cell's children
// nodes are added to the queue.

static void	bfs(t_info *info, int i, int j, unsigned int current_heat)
{
	t_pos	pos;

	push_to_queue(info, i, j);
	info->visited[i][j] = 1;
	while (queue_has_next(info))
	{
		pos = pop_from_queue(info);
		i = pos.y;
		j = pos.x;
		if (current_heat > info->heatmap[i][j])
			continue ;
		queue_children_nodes(info, i, j);
		info->heatmap[i][j] = current_heat;
		current_heat++;
	}
	reset_queue(info);
}

// For each cell with an opponent block in it, start a breadth first search.

void	update_heatmap(t_info *info)
{
	int		i;
	int		j;
	char	opponent_symbol;

	opponent_symbol = player_symbol(info->opponent);
	i = 0;
	while (i < info->nrows)
	{
		j = 0;
		while (j < info->ncols)
		{
			if (info->map[i][j] == opponent_symbol)
				bfs(info, i, j, 0);
			j++;
		}
		i++;
	}
	reset_visited(info);
}
