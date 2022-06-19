/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:28:31 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/20 00:08:47 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	queue_has_next(t_info *info)
{
	if (info->queue.push > info->queue.pop)
		return (1);
	return (0);
}

void	push_to_queue(t_info *info, int i, int j)
{
	if (info->queue.push >= info->queue.size)
		die(info, "Error, queue is full.");
	info->queue.data[info->queue.push] = (t_pos){j, i};
	info->queue.push++;
}

t_pos	pop_from_queue(t_info *info)
{
	if (info->queue.pop >= info->queue.size)
		die(info, "Error, can't pop from queue. Index out of bounds.");
	return (info->queue.data[info->queue.pop++]);
}

void	reset_queue(t_info *info)
{
	/*
	int	i;

	i = 0;
	while (i < info->queue.size)
	{
		info->queue.data[i] = (t_pos){0, 0};
		i++;
	}
	*/
	info->queue.push = 0;
	info->queue.pop = 0;
}
