#ifndef FRACTOL_H
#define FRACTOL_H
#include <math.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <mlx.h>
#include <pthread.h>
#include "../libft/libft.h"
#include <stdio.h>
#define HEIGHT 1000
#define WIDTH 1000
#define USAGE "Usage : ./fractol [id_fractale][width] [height]"

typedef enum
{
	julia, mandelbrot, burningship
}					e_fractale;

typedef struct s_env
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	unsigned int *img_data;
	char 	**argv;
	int		psych_mod;
	int		width;
	int 	height;
	int		bpp;
	int		size_line;
	int		endian;
	int		mouse;
	int		x;
	int		y;
	int		iter_max;
	int 	show_text;
	int		it;
	double 	zoom;
	double	tmp;	
	unsigned int	color;
	double 	x1;
	double 	y1;
	double c_r;
	double c_i;
	double z_r;
	double z_i;
	e_fractale 	id_fractale;
}				t_env;


typedef struct s_envtab
{
	t_env *f_env;
}
t_tab;



void	handle_events(t_env *fractol);
void 	init_mandel(t_env *fractol);
void	make_julia(t_env *fractol);
void	make_mandelbrot(t_env *fractol);
void	make_burningship(t_env *fractol);
void	mandelbrot_calc(t_env *fractol);
void	julia_calc(t_env *fractol);
void	burningship_calc(t_env *fractol);
void	fill_pxl(t_env *fractol, int x, int y, int color);
void	init_win(t_env *fractol);
void	init_julia(t_env *fractol);
void	init_mandel(t_env *fractol);
void	init_burn(t_env *fractol);
void	init_fractol(t_env *fractol, char **argv);
//void	(*make_fractale[3])(t_env *) = {make_julia, make_mandelbrot, make_burningship};
int		julia_mouse(int x, int y, t_env *fractol);
int 	ft_close(void);


#endif
