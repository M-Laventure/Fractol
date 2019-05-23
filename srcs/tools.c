#include "../includes/fractol.h"

void	make_fractale(t_env *fractol)
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
			pthread_create(&threads[i], NULL, fractol->id_fractale, &env[i]);
			i++;
		}
		while (i--)
			pthread_join(threads[i], NULL);
		mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img_ptr, 0, 0);	
}

void	fill_pxl(t_env *fractol, int x, int y, int color)
{
	if	(x < fractol->width && y < fractol->height && x >= 0 && y >= 0)
		fractol->img_data[y * WIDTH + x] = color;
}

void	init_win(t_env *fractol, char **argv)
{
	fractol->mlx_ptr = mlx_init();
	fractol->width = ft_atoi(argv[2]);
	fractol->height = ft_atoi(argv[3]);
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, fractol->width, fractol->height, "Fractol");
	fractol->img = mlx_new_image(fractol->mlx_ptr, fractol->width, fractol->height);
	fractol->img_data = (int *)mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
}

void init_fractol(t_env *fractol, char **argv)
{
	init_win(fractol, argv);
	if (ft_strcmp(argv[1], "julia"))
		init_julia(fractol);
	if (ft_strcmp(argv[1], "burningship"))
		init_burn(fractol);	
	if (ft_strcmp(argv[1], "mandelbrot"))
		init_mandel(fractol);
}


