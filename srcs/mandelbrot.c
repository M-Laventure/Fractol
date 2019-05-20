#include "../includes/fractol.h"
#include <stdio.h>


void	mandel_color(t_env	*mandel)
{
//	double tmp;

	mandel->c_r = mandel->x / mandel->zoom + mandel->x1;
	mandel->c_i = mandel->y / mandel->zoom + mandel->y1;
	mandel->z_r = 0;
	mandel->z_i = 0;
	mandel->iter = 0;
	while ((mandel->z_r * mandel->z_r) + (mandel->z_i * mandel->z_i) < 4  && mandel->iter < mandel->it_max)
	{
		mandel->tmp = mandel->z_r;
		mandel->z_r = mandel->z_r * mandel->z_r - mandel->z_i * mandel->z_i + mandel->c_r;
		mandel->z_i = 2 * mandel->z_i * mandel->tmp + mandel->c_i;
		mandel->iter++;
	}
	if (mandel->iter == mandel->it_max)
	{
	//	printf("x: %d\n", mandel->x);
	//	printf("y: %d\n", mandel->y);
		fill_pxl(mandel, mandel->x, mandel->y, 0x000000);
	}
	else
	{
	//	printf("x: %d\n", mandel->x);
	//	printf("y: %d\n", mandel->y);
		fill_pxl(mandel, mandel->x, mandel->y, 0);
	}
}


/*
   typedef struct	s_tdata
   {
   int		x;
   t_env	*env;
   }				t_tdata;
   */

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
			mandel_color(mandel);
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



