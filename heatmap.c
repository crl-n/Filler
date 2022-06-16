/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:58:37 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/16 18:58:41 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

int	are_valid_ids(t_info *info, int i, int j)
{
	if (i < 0 || i >= info->nrows)
		return (0);
	if (j < 0 || j >= info->ncols)
		return (0);
	return (1);
}

void	add_to_queue(t_info *info, int i, int j)
{
	t_list	*node;

	node = ft_lstnew(NULL, 0);
	node->content = new_pos(j, i);
	node->content_size = sizeof (node);
	ft_lstadd_back(&info->queue, node);
	ft_lstsize(info->queue);
}

static void	bfs(t_info *info, int i, int j, unsigned int current_heat)
{
	t_pos	*pos;

	add_to_queue(info, i, j);
	while (info->queue)
	{
		pos = ft_lstpop_left(&info->queue);
		i = pos->y;
		j = pos->x;
		free(pos);
		pos = NULL;
		if (info->visited[i][j] || current_heat > info->heatmap[i][j])
			continue ;
		info->visited[i][j] = 1;
		info->heatmap[i][j] = current_heat;
		if (are_valid_ids(info, i - 1, j) && !info->visited[i - 1][j])
			add_to_queue(info, i - 1, j);
		if (are_valid_ids(info, i, j + 1) && !info->visited[i][j + 1])
			add_to_queue(info, i, j + 1);
		if (are_valid_ids(info, i + 1, j) && !info->visited[i + 1][j])
			add_to_queue(info, i + 1, j);
		if (are_valid_ids(info, i, j - 1) && !info->visited[i][j - 1])
			add_to_queue(info, i, j - 1);
		current_heat++;
	}
}

// 1. Iterate through map, set all NEW opponent cells to 0.
// 2. BFS from each NEW opponent cell.
// 3. During BFS, update each cell with the distance from the cell 
//  the search started from IF the value is smaller than it was.

void	update_heatmap(t_info *info)
{
	int		i;
	int		j;
	char	symbol;

	symbol = player_symbol(info->opponent);
	i = 0;
	while (i < info->nrows)
	{
		j = 0;
		while (j < info->ncols)
		{
			if (info->map[i][j] == symbol)
				bfs(info, i, j, 0);
			j++;
		}
		i++;
	}
	reset_visited(info);
}
