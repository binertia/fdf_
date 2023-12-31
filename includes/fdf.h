/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:10:10 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/09/01 16:50:45 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H
#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 1920
#define HEIGHT 1080

#define ARROW_LEFT 123
#define ARROW_RIGHT 124
#define ARROW_DOWN 125
#define ARROW_UP 126
#define MINUS 27
#define PLUS 24
#define SPACE 49
#define KEY_R 15
#define MOUSE_CLICK_LEFT 1
#define MOUSE_CLICK_RIGHT 2
#define MOUSE_CLICK_MIDDLE 3
#define MOUSE_WHEEL_UP 4
#define MOUSE_WHEEL_DOWN 5
#define ESCAPE 53

typedef struct s_point
{
	int x;
	int y;
	int z;
	int color;
	int reverse;
} t_point;

typedef struct s_map
{
	int height;
	int width;
	int ***array;
	int z_max;
	int z_min;
} t_map;

typedef struct s_camera
{
	int zoom;
	double x_angle;
	double y_angle;
	double z_angle;
	float z_height;
	int x_offset;
	int y_offset;
	int iso;
} t_camera;

typedef struct s_mouse
{
	int button;
	int x;
	int y;
	int prev_x;
	int prev_y;
} t_mouse;

typedef struct s_fdf
{
	void *mlx;
	void *win;
	void *img;
	char *data_addr;
	int bpp;
	int size_line;
	int endian;
	int steep;
	t_map *map;
	t_camera *camera;
	t_mouse *mouse;
} t_fdf;

#endif
