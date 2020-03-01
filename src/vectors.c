#include "../includes/common.h"

t_vec2f	v2_min(t_vec2f a, t_vec2f b)
{
	t_vec2f c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

t_vec2f	v2_plus(t_vec2f a, t_vec2f b)
{
	t_vec2f c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_vec3f	v3_min(t_vec3f a, t_vec3f b)
{
	t_vec3f c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vec3f	v3_plus(t_vec3f a, t_vec3f b)
{
	t_vec3f c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vec3f	v3_scale(t_vec3f a, double n)
{
	t_vec3f c;

	c.x = a.x * n;
	c.y = a.y * n;
	c.z = a.z * n;
	return (c);
}

t_vec2f	v2_scale(t_vec2f a, double n)
{
	t_vec2f c;

	c.x = a.x * n;
	c.y = a.y * n;
	return (c);
}

void	actualize_dir(double diff, t_vec2f *dir)
{
	double	x;
	double	y;

	x = dir->x;
	y = dir->y;
	dir->x = x * cos(diff) - y * sin(diff);
	dir->y = x * sin(diff) + y * cos(diff);
}

double	vec3f_length(t_vec3f v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3f	v2_to_v3(t_vec2f a)
{
	t_vec3f c;

	c.x = a.x;
	c.y = 0;
	c.z = a.y;
	return (c);
}

t_vec2f	v3_to_v2(t_vec3f a)
{
	t_vec2f c;

	c.x = a.x;
	c.y = a.z;
	return (c);
}

bool	is_inside_vec2f(t_vec2f p1, t_vec2f p2, t_vec2f point)
{
	if ((point.x < p1.x && point.x < p2.x) ||
			(point.x > p1.x && point.x > p2.x))
		return (false);
	if ((point.y < p1.y && point.y < p2.y) ||
			(point.y > p1.y && point.y > p2.y))
		return (false);
	return (true);
}

float	v2_dot(t_vec2f v)
{
	return (v.x * v.x + v.y * v.y);
}

double	v2_len(t_vec2f v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double	v2_atan(t_vec2f v1, t_vec2f v2)
{
	return (atan2(v1.x * v2.y - v1.y * v2.x, v1.x * v2.x + v1.y * v2.y));
}

void	v2_rot(t_vec2f *p, double angle)
{
	t_vec2f temp;

	temp = *p;
	p->x = temp.x * cos(angle) - temp.y * sin(angle);
	p->y = temp.x * sin(angle) + temp.y * cos(angle);
}