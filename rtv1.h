/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 02:17:11 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/06 17:03:20 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <limits.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include <stdbool.h>
# define PIX mlx_pixel_put
# define STR mlx_string_put
# define W 1600
# define H 1200
# define PI 3.1415926

typedef struct		s_vars t_vars;
typedef struct		s_obj t_obj;

typedef struct		s_pt
{
	int				sx;
	int				sy;
	float			x;
	float			y;
	float			z;
}					t_pt;

typedef struct		s_x
{
	float			l;
	t_pt			normal;
}					t_x;

typedef struct		s_obj
{
	t_pt			c;
	t_pt			v;
	float			r;
	t_pt			normal;
	unsigned int	color;
	float			(*intersect)(t_obj obj, t_pt p, t_pt v);
	unsigned int	(*light)(t_vars *vp, t_pt p);
}					t_obj;

typedef struct		s_vars
{
	unsigned char	mode;
	void			*mlx;
	void			*win;
	void			*img;
	char			*str;
	float			*depth;
	float			sd;
	t_obj			*obj;
	int				n_ob;
	t_obj			*c_ob;
	t_pt			eye;
	t_pt			rot;
	int				n_l;
	int				c_l;
	t_pt			*li;
}					t_vars;

unsigned int		add_color(unsigned int c1, unsigned int c2);
unsigned int		div_color(int div, unsigned int color);
unsigned int		t_color(float t, unsigned int c_st, unsigned int c_ed);
t_pt				vector(t_pt a, t_pt b);
int					ptos(t_pt p);
int					max(int a, int b, int c);
float				norm(t_pt p);
t_pt				v_scale(t_pt p, float l);
t_pt				add_points(t_pt p, t_pt q);
t_pt				neg_point(t_pt pt);
t_pt				translate(t_pt p, t_pt m);
t_pt				rot_x(t_pt p, float theta);
t_pt				rot_y(t_pt p, float theta);
t_pt				rot_z(t_pt p, float theta);
t_pt				cam_rot(t_pt p, float rx, float ry);
void				draw_ob(t_vars *vp);
float				intersect_sphere(t_obj obj, t_pt p, t_pt v);
float				intersect_plane(t_obj obj, t_pt p, t_pt v);
float				intersect_cylinder(t_obj obj, t_pt p, t_pt v);
float				intersect_cone(t_obj obj, t_pt p, t_pt v);
unsigned int		sphere_light(t_vars *vp, t_pt p);
unsigned int		plane_light(t_vars *vp, t_pt p);
unsigned int		cylinder_light(t_vars *vp, t_pt p);
unsigned int		cone_light(t_vars *vp, t_pt p);
bool				read_map(t_vars *vp, char *file);
void				check_for_shadow(t_vars *vp, t_pt p, int i);
t_pt				cy_rot(t_obj obj, t_pt p);
bool				check_properties(t_vars *vp, char **line);
bool				check_shape(int fd, t_vars *vp, char **line);
int					num_len(int num);
int					ft_atoi_base(const char *str, int str_base);

#endif
