/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mlx.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:29:23 by acancel           #+#    #+#             */
/*   Updated: 2025/02/05 15:33:16 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_MLX_H
# define DISPLAY_MLX_H

# define WIDTH_WIN 720 /* WIDTH of MLX WIN */
# define HEIGHT_WIN 540 /* HEIGHT of MLX WIN */
# define ESC_KB 65307 /* ESC BUTTON */
# define LEFT_KB 65361 /* LEFT BUTTON */
# define RIGHT_KB 65363 /* RIGHT BUTTON */
# define UP_KB 65362 /* UP BUTTON */
# define DOWN_KB 65364 /* DOWN BUTTON */
# define W_KB 119 /* W BUTTON */
# define A_KB 97 /* A BUTTON */
# define S_KB 115 /* S BUTTON */
# define D_KB 100 /* D BUTTON */
# define R_KB 114 /* R BUTTON */
# define F_KB 102 /* F BUTTON */
# define Q_KB 113 /* Q BUTTON */
# define E_KB 101 /* E BUTTON */
# include <mlx.h>

typedef struct s_minirt	t_minirt;

typedef struct s_img
{
	void	*img;
	void	*mlx_ptr;
	void	*win_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

int		mlx_init_protected(t_img *img);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	mlx_launch_event_and_loop(t_img *img, t_minirt *mini);
void	mlx_destroy_all(t_img *img);
int		kb_event(int key, t_minirt *mini);

#endif	