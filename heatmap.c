/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:53:02 by cnysten           #+#    #+#             */
/*   Updated: 2022/04/13 13:45:51 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>

static int	are_valid_ids(t_info *info, int i, int j)
{
	if (i < 0 || i >= info->nrows)
		return (0);
	if (j < 0 || j >= info->ncols)
		return (0);
	return (1);
}

static void	update_adjacent_cells(t_info *info,
		int i, int j, unsigned int current_heat)
{
	if (are_valid_ids(info, i - 1, j)
		&& info->heatmap[i - 1][j] > current_heat + 1)
		info->heatmap[i - 1][j] = current_heat + 1;
	if (are_valid_ids(info, i - 1, j + 1)
		&& info->heatmap[i - 1][j + 1] > current_heat + 1)
		info->heatmap[i - 1][j + 1] = current_heat + 1;
	if (are_valid_ids(info, i, j + 1)
		&& info->heatmap[i][j + 1] > current_heat + 1)
		info->heatmap[i][j + 1] = current_heat + 1;
	if (are_valid_ids(info, i + 1, j + 1)
		&& info->heatmap[i + 1][j + 1] > current_heat + 1)
		info->heatmap[i + 1][j + 1] = current_heat + 1;
	if (are_valid_ids(info, i + 1, j)
		&& info->heatmap[i + 1][j] > current_heat + 1)
		info->heatmap[i + 1][j] = current_heat + 1;
	if (are_valid_ids(info, i + 1, j - 1)
		&& info->heatmap[i + 1][j - 1] > current_heat + 1)
		info->heatmap[i + 1][j - 1] = current_heat + 1;
	if (are_valid_ids(info, i, j - 1)
		&& info->heatmap[i][j - 1] > current_heat + 1)
		info->heatmap[i][j - 1] = current_heat + 1;
	if (are_valid_ids(info, i - 1, j - 1)
		&& info->heatmap[i - 1][j - 1] > current_heat + 1)
		info->heatmap[i - 1][j - 1] = current_heat + 1;
}

static void	update_heatmap2(t_info *info, unsigned int current_heat)
{
	int	i;
	int	j;

	if (current_heat == MAX_HEAT)
		return ;
	i = 0;
	while (i < info->nrows)
	{
		j = 0;
		while (j < info-> ncols)
		{
			if (info->heatmap[i][j] == current_heat)
				update_adjacent_cells(info, i, j, current_heat);
			j++;
		}
		i++;
	}
	return (update_heatmap2(info, current_heat + 1));
}

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
			if (is_player(info->map[i][j], info->opponent))
				info->heatmap[i][j] = 0;
			j++;
		}
		i++;
	}
	return (update_heatmap2(info, 0));
}

void	print_heatmap(t_info *info)
{
	int	i;
	int	j;

	dprintf(info->fd, "PRINTING HEATMAP\n");
	i = 0;
	while (i < info->nrows)
	{
		j = 0;
		while (j < info-> ncols)
		{
			dprintf(info->fd, "%u ", info->heatmap[i][j]);
			j++;
		}
		dprintf(info->fd, "\n");
		i++;
	}
}
