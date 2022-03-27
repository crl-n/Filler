/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:03:11 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/27 17:30:17 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

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
void	free_heatmap(char **heatmap, int rows, int cols)
{
	size_t	size;

	if (!heatmap)
		return ;
	size = (rows + 1) * sizeof (double *) + rows * (cols) * sizeof (double);
	ft_bzero(heatmap, size);
	free(heatmap);
}
