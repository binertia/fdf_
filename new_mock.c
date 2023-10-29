#include "includes/fdf.h"

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int get_rgb(int r, int g, int b) { return (r << 16 | g << 8 | b); }

// int get_gradien(int color, int range, int current)
// {
// 	int res;
//
// 	res = ((int)(((double)current / range) * 16777215));
//
// 	return (color + (res));
// }
int add_shade(int color, double shade)
{
	color = color + (shade * 255) * 0x01000000;
	return (color);
}

// rainbow version;
int get_gradien(int color, int range, int current)
{
	int res;
	double calc;

	calc = ((double)current / range);
	if (calc < 0.201)
		return (color + (int)(calc * 5 * 255) * 0x100);
	else if (calc > 0.200 && calc < 0.401)
		return (color + 0xFF00 - ((int)((calc - 0.2) * 5 * 255) * 0x010000));
	else if (calc > 0.400 && calc < 0.601)
		return (0xFF00 + ((int)((calc - 0.4) * 5 * 255) * 0x1));
	else if (calc > 0.600 && calc < 0.801)
		return 0xFFFFFF - (0xFFFF - ((int)((calc - 0.6) * 5 * 255) * 0x100));
	else
		return 0xFFFFFF - (0xFF + ((int)((calc)-0.8) * 5 * 255) * 0x10000);
}

void draw_square(void *mlx, int center, int range, int color)
{
	int x_start;
	int x_end;
	int y_start;
	int y_end;
	int temp;

	y_start = center - range;
	y_end = center + range;
	temp = y_start;

	while (y_start <= y_end)
	{
		x_start = center - range;
		x_end = center + range;
		while (x_start <= x_end)
		{
			if (y_start <= y_end && x_start <= x_end)
				my_mlx_pixel_put(mlx, x_start, y_start,
								 get_gradien(color, range * 2, y_start - temp));
			x_start++;
		}
		y_start++;
	}
	return;
}

void draw_circle(void *img, int center, int radius, int color)
{
	int x;
	int y;

	y = center - radius;
	while (y <= center + radius)
	{
		x = center - radius;
		while (x <= center + radius)
		{
			if (radius * radius >=
				(center - x) * (center - x) + (center - y) * (center - y))
				my_mlx_pixel_put(
					img, x, y,
					get_gradien(color, radius * 2, y - (center - radius)));
			x++;
		}
		y++;
	}
	y = center - 30;
	while (y <= center)
	{
		x = center - radius;
		while (x <= center + radius)
		{
			if (x % 2 == 0)
				my_mlx_pixel_put(img, x, y, 0x003412);
			x++;
		}
		y++;
	}
}

typedef struct s_vars
{
	void *mlx;
	void *win;
} t_vars;

int main(void)
{
	void *mlx;
	t_data img;
	t_vars vars;
	int	x;
	int	y;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 480, 420, "Hello world!"); // max 1680, 1020
	img.img = mlx_new_image(vars.mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	// draw_square(&img, 550, 300, get_rgb(255, 0, 0));
	draw_circle(&img, 400, 400, 0xFF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 0, win_close, &vars);
	mlx_key_hook(vars.win, print_key, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_mouse_hook(vars.win, handle_mouse_click, NULL);
	mlx_mouse_hook(vars.win, handle_move, NULL);
	mlx_loop(vars.mlx); 
}
