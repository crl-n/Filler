/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:56:59 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/16 11:31:02 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

t_pos	*new_pos(int x, int y)
{
	t_pos	*pos;

	pos = (t_pos *) malloc(sizeof (t_pos));
	if (!pos)
		return (NULL);
	pos->x = x;
	pos->y = y;
	return (pos);
}

t_info	*new_info(void)
{
	t_info	*info;

	info = (t_info *) malloc(sizeof (t_info));
	if (!info)
		return (NULL);
	ft_bzero(info, sizeof (t_info));
	info->first_round = 1;
	return (info);
}

t_piece	*new_piece(void)
{
	t_piece	*piece;

	piece = (t_piece *) malloc(sizeof (t_piece));
	if (!piece)
		return (NULL);
	ft_bzero(piece, sizeof (t_piece));
	return (piece);
}

char	**new_string_array(int rows, int cols)
{
	char	**array;
	char	*str;
	size_t	size;
	int		i;

	size = (rows + 1) * sizeof (char *) + rows * (cols + 1) * sizeof (char);
	array = (char **) malloc(size);
	if (!array)
		return (NULL);
	ft_bzero(array, size);
	str = (char *)(array + rows + 1);
	i = 0;
	while (i < rows)
	{
		array[i] = str + i * (cols + 1);
		i++;
	}
	return (array);
}

unsigned int	**new_heatmap(int rows, int cols)
{
	unsigned int	**heatmap;
	unsigned int	*cell;
	size_t			size;
	int				i;

	size = (rows + 1) * sizeof (unsigned int *);
	size += rows * cols * sizeof (unsigned int);
	heatmap = (unsigned int **) malloc(size);
	if (!heatmap)
		return (NULL);
	ft_bzero(heatmap, size);
	cell = (unsigned int *)(heatmap + rows + 1);
	i = 0;
	while (i < rows)
	{
		heatmap[i] = cell + i * (cols);
		i++;
	}
	ft_memset(heatmap[0], MAX_HEAT, rows * cols * sizeof (unsigned int));
	return (heatmap);
}
