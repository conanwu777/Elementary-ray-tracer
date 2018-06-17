/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:18:30 by cwu               #+#    #+#             */
/*   Updated: 2018/06/06 17:18:33 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_pt			add_points(t_pt a, t_pt b)
{
	t_pt pt;

	pt.x = a.x + b.x;
	pt.y = a.y + b.y;
	pt.z = a.z + b.z;
	return (pt);
}

t_pt			neg_point(t_pt pt)
{
	pt.x = -pt.x;
	pt.y = -pt.y;
	pt.z = -pt.z;
	return (pt);
}

t_pt			vector(t_pt a, t_pt b)
{
	t_pt new;

	new.x = b.x - a.x;
	new.y = b.y - a.y;
	new.z = b.z - a.z;
	return (new);
}

t_pt			v_scale(t_pt p, float l)
{
	p.x *= l;
	p.y *= l;
	p.z *= l;
	return (p);
}

t_pt			translate(t_pt p, t_pt m)
{
	p.x -= m.x;
	p.y -= m.y;
	p.z -= m.z;
	return (p);
}
