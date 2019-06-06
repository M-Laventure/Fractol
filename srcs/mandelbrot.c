#include "../includes/fractol.h"
#include <stdio.h>

void	mandelbrot_calc(t_env *fractol)
{
	fractol->c_r = fractol->x / fractol->zoom + fractol->x1;
	fractol->c_i = fractol->y / fractol->zoom + fractol->y1;
	fractol->z_r = 0;
	fractol->z_i = 0;
	fractol->it = 0;
	while (fractol->z_r * fractol->z_r + fractol->z_i *
			fractol->z_i < 4 && fractol->it < fractol->iter_max)
	{
		fractol->tmp = fractol->z_r;
		fractol->z_r = fractol->z_r * fractol->z_r -
			fractol->z_i * fractol->z_i + fractol->c_r;
		fractol->z_i = 2 * fractol->z_i * fractol->tmp + fractol->c_i;
		fractol->it++;
	}
	if (fractol->it == fractol->iter_max)
		fill_pxl(fractol, fractol->x, fractol->y, 0x000000);
	else
		fill_pxl(fractol, fractol->x, fractol->y, (fractol->color * fractol->it));
}


void	*mandel(void *arg)
{
	t_env		*mandel;

	mandel = (t_env *)arg;
	mandel->x = 0;
	while (mandel->x < WIDTH)
	{
		mandelbrot_calc(mandel);
		mandel->x++;
	}
//	pthread_exit(NULL);
	return (NULL);
}

void	make_mandelbrot(t_env *fractol)
{
	int i;
	t_env		env[HEIGHT];
	pthread_t	threads[HEIGHT];

	i = 0;
	while (i < HEIGHT)
	{
		ft_memcpy((void *)&env[i], (void *)fractol, sizeof(t_env));
		env[i].y = i;
		pthread_create(&threads[i], NULL, mandel, &env[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img, 0, 0);	
}
