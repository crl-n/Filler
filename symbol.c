/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 01:31:28 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/27 01:31:38 by carlnysten       ###   ########.fr       */
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

