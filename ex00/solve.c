/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaxapar <gaxapar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by gaxapar           #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by gaxapar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

static int	count_bits(int mask)
{
	int	count;

	count = 0;
	while (mask)
	{
		count += mask & 1;
		mask >>= 1;
	}
	return (count);
}

static int	reduce_cell(t_board *b, int pos)
{
	int	v;
	int	keep;

	keep = 0;
	v = 0;
	while (++v <= b->size)
	{
		if ((b->masks[pos] & (1 << v)) && cell_can(b, pos, v))
			keep |= 1 << v;
	}
	if (keep == b->masks[pos])
		return (0);
	b->masks[pos] = keep;
	if (!keep)
		return (-1);
	return (1);
}

static int	propagate(t_board *b)
{
	int	pos;
	int	changed;
	int	result;

	changed = 1;
	while (changed)
	{
		changed = 0;
		pos = 0;
		while (pos < b->size * b->size)
		{
			result = reduce_cell(b, pos);
			if (result < 0)
				return (0);
			if (result > 0)
				changed = 1;
			pos++;
		}
	}
	return (1);
}

static int	next_cell(t_board *b)
{
	int	pos;
	int	best;
	int	best_count;
	int	count;

	pos = 0;
	best = -1;
	best_count = 10;
	while (pos < b->size * b->size)
	{
		count = count_bits(b->masks[pos]);
		if (count > 1 && count < best_count)
		{
			best = pos;
			best_count = count;
		}
		pos++;
	}
	return (best);
}

int	solve(t_board *b)
{
	t_board	copy;
	int		pos;
	int		v;

	if (!propagate(b))
		return (0);
	pos = next_cell(b);
	if (pos < 0)
		return (1);
	v = 0;
	while (++v <= b->size)
	{
		if (b->masks[pos] & (1 << v))
		{
			copy = *b;
			copy.masks[pos] = 1 << v;
			if (solve(&copy))
			{
				*b = copy;
				return (1);
			}
		}
	}
	return (0);
}
