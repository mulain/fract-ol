/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:12:50 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/14 17:58:33 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
Draws the Sierpinski Triangle - but using circles!
This version works with pixel by pixel calculation, but
is insanely slow because of it.
*/
int	sierpcircle_slow(t_env *e)
{
	e->in_sierp = 0;
	sierphelper_slow(e, e->r_start, 0, 0);
	if (e->in_sierp)
		return (0x00FFFFFF);
	return (0);
}

void	sierphelper_slow(t_env *e, double r, double x, double y)
{
	double		delta;

	if (r > e->r_min)
	{
		sierphelper_slow(e, r / 2, x - r * e->factor, y);
		sierphelper_slow(e, r / 2, x + r * e->factor, y);
		sierphelper_slow(e, r / 2, x, y + r * e->factor);
	}
	if ((e->x_mappd > x - r - e->line && e->x_mappd < x + r + e->line)
		&& (e->y_mappd > y - r - e->line
			&& e->y_mappd < y + r + e->line))
	{
		delta = (e->x_mappd - x) * (e->x_mappd - x)
			+ (e->y_mappd - y) * (e->y_mappd - y) - r * r;
		if (delta < r * e->line && delta > -(r * e->line))
			e->in_sierp = 1;
	}
}
