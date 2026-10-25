/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaxapar <gaxapar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by gaxapar           #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by gaxapar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH01_H
# define RUSH01_H

# include <unistd.h>

typedef struct s_board
{
	int	size;
	int	views[36];
	int	masks[81];
}	t_board;

typedef struct s_line
{
	int	size;
	int	front;
	int	back;
	int	lo;
	int	hi;
	int	front_seen;
	int	back_seen;
	int	taken[9];
	int	masks[9];
}	t_line;

int		parse_input(char *str, t_board *b);
int		solve(t_board *b);
int		in_bounds(t_board *b, int x, int y, int v);
int		cell_can(t_board *b, int pos, int v);
int		line_fits(t_line *l);
void	print_grid(t_board *b);
void	put_error(void);

#endif
