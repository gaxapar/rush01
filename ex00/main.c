/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaxapar <gaxapar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by gaxapar           #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by gaxapar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

static void	put_char(char c)
{
	write(1, &c, 1);
}

static int	value_of(int mask)
{
	int	v;

	v = 1;
	while (!(mask & (1 << v)))
		v++;
	return (v);
}

void	put_error(void)
{
	write(1, "Error\n", 6);
}

void	print_grid(t_board *b)
{
	int	x;
	int	y;

	y = 0;
	while (y < b->size)
	{
		x = 0;
		while (x < b->size)
		{
			put_char(value_of(b->masks[y * b->size + x]) + '0');
			if (x < b->size - 1)
				put_char(' ');
			x++;
		}
		put_char('\n');
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_board	b;

	if (argc != 2 || !parse_input(argv[1], &b) || !solve(&b))
		put_error();
	else
		print_grid(&b);
	return (0);
}
