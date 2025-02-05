/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:19:50 by acancel           #+#    #+#             */
/*   Updated: 2025/02/05 15:35:00 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	kb_event(int key, t_minirt *mini)
{
	float	move_speed;
	t_vec3	up ;

	up = (t_vec3){0, 1, 0};
	move_speed = 0.5;
	if (key == ESC_KB)
	{
		mlx_loop_end(mini->img.mlx_ptr);
		return (0);
	}
	if (key == W_KB)
		move_camera(mini, mini->cam.direction, move_speed);
	else if (key == S_KB)
		move_camera(mini, mini->cam.direction, -move_speed);
	else if (key == A_KB)
		move_camera(mini, cross_vec3(up, mini->cam.direction), -move_speed);
	else if (key == D_KB)
		move_camera(mini, cross_vec3(up, mini->cam.direction), move_speed);
	else if (key == R_KB)
		move_camera(mini, up, move_speed);
	else if (key == F_KB)
		move_camera(mini, up, -move_speed);
	mini->to_redraw = true;
	return (0);
}

void	mlx_launch_event_and_loop(t_img *img, t_minirt *mini)
{
	mlx_hook(img->win_ptr, 02, 1L << 0, kb_event, img);
	mlx_loop_hook(img->mlx_ptr, draw_image, mini);
	mlx_hook(img->win_ptr, 17, 0L, mlx_loop_end, img->mlx_ptr);
	mlx_loop(img->mlx_ptr);
}
