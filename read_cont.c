/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cont.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:38:19 by cwu               #+#    #+#             */
/*   Updated: 2018/06/06 17:40:54 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

bool	properties_cont(t_vars *vp, char **line)
{
	if (ft_strncmp(*line, "vector", 6) == 0)
	{
		vp->c_ob->v.x = ft_atoi(*line + 6);
		vp->c_ob->v.y = ft_atoi(*line + 7 + num_len(vp->c_ob->v.x));
		vp->c_ob->v.z = ft_atoi(*line + 8 + num_len(vp->c_ob->v.x)
		+ num_len(vp->c_ob->v.y));
		return (false);
	}
	if (ft_strncmp(*line, "radius", 6) == 0)
	{
		vp->c_ob->r = ft_atoi(*line + 6);
		return (false);
	}
	if (ft_strncmp(*line, "color", 5) == 0)
	{
		vp->c_ob->color = (unsigned int)ft_atoi_base(*line + 5, 16);
		return (false);
	}
	return (true);
}

bool	check_properties(t_vars *vp, char **line)
{
	if (ft_strncmp(*line, "center", 6) == 0)
	{
		vp->c_ob->c.x = ft_atoi(*line + 6);
		vp->c_ob->c.y = ft_atoi(*line + 7 + num_len(vp->c_ob->c.x));
		vp->c_ob->c.z = ft_atoi(*line + 8 + num_len(vp->c_ob->c.x)
		+ num_len(vp->c_ob->c.y));
		return (false);
	}
	if (ft_strncmp(*line, "normal", 6) == 0)
	{
		vp->c_ob->normal.x = ft_atoi(*line + 6);
		vp->c_ob->normal.y = ft_atoi(*line + 7 + num_len(vp->c_ob->normal.x));
		vp->c_ob->normal.z = ft_atoi(*line + 8 + num_len(vp->c_ob->normal.x)
		+ num_len(vp->c_ob->normal.y));
		return (false);
	}
	return (properties_cont(vp, line));
}

void	light_properties(int fd, t_vars *vp, char **line)
{
	ft_gnl(fd, line);
	if (vp->c_l > vp->n_l)
		return ;
	vp->li[vp->c_l].x = ft_atoi(*line + 6);
	vp->li[vp->c_l].y = ft_atoi(*line + 7 +
	num_len(vp->li[vp->c_l].x));
	vp->li[vp->c_l].z = ft_atoi(*line + 8 +
	num_len(vp->li[vp->c_l].x) + num_len(vp->li[vp->c_l].y));
	free(*line);
	ft_gnl(fd, line);
	vp->li[vp->c_l].sx = (unsigned int)ft_atoi_base(*line + 5, 16);
}

bool	shape_cont(int fd, t_vars *vp, char **line)
{
	if (ft_strcmp(*line, "cone") == 0)
	{
		vp->c_ob->intersect = intersect_cone;
		vp->c_ob->light = cone_light;
		return (false);
	}
	if (ft_strcmp(*line, "light") == 0)
	{
		vp->c_ob--;
		free(*line);
		light_properties(fd, vp, line);
		vp->c_l++;
		return (false);
	}
	return (true);
}

bool	check_shape(int fd, t_vars *vp, char **line)
{
	if (ft_strcmp(*line, "sphere") == 0)
	{
		vp->c_ob->intersect = intersect_sphere;
		vp->c_ob->light = sphere_light;
		return (false);
	}
	if (ft_strcmp(*line, "plane") == 0)
	{
		vp->c_ob->intersect = intersect_plane;
		vp->c_ob->light = plane_light;
		return (false);
	}
	if (ft_strcmp(*line, "cylinder") == 0)
	{
		vp->c_ob->intersect = intersect_cylinder;
		vp->c_ob->light = cylinder_light;
		return (false);
	}
	return (shape_cont(fd, vp, line));
}
