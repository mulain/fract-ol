/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:41:46 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/14 21:10:40 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_release(int key, t_env *e)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		my_exit(e, 0);
	}
	if (key == KEY_LEFT || key == KEY_UP || key == KEY_RIGHT || key == KEY_DOWN)
		move_key(e, key);
	if (key == KEY_W || key == KEY_S)
		mod_iter(e, key);
	if (key == KEY_I)
		mod_inside_set(e);
	if (key == KEY_O)
		mod_outside_set(e);
	if (key == KEY_C)
		mod_color(e);
	return (0);
}

/*
To retrieve mapped coordinates of the mouse (e.g. when looking for Julia sets),
paste this:

if (button == MOUSE_MIDDLE)
		printf("mouse_x:%f\nmouse_y:%f\n", e->x_mappd, e->y_mappd);

Can't keep it because printf is needed to print float.
*/
int	mouse_press(int button, int mouse_x, int mouse_y, t_env *e)
{
	map_pxl(e, mouse_x, mouse_y);
	if (button == MOUSE_LEFT)
	{
		e->mouse_press_x = mouse_x;
		e->mouse_press_y = mouse_y;
	}
	if (button == MOUSE_SCR_UP)
		zoom(e, 1);
	if (button == MOUSE_SCR_DOWN)
		zoom(e, 0);
	return (0);
}

int	mouse_release(int button, int mouse_x, int mouse_y, t_env *e)
{
	int		threshold;

	threshold = 5;
	map_pxl(e, mouse_x, mouse_y);
	if (button == MOUSE_LEFT)
	{
		e->mouse_release_x = mouse_x;
		e->mouse_release_y = mouse_y;
		if (calc_absolute_int(e->mouse_press_x - mouse_x) < threshold
			&& calc_absolute_int(e->mouse_press_y - mouse_y) < threshold)
			zoom(e, 1);
		else
			move_mouse(e);
	}
	if (button == MOUSE_RIGHT)
		zoom(e, 0);
	return (1);
}
