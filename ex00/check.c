/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaxapar <gaxapar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by gaxapar           #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by gaxapar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

int	in_bounds(t_board *b, int x, int y, int v)
{
	int	n;

	n = b->size;
	if (v > n - b->views[x] + 1 + y)
		return (0);
	if (v > n - b->views[n + x] + 1 + (n - 1 - y))
		return (0);
	if (v > n - b->views[2 * n + y] + 1 + x)
		return (0);
	if (v > n - b->views[3 * n + y] + 1 + (n - 1 - x))
		return (0);
	return (1);
}

static void	load_line(t_board *b, t_line *l, int start, int step)
{
	int	i;

	l->size = b->size;
	l->lo = b->size;
	l->hi = -1;
	l->front_seen = 0;
	l->back_seen = 0;
	i = 0;
	while (i < b->size)
	{
		l->masks[i] = b->masks[start + i * step];
		l->taken[i] = 0;
		i++;
	}
}

int	cell_can(t_board *b, int pos, int v)
{
	t_line	l;
	int		n;
	int		x;
	int		y;

	n = b->size;
	x = pos % n;
	y = pos / n;
	load_line(b, &l, y * n, 1);
	l.masks[x] = 1 << v;
	l.front = b->views[2 * n + y];
	l.back = b->views[3 * n + y];
	if (!line_fits(&l))
		return (0);
	load_line(b, &l, x, n);
	l.masks[y] = 1 << v;
	l.front = b->views[x];
	l.back = b->views[n + x];
	return (line_fits(&l));
}
