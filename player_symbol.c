/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 01:31:28 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/20 23:37:05 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	player_symbol_lower(int player)
{
	if (player == 1)
		return ('o');
	return ('x');
}

char	player_symbol(int player)
{
	if (player == 1)
		return ('O');
	return ('X');
}

int	is_player(char c, int player)
{
	if (c == player_symbol(player))
		return (1);
	if (c == player_symbol_lower(player))
		return (1);
	return (0);
}
