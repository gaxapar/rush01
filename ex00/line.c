/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaxapar <gaxapar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by gaxapar           #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by gaxapar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

static int	place(t_line *l, int v);

static int	bounds_ok(t_line *l, int v)
{
	int	left;
	int	right;

	if (l->front_seen > l->front || l->back_seen > l->back)
		return (0);
	left = l->lo;
	if (v - 1 < left)
		left = v - 1;
	right = l->size - 1 - l->hi;
	if (v - 1 < right)
		right = v - 1;
	return (l->front_seen + left >= l->front
		&& l->back_seen + right >= l->back);
}

static int	try_pos(t_line *l, int v, int p)
{
	t_line	old;
	int		ok;

	old = *l;
	if (p < l->lo)
	{
		l->lo = p;
		l->front_seen++;
	}
	if (p > l->hi)
	{
		l->hi = p;
		l->back_seen++;
	}
	l->taken[p] = 1;
	ok = bounds_ok(l, v) && place(l, v - 1);
	*l = old;
	return (ok);
}

static int	place(t_line *l, int v)
{
	int	p;

	if (v == 0)
		return (l->front_seen == l->front && l->back_seen == l->back);
	p = 0;
	while (p < l->size)
	{
		if (!l->taken[p] && (l->masks[p] & (1 << v))
			&& try_pos(l, v, p))
			return (1);
		p++;
	}
	return (0);
}

int	line_fits(t_line *l)
{
	return (place(l, l->size));
}
