/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:22:16 by cwu               #+#    #+#             */
/*   Updated: 2018/06/06 17:22:17 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_pt			cam_rot(t_pt p, float rx, float ry)
{
	p = rot_x(p, rx);
	p = rot_y(p, ry);
	return (p);
}

t_pt			rot_x(t_pt p, float theta)
{
	t_pt res;

	res.x = p.x;
	res.y = p.y * cos(theta) - p.z * sin(theta);
	res.z = p.y * sin(theta) + p.z * cos(theta);
	return (res);
}

t_pt			rot_y(t_pt p, float theta)
{
	t_pt res;

	res.x = p.x * cos(theta) - p.z * sin(theta);
	res.y = p.y;
	res.z = p.x * sin(theta) + p.z * cos(theta);
	return (res);
}

t_pt			rot_z(t_pt p, float theta)
{
	t_pt res;

	res.x = p.x * cos(theta) - p.y * sin(theta);
	res.y = p.x * sin(theta) + p.y * cos(theta);
	res.z = p.z;
	return (res);
}

t_pt			cy_rot(t_obj obj, t_pt p)
{
	t_pt res;

	obj.v.z = (obj.v.z == 0 ? 0.001 : obj.v.z);
	obj.v.x = (obj.v.x == 0 ? 0.001 : obj.v.x);
	res = rot_x(p, PI / 2 - atan(-obj.v.y / obj.v.z));
	res = rot_z(res, PI / 2 - atan(-pow(pow(obj.v.y, 2)
		+ pow(obj.v.z, 2), 0.5) / obj.v.x));
	return (res);
}
