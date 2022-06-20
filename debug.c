/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:37:04 by cnysten           #+#    #+#             */
/*   Updated: 2022/06/16 18:24:05 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>

void	print_heatmap(t_info *info)
{
	int	i;
	int	j;

	dprintf(2, "PRINTING HEATMAP\n");
	i = 0;
	while (i < info->nrows)
	{
		j = 0;
		while (j < info-> ncols)
		{
			dprintf(2, "%u ", info->heatmap[i][j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
}

void	print_map(t_info *info)
{
	int	i;

	dprintf(2, "PRINTING MAP\n");
	i = 0;
	while (i < info->nrows)
	{
		dprintf(2, "%s\n", info->map[i]);
		i++;
	}
}

void	print_visited(t_info *info)
{
	int	i;
	int	j;

	dprintf(2, "PRINTING HEATMAP\n");
	i = 0;
	while (i < info->nrows)
	{
		j = 0;
		while (j < info-> ncols)
		{
			dprintf(2, "%i ", info->visited[i][j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
}
