/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:03:11 by carlnysten        #+#    #+#             */
/*   Updated: 2022/04/13 13:37:40 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

void	die(t_info *info)
{
	t_piece	*piece;

	piece = info->piece;
	if (piece)
	{
		free_string_array(piece->data, piece->rows, piece->cols);
		free(piece);
	}
	if (info->map)
		free_string_array(info->map, info->nrows, info->ncols);
	free_heatmap(info->heatmap, info->nrows, info->ncols);
	if (info->cmd)
		free(info->cmd);
	if (info)
		free(info);
	exit(0);
}

// Note: This function only expects a string array allocated
// with a single malloc.
void	free_string_array(char **array, int rows, int cols)
{
	size_t	size;

	if (!array)
		return ;
	size = (rows + 1) * sizeof (char *) + rows * (cols + 1) * sizeof (char);
	ft_bzero(array, size);
	free(array);
}

// Note: This function expects a 2D array of doubles allocated
// with a single malloc.
void	free_heatmap(unsigned int **heatmap, int rows, int cols)
{
	size_t	size;

	if (!heatmap)
		return ;
	size = (rows + 1) * sizeof (unsigned int *);
	size += rows * (cols) * sizeof (unsigned int);
	ft_bzero(heatmap, size);
	free(heatmap);
}
