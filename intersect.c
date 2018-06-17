/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:02:40 by cwu               #+#    #+#             */
/*   Updated: 2018/06/06 17:02:41 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			draw_ob(t_vars *vp)
{
	t_pt	p;
	t_pt	p2;
	float	ll;
	int		i;

	p.sy = -H / 2;
	while (++p.sy < H / 2)
	{
		p.sx = -W / 2;
		while (++p.sx < W / 2 && (i = ptos(p)) >= 0)
		{
			p.x = p.sx;
			p.y = p.sy;
			p.z = vp->sd;
			p2 = p;
			p = cam_rot(p, vp->rot.x, vp->rot.y);
			if ((ll = vp->c_ob->intersect(*(vp->c_ob), vp->eye, p)) != -1)
			{
				p2 = v_scale(p2, ll);
				p = translate(v_scale(p, ll), neg_point(vp->eye));
				if (vp->depth[i] > p2.z && (vp->depth[i] = p2.z) == p2.z)
					check_for_shadow(vp, p, i);
			}
		}
	}
}

float			intersect_sphere(t_obj obj, t_pt p, t_pt v)
{
	float a;
	float b;
	float c;
	float det;
	float tmp;

	p = translate(p, obj.c);
	a = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
	b = 2 * (p.x * v.x + p.y * v.y + p.z * v.z);
	c = pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2) - pow(obj.r, 2);
	if ((det = pow(b, 2) - 4 * a * c) < 0)
		return (-1);
	tmp = (-b - pow(det, 0.5)) / 2 / a;
	if (tmp > 0)
		return (tmp);
	tmp = (-b + pow(det, 0.5)) / 2 / a;
	if (tmp > 0)
		return (tmp);
	return (-1);
}

float			intersect_plane(t_obj obj, t_pt p, t_pt v)
{
	float tmp;
	float a;
	float b;

	p = translate(p, obj.c);
	a = obj.normal.x * v.x + obj.normal.y * v.y + obj.normal.z * v.z;
	b = obj.normal.x * p.x + obj.normal.y * p.y + obj.normal.z * p.z;
	if (a == 0)
		return (-1);
	tmp = -b / a;
	if (tmp > 0)
		return (tmp);
	return (-1);
}

float			intersect_cylinder(t_obj obj, t_pt p, t_pt v)
{
	float a;
	float b;
	float c;
	float det;
	float tmp;

	p = cy_rot(obj, translate(p, obj.c));
	v = cy_rot(obj, v);
	a = pow(v.x, 2) + pow(v.z, 2);
	b = 2 * (p.x * v.x + p.z * v.z);
	c = pow(p.x, 2) + pow(p.z, 2) - pow(obj.r, 2);
	if ((det = pow(b, 2) - 4 * a * c) < 0)
		return (-1);
	tmp = (-b - pow(det, 0.5)) / 2 / a;
	if (tmp > 0)
		return (tmp);
	tmp = (-b + pow(det, 0.5)) / 2 / a;
	if (tmp > 0)
		return (tmp);
	return (-1);
}

float			intersect_cone(t_obj obj, t_pt p, t_pt v)
{
	float a;
	float b;
	float c;
	float det;
	float tmp;

	p = cy_rot(obj, translate(p, obj.c));
	v = cy_rot(obj, v);
	a = pow(v.x, 2) + pow(v.z, 2) - pow(v.y * obj.r / 100, 2);
	b = 2 * (p.x * v.x + p.z * v.z - p.y * v.y * pow(obj.r / 100, 2));
	c = pow(p.x, 2) + pow(p.z, 2) - pow(p.y * obj.r / 100, 2);
	if ((det = pow(b, 2) - 4 * a * c) < 0)
		return (-1);
	tmp = (-b - pow(det, 0.5)) / 2 / a;
	if (tmp > 0)
		return (tmp);
	tmp = (-b + pow(det, 0.5)) / 2 / a;
	if (tmp > 0)
		return (tmp);
	return (-1);
}
