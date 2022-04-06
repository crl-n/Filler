/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:03:11 by carlnysten        #+#    #+#             */
/*   Updated: 2022/04/06 11:59:37 by cnysten          ###   ########.fr       */
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
void	free_heatmap(unsigned int **heatmap, int rows, int cols)
{
	size_t	size;

	if (!heatmap)
		return ;
	size = (rows + 1) * sizeof (unsigned int *) + rows * (cols) * sizeof (unsigned int);
	ft_bzero(heatmap, size);
	free(heatmap);
}
