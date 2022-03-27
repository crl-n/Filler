/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:31:03 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/27 21:42:43 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	can_place_piece(int x, int y, t_info *info, t_piece *piece)
{
	int	i;
	int	j;
	int	overlap;

	dprintf(info->fd, "CHECKING IF PIECE CAN BE PLACED y: %d x: %d\n", y, x);
	dprintf(info->fd, "PLAYER SYMBOLS: %c %c\n", player_symbol(info->player), player_symbol_lower(info->player));
	overlap = 0;
	i = 0;
	while (i < piece->rows && y < info->nrows)
	{
		if (y >= info->nrows)
			break ;
		j = 0;
		while (j < piece->cols)
		{
			//dprintf(info->fd, "CHECKING: y %d x %d\n", y, x);
			if (x >= info->ncols)
				break ;
			if (is_player(info->map[y][x], info->player) && piece->data[i][j] == '*')
				overlap++;
			x++;
			j++;
		}
		x -= piece->cols;
		y++;
		i++;
	}
	if (overlap == 1)
	{
		dprintf(info->fd, "* PIECE CAN BE PLACED overlap: %d\n", overlap);
		return (1);
	}
	dprintf(info->fd, "PIECE CAN NOT BE PLACED\n");
	return (0);
}

// Attempts to find placement near pos using a sprial search pattern.
t_pos	*find_placement_near(t_pos *pos, t_info *info, t_piece *piece)
{
	int	y;
	int	x;
	int	i;
	int	rate;

	dprintf(info->fd, "FIND_PLACEMENT_NEAR y: %d x: %d\n", pos->y, pos->x);
	y = pos->y;
	x = pos->x;
	rate = 1;
	while (1)
	{
		i = 0;
		while (i++ < rate)
			if (can_place_piece(++x, y, info, piece))
				return (new_pos(x, y));
		while (--i > 0)
			if (can_place_piece(x, ++y, info, piece))
				return (new_pos(x, y));
		rate++;
		while (i++ < rate)
			if (can_place_piece(--x, y, info, piece))
				return (new_pos(x, y));
		while (--i > 0)
			if (can_place_piece(x, --y, info, piece))
				return (new_pos(x, y));
		rate++;
	}
	return (NULL);
}

void	think(t_info *info, t_piece *piece)
{
	t_pos	*pos;

	(void) piece;
	if (!info->prev)
		info->prev = find_in_map(info, player_symbol(info->player));
	else
		info->prev = find_in_map(info, player_symbol_lower(info->player));
	pos = find_placement_near(info->center, info, piece);
	dprintf(info->fd, "FOUND PLACEMENT y: %d x: %d\n", pos->y, pos->x);
	info->cmd->y = pos->y;
	info->cmd->x = pos->x;
	free(pos);
	pos = NULL;
	send_command(info);
}
