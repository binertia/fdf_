#include "includes/fdf.h"

// Fixed-point scaling factor
#define FIXED_SCALE 16

typedef struct s_data
{
    void *mlx;
    void *win;
    int x1, y1; // Starting point
    int x2, y2; // Ending point
} t_data;

void draw(t_data *ref)
{
    int steps, k;
    int dx, dy, xIncrement, yIncrement, x, y;

    dx = (ref->x2 - ref->x1) << FIXED_SCALE; // Convert to fixed-point
    dy = (ref->y2 - ref->y1) << FIXED_SCALE; // Convert to fixed-point

    if (abs(dx) > abs(dy)) {
        steps = abs(dx >> FIXED_SCALE); // Convert back to integer
    } else {
        steps = abs(dy >> FIXED_SCALE); // Convert back to integer
    }

    xIncrement = dx / steps;
    yIncrement = dy / steps;

    x = ref->x1 << FIXED_SCALE; // Convert to fixed-point
    y = ref->y1 << FIXED_SCALE; // Convert to fixed-point

    mlx_pixel_put(ref->mlx, ref->win, x >> FIXED_SCALE, y >> FIXED_SCALE, 0xFF0000); // Convert back to integer

    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        mlx_pixel_put(ref->mlx, ref->win, x >> FIXED_SCALE, y >> FIXED_SCALE, 0xFF0000); // Convert back to integer
    }
}

int main(int ac, char *av[])
{
    if (ac < 3)
    {
        printf("Usage: %s x1 y1\n", av[0]);
        return 1;
    }

    t_data squair;
    squair.mlx = mlx_init();
    squair.win = mlx_new_window(squair.mlx, 800, 600, "MiniLibX Example");
    squair.x1 = atoi(av[1]);
    squair.y1 = atoi(av[2]);
    squair.x2 = 400; // Ending point
    squair.y2 = 400; // Ending point
    draw(&squair);
    mlx_loop(squair.mlx);
    return 0;
}

