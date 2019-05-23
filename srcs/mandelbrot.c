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
			fractol->z_i < 4 && fractol->it < fractol->it_max)
	{
		fractol->tmp = fractol->z_r;
		fractol->z_r = fractol->z_r * fractol->z_r -
			fractol->z_i * fractol->z_i + fractol->c_r;
		fractol->z_i = 2 * fractol->z_i * fractol->tmp + fractol->c_i;
		fractol->it++;
	}
	if (fractol->it == fractol->it_max)
		fill_pxl(fractol, fractol->x, fractol->y, 0x000000);
	else
		fill_pxl(fractol, fractol->x, fractol->y, (fractol->color * fractol->it));
}


void	*mandel(void *arg)
{
	t_env		*mandel;
	int			tmp;

	mandel = (t_env *)arg;
	mandel->x = 0;
	tmp = mandel->y;
	while (mandel->x < 599)
	{
		mandel->y = tmp;
		while (mandel->y < mandel->y_max)
		{
			mandelbrot_calc(mandel);
			mandel->y++;
		}
		mandel->x++;
	}
	return (NULL);
}

void	make_mandelbrot(t_env *fractol)
{
	int i;
	t_env		env[THREAD_NUMBER];
	pthread_t	threads[THREAD_NUMBER];

	i = 0;
	while (i < THREAD_NUMBER)
	{
		ft_memcpy((void *)&env[i], (void *)fractol, sizeof(t_env));
		env[i].y = THREAD_WIDTH * i;
		env[i].y_max = THREAD_WIDTH * (i + 1);
		pthread_create(&threads[i], NULL, mandel, &env[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img, 0, 0);	
}
