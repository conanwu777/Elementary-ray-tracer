/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:02:52 by cwu               #+#    #+#             */
/*   Updated: 2018/06/06 17:02:53 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			refresh(t_vars *vp)
{
	int i;

	i = -1;
	while (++i < W * H)
	{
		vp->depth[i] = INT_MAX;
		((unsigned int*)vp->str)[i] = 0;
	}
	vp->c_ob = vp->obj;
	while (vp->c_ob < vp->obj + vp->n_ob)
	{
		draw_ob(vp);
		vp->c_ob++;
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img, 0, 0);
}

int				k_control(int key, void *ptr)
{
	t_vars *vp;

	vp = (t_vars*)ptr;
	if (key == 53)
		exit(1);
	if (key == 49)
		vp->mode = (vp->mode == 2) ? 0 : vp->mode + 1;
	if (key == 123 || key == 124)
		vp->eye.x += (key == 123 ? -50 : 50);
	if (key == 125 || key == 126)
		vp->eye.y += (key == 125 ? -50 : 50);
	if (key == 13 || key == 1)
		vp->rot.x += (key == 13 ? -0.1 : 0.1);
	if (key == 0 || key == 2)
		vp->rot.y += (key == 0 ? 0.1 : -0.1);
	if (key == 43 || key == 47)
		vp->eye.z += (key == 43 ? 50 : -50);
	refresh(vp);
	return (1);
}

int				exp_hook(void *ptr)
{
	t_vars *vp;

	vp = (t_vars*)ptr;
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img, 0, 0);
	return (0);
}

t_pt			o(void)
{
	t_pt p;

	p.x = 0;
	p.y = 0;
	p.z = 0;
	return (p);
}

int				main(int ac, char **av)
{
	t_vars	vars;
	int		db;

	if (ac != 2)
		return (ft_printf("Invalid Number of Arguments"));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, W, H, "RTv1");
	vars.img = mlx_new_image(vars.mlx, W, H);
	vars.str = mlx_get_data_addr(vars.img, &db, &db, &db);
	vars.depth = (float*)malloc(sizeof(float) * W * H);
	vars.rot = o();
	vars.sd = 400;
	vars.mode = 0;
	if (read_map(&vars, av[1]) == false)
		return (ft_printf("Invalid File"));
	refresh(&vars);
	mlx_hook(vars.win, 2, 0, &k_control, (void*)(&vars));
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_expose_hook(vars.win, exp_hook, (void *)(&vars));
	mlx_loop(vars.mlx);
	return (0);
}
