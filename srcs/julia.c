#include "../includes/fractol.h"

void	julia_calc(t_env *julia)
{
	julia->z_r = julia->x / julia->zoom + julia->x1;
	julia->z_i = julia->y / julia->zoom + julia->y1;
	julia->it = 0;
	while (julia->z_r * julia->z_r + julia->z_i
			* julia->z_i < 4 && julia->it < julia->iter_max)
	{
		julia->tmp = julia->z_r;
		julia->z_r = julia->z_r * julia->z_r -
			julia->z_i * julia->z_i - 0.8 + (julia->c_r / WIDTH);
		julia->z_i = 2 * julia->z_i * julia->tmp + julia->c_i / WIDTH;
		julia->it++;
	}
	if (julia->it == julia->iter_max)
		fill_pxl(julia, julia->x, julia->y, 0x000000);
	else
		fill_pxl(julia, julia->x, julia->y, (julia->color * julia->it));
}

void	*jul(void *fractol)
{
	t_env	*julia;

	julia = (t_env *)fractol;
	julia->x = 0;
	while (julia->x < WIDTH)
	{
		julia_calc(julia);
		julia->x++;
	}
	return (fractol);
}




void	make_julia(t_env *fractol)
{
	int i;
	t_env		env[HEIGHT];
	pthread_t	threads[HEIGHT];

	i = 0;
	while (i < HEIGHT)
	{
		ft_memcpy((void *)&env[i], (void *)fractol, sizeof(t_env));
		env[i].y = i;
		pthread_create(&threads[i], NULL, jul, &env[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img, 0, 0);	
}

int	julia_mouse(int x, int y, t_env *fractol)
{
	if (fractol->id_fractale == 0 && fractol->mouse == 1)
	{
		fractol->c_r = x * 2;
		fractol->c_i = y * 2 - 800;
		make_julia(fractol);
	}
	return (0);
}

