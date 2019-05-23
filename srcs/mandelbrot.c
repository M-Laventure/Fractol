#include "../includes/fractol.h"
#include <stdio.h>

void	mandelbrot_calc(t_fractol *data)
{
	data->c_r = data->x / data->zoom + data->x1;
	data->c_i = data->y / data->zoom + data->y1;
	data->z_r = 0;
	data->z_i = 0;
	data->it = 0;
	while (data->z_r * data->z_r + data->z_i *
			data->z_i < 4 && data->it < data->it_max)
	{
		data->tmp = data->z_r;
		data->z_r = data->z_r * data->z_r -
			data->z_i * data->z_i + data->c_r;
		data->z_i = 2 * data->z_i * data->tmp + data->c_i;
		data->it++;
	}
	if (data->it == data->it_max)
		put_pxl_to_img(data, data->x, data->y, 0x000000);
	else
		put_pxl_to_img(data, data->x, data->y, (data->color * data->it));
}


void	*mandelbrot(void *arg)
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
			mandel_calc(mandel);
			mandel->y++;
		}
		mandel->x++;
	}
	return (NULL);
}

void	mandel_thread(t_env *fractol)
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
		//printf("env.y_max: %d\n", env[i].y_max);		
		pthread_create(&threads[i], NULL, mandel, &env[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img_ptr, 0, 0);	
}

void	make_mandelbrot(t_env *fractol)
{
	init_mandel(fractol);
	mandel_thread(fractol);
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img_ptr, 0, 0);	
//	ft_putendl("here");
}


/*
 ** If z is out of mandelbrot set after the maximum number of iteration, color the current pixel in black
 */



