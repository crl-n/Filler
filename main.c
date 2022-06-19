/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 10:12:58 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/20 02:23:38 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

// TODO
// Improve parser error handling.

static void	init_info(t_info *info)
{
	info->piece = new_piece();
	info->map = new_string_array(info->nrows, info->ncols);
	info->heatmap = new_heatmap(info->nrows, info->ncols);
	info->visited = boolean_array(info->nrows, info->ncols);
	info->searched = boolean_array(info->nrows, info->ncols);
	info->queue.data = new_pos_array(info->nrows, info->ncols);
	info->queue.size = info->nrows * info->ncols;
	if (!info->piece || !info->map || !info->heatmap || !info->visited)
		die(info, ERROR);
}

int	main(void)
{
	t_info	*info;

	info = new_info();
	if (!info)
		return (0);
	get_player_number(info);
	get_map_dimensions(info);
	init_info(info);
	while (1)
	{
		get_map_info(info);
		update_heatmap(info);
		get_piece_info(info->piece, info, 0);
		solve(info);
		skip_line(info);
	}
	return (0);
}
