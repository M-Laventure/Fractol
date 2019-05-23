#include "../includes/fractol.h"

void	init_mandel(t_env *fractol)
{
		fractol->id_fractale = mandelbrot;
		fractol->it_max = 50;
		fractol->zoom = 300;
		fractol->x1 = -2.05;
		fractol->y1 = -1.3;
		fractol->color = 265;
}

void	init_julia(t_env *fractol)
{
		fractol->id_fractale = julia;
		fractol->zoom = 200;
		fractol->it_max = 50;
		fractol->x1 = -2.0;
		fractol->y1 = -1.9;
		fractol->color = 265;
		fractol->c_r = 0.285;
		fractol->c_i = 0.01;
		fractol->mouse = 1;
}

void	init_burn(t_env *fractol)
{
		fractol->id_fractale = burningship;
		fractol->it_max = 50;
		fractol->zoom = 220;
		fractol->x1 = -2.2;
		fractol->y1 = -2.5;
		fractol->color = 265;
}

