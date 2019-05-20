#ifndef FRACTOL_H
#define FRACTOL_H
#include <math.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <mlx.h>
#include <pthread.h>
#include "../libft/libft.h"
#define ITER_MAX 50
#define WIDTH 600
#define THREAD_WIDTH 5
#define THREAD_NUMBER 120
#define USAGE "Usage : ./fractol [id_fractale][width] [height]"


typedef enum
{
	julia, mandelbrot, burningship
}					e_fractale;

typedef struct s_env
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int 	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	int		x;
	int		y;
	int		it_max;
	int		iter;
	double 	zoom;
	double	tmp;	
	int y_max;
	int		color;
	double 	x1;
	double 	y1;
	double c_r;
	double c_i;
	double z_r;
	double z_i;
	e_fractale 	id_fractale;
}				t_env;

/*typedef	struct	s_tdata
{
	int		y;
	t_env	*env;
}				t_tdata;*/


void	handle_events(t_env *fractol);
void 	init_mandel(t_env *fractol);
void	make_mandelbrot(t_env *fractol);
void	make_julia(t_env *fractol);
void	make_burningship(t_env *fractol);
void	fill_pxl(t_env *fractol, int x, int y, int color);
void	init_win(t_env *fractol, char **argv);
void	init_fractol(t_env *fractol, char **argv);

#endif
