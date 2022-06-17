/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 10:12:58 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/17 01:44:36 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

// TODO
// Improve parser error handling.

int	main(void)
{
	t_info	*info;

	info = new_info();
	if (!info)
		return (0);
	info->piece = new_piece();
	get_player_number(info);
	get_map_dimensions(info);
	info->map = new_string_array(info->nrows, info->ncols);
	info->heatmap = new_heatmap(info->nrows, info->ncols);
	info->visited = int_array_2d(info->nrows, info->ncols);
	if (!info->piece || !info->map || !info->heatmap)
		die(info, ERROR);
	while (1)
	{
		get_map_info(info);
		//print_map(info);
		update_heatmap(info);
		get_piece_info(info->piece, info, 0);
		solve(info->piece, info);
		skip_line(info);
	}
	return (0);
}
