/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:57:07 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/13 16:37:49 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
This put_pixel is guarded and very slow. Shouldn't use in final
build, mainly for troubleshooting.
*/
void	put_pixel_guarded(t_env *e, int x, int y, int color)
{
	char	*pxl;

	if (x < 0 || y < 0)
	{
		write (1, "put_pixel: Negative input.", 26);
		return ;
	}
	if (x * (e->img_bpp / 8) > e->img_line_length)
	{
		write (1, "put_pixel: x > line length.", 27);
		return ;
	}
	if (y > e->img_height)
	{
		write (1, "put_pixel: y > img height.", 26);
		return ;
	}
	pxl = e->img_addr + (y * e->img_line_length + x * (e->img_bpp / 8));
	*(unsigned int *)pxl = color;
}

/*
Draws a rectangle at coordinates (x;y) with the dimensions (length;height).
Color is passed by the envelope.
*/
void	put_rectangle(t_env *e, int length, int height)
{
	int		x;
	int		y;
	int		color;

	x = 100;
	y = 100;
	color = 0x00FFFFFF;
	while (height > 0)
	{
		while (length > 0)
		{
			put_pixel(e, x + length, y + height, color);
			length--;
		}
		height--;
	}
}

/*
Puts a circle, but assigns (a;b) incorrectly resulting in a visual effect.
*/
void	put_circle_weird(t_env *e, int a, int b, int r)
{
	int		x;
	int		y;
	int		delta;
	int		thickness;

	thickness = 1;
	y = a - r - r * thickness;
	if (y < 0)
		y = 0;
	while (y < a + r + r * thickness && y < e->img_height)
	{
		x = a - r - r * thickness;
		if (x < 0)
			x = 0;
		while (x < e->img_width)
		{
			delta = (x - a) * (x - a) + (y - b) * (y - b) - r * r;
			if (delta < r + r * thickness && delta > -(r + r * thickness))
				put_pixel(e, x, y, e->color);
			x++;
		}
		y++;
	}
}

/* void	put_circle2(t_env *e, int a, int b, int r)
{
	int		x;
	int		y;
	int		delta;
	int		gaussfactor;
	int		i;

	y = 0;
	gaussfactor = 70;
	while (y < e->img_height)
	{
		x = 0;
		while (x < e->img_width)
		{
			i = 5;
			delta = (x - a) * (x - a) + (y - b) * (y - b) - r * r;
			while (i * gaussfactor < 255 && i > -1)
			{
				if (delta < r + r * i && delta > -(r + r * i))
				{
					put_pixel(e, x, y, add_transparency(i * gaussfactor, e->color));
					//my_put_pixel(img, x, y, color);
				}
				i--;
			}
			x++;
		}
		y++;
	}
}
 */