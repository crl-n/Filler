/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:53:55 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/20 02:13:00 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "get_map_info.h"
#include <unistd.h>
#include <stdlib.h>

void	get_map_info(t_info *info)
{
	static t_buffer	buffer;
	int				bytes_read;
	int				i;

	buffer.size = info->nrows * (5 + info->ncols) + 1;
	buffer.data = (char *)malloc(buffer.size);
	buffer.data[buffer.size - 1] = '\0';
	skip_line(info);
	bytes_read = 0;
	while (bytes_read != (int)(buffer.size - 1))
	{
		bytes_read += read(0, buffer.data + bytes_read, buffer.size - 1 - bytes_read);
		//ft_putstr_fd(buffer.data, 2);
		//die(info, ERROR_MAP_INFO);
	}
	i = 0;
	while (i < info->nrows)
	{
		ft_strncpy(info->map[i], buffer.data + (i * (5 + info->ncols)) + 4, info->ncols);
		i++;
	}
	ft_strdel(&buffer.data);
}
