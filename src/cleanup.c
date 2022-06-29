/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:03:11 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/29 09:58:41 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

void	del(void *node, size_t size)
{
	(void) size;
	if (node)
		free(node);
}

void	put_error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	exit(-1);
}

void	die(t_info *info, char *error_msg)
{
	if (!info)
		exit(0);
	if (info->piece)
	{
		free_string_array(info->piece->data,
			info->piece->rows, info->piece->cols);
		free(info->piece);
	}
	if (info->map)
		free_string_array(info->map, info->nrows, info->ncols);
	if (info->heatmap)
		free_heatmap(info->heatmap, info->nrows, info->ncols);
	if (info->visited)
		free(info->visited);
	if (info->searched)
		free(info->searched);
	if (info->queue.data)
		free(info->queue.data);
	ft_strdel(&(info->buffer.data));
	if (error_msg)
		put_error_msg(error_msg);
	//system("leaks cnysten.filler >> leaks_out");
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
