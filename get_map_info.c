/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:53:55 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/20 13:22:44 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <unistd.h>
#include <stdlib.h>

static void	validate_map_info(t_info *info)
{
	(void) info;
}

static void	copy_to_map(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nrows)
	{
		ft_strncpy(info->map[i],
			info->buffer.data + (i * (5 + info->ncols)) + 4, info->ncols);
		i++;
	}
	ft_strclr(info->buffer.data);
}

void	get_map_info(t_info *info)
{
	int	bytes_read;
	int	total_bytes_read;

	skip_line(info);
	bytes_read = 0;
	total_bytes_read = 0;
	while (total_bytes_read != (int)(info->buffer.size - 1))
	{
		bytes_read = read(0, info->buffer.data + bytes_read,
				info->buffer.size - 1 - bytes_read);
		if (bytes_read < 0)
			die(info, ERROR_MAP_INFO);
		total_bytes_read += bytes_read;
	}
	validate_map_info(info);
	copy_to_map(info);
}
