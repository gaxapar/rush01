/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaxapar <gaxapar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by gaxapar           #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by gaxapar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

static int	count_numbers(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] < '1' || str[i] > '9')
			return (-1);
		count++;
		i++;
		if (str[i] == ' ' && str[i + 1] != '\0')
			i++;
		else if (str[i] != '\0')
			return (-1);
	}
	return (count);
}

static int	fill_masks(t_board *b)
{
	int	pos;
	int	v;

	pos = 0;
	while (pos < b->size * b->size)
	{
		v = 0;
		while (++v <= b->size)
		{
			if (in_bounds(b, pos % b->size, pos / b->size, v))
				b->masks[pos] |= 1 << v;
		}
		pos++;
	}
	return (1);
}

int	parse_input(char *str, t_board *b)
{
	int	count;
	int	i;

	count = count_numbers(str);
	if (count <= 0 || count % 4 != 0 || count > 36)
		return (0);
	b->size = count / 4;
	i = 0;
	while (i < count)
	{
		b->views[i] = str[i * 2] - '0';
		if (b->views[i] > b->size)
			return (0);
		i++;
	}
	i = 0;
	while (i < b->size * b->size)
		b->masks[i++] = 0;
	return (fill_masks(b));
}
