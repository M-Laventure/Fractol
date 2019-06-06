#include "../includes/fractol.h"

void	burningship_calc(t_env *fractol)
{

	fractol->c_r = fractol->x / fractol->zoom + fractol->x1;
	fractol->c_i = fractol->y / fractol->zoom + fractol->y1;
	//printf("%f\n", fractol->c_r);
	fractol->z_r = 0;
	fractol->z_i = 0;
	fractol->it = 0;
	while (fractol->z_r * fractol->z_r + fractol->z_i * fractol->z_i < 4
			&& fractol->it < fractol->iter_max)
	{
		fractol->tmp = fractol->z_r * fractol->z_r - fractol->z_i * fractol->z_i + fractol->c_r;
		fractol->z_i = fabs(2 * fractol->z_r * fractol->z_i) + fractol->c_i;
		fractol->z_r = fractol->tmp;
		fractol->it++;
	}
	if (fractol->it == fractol->iter_max)
		fill_pxl(fractol, fractol->x, fractol->y, 0x000000);
	else
	{
		if (fractol->psych_mod == 1)
			fill_pxl(fractol, fractol->x, fractol->y, fractol->it * (fractol->color / fractol->iter_max));
		else
			fill_pxl(fractol, fractol->x, fractol->y, fractol->it * fractol->color);
	}
}

void	*burning(void *fractol)
{	
	t_env	*burn;

	burn = (t_env *)fractol;
	burn->x = 0;
	while (burn->x < burn->width)
	{
		burningship_calc(burn);
		burn->x++;
	}
	return (NULL);
}

/*typedef struct s_envtab
{
	t_env *f_env;
	int y_max;
}				t_tab;*/


void	make_burningship(t_env *fractol)
{
		int i;
		t_env		env[fractol->height];
		pthread_t	threads[fractol->height];

		i = 0;
		while (i < fractol->height)
		{
			ft_memcpy((void *)&env[i], (void *)fractol, sizeof(t_env));
			env[i].y = i;
			pthread_create(&threads[i], NULL, burning, &env[i]);
			i++;
		}
		while (i--)
			pthread_join(threads[i], NULL);
		mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img, 0, 0);
}

/*
void	make_burningship(t_env *fractol)
{
		printf("IN\n");
		int i;
		t_env		env[THREAD_NUMBER];
	//	t_tab		env_tab[HEIGHT];
		pthread_t	threads[THREAD_NUMBER];
		
	
		i = 0;
	//	while (i < HEIGHT)
		while (i < THREAD_NUMBER)
		{
			//env_tab[i].f_env = fractol;
			ft_memcpy((void *)&env[i], (void *)fractol, sizeof(t_env));
			env[i].y = THREAD_WIDTH * i;
			//env_tab[i].f_env->y = i;
			//env_tab[i].f_env->y_max = HEIGHT - 1;
			env[i].y_max = THREAD_WIDTH * (i + 1);
			//printf("env.y_max: %d\n", env[i].y_max);	
			//pthread_create(&threads[i], NULL, burning, &env_tab[i]);
			pthread_create(&threads[i], NULL, burning, &env[i]);
			i++;
		}
		while (i--)
			pthread_join(threads[i], NULL);
		mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img, 0, 0);	
}*/


