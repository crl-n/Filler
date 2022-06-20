/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 00:34:52 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/20 02:02:06 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include <stdlib.h>

// Allocates a 2D array of t_bool's, i.e. 8-bit unsigned integers.

t_bool	**boolean_array(int n_rows, int n_cols)
{
	t_bool		**arr;
	t_bool		*cells;
	int			i;
	size_t		size;

	size = n_rows * sizeof (t_bool *) + n_rows * n_cols * sizeof (t_bool);
	arr = (t_bool **) malloc(size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, size);
	cells = (t_bool *)(arr + n_rows);
	i = 0;
	while (i < n_rows)
	{
		arr[i] = cells + i * n_cols;
		i++;
	}
	return (arr);
}

void	reset_visited(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->nrows)
	{
		j = 0;
		while (j < info->ncols)
		{
			info->visited[i][j] = FALSE;
			j++;
		}
		i++;
	}
}
