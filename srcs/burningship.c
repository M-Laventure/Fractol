#include "../includes/fractol.h"


void	*burning(void *fractol)
{
	int		tmp;
	t_env	*burn;

	burn = (t_env *)fractol;
	burn->x = 0;
	tmp = burn->y;
	while (burn->x < WIDTH)
	{
		burn->y = tmp;
		while (burn->y < burn->y_max)
		{
			burningship_calc(burn);
			burn->y++;
		}
		burn->x++;
	}
	return (NULL);
}

void	make_burningship(t_env *fractol)
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
			pthread_create(&threads[i], NULL, burning, &env[i]);
			i++;
		}
		while (i--)
			pthread_join(threads[i], NULL);
		mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img, 0, 0);	
}

void	burningship_calc(t_env *fractol)
{
	fractol->c_r = fractol->x / fractol->zoom + fractol->x1;
	fractol->c_i = fractol->y / fractol->zoom + fractol->y1;
	fractol->z_r = 0;
	fractol->z_i = 0;
	fractol->it = 0;
	while (fractol->z_r * fractol->z_r + fractol->z_i * fractol->z_i < 4
			&& fractol->it < fractol->it_max)
	{
		fractol->tmp = fractol->z_r * fractol->z_r - fractol->z_i * fractol->z_i + fractol->c_r;
		fractol->z_i = fabs(2 * fractol->z_r * fractol->z_i) + fractol->c_i;
		fractol->z_r = fractol->tmp;
		fractol->it++;
	}
	if (fractol->it == fractol->it_max)
		fill_pxl(fractol, fractol->x, fractol->y, 0x000000);
	else
		fill_pxl(fractol, fractol->x, fractol->y, (fractol->color * fractol->it));
}

