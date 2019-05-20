#include "../includes/fractol.h"

void	init_mandel(t_env *mandel)
{
	mandel->it_max = 50;
	mandel->zoom = 300;
	mandel->x1 = -2.05;
	mandel->y1 = -1.3;
	mandel->color = 265;
}
