#include "scop.h"

t_v3f	v(double x, double y, double z) {
	t_v3f c;

	c.x = x;
	c.y = y;
	c.z = z;
	return (c);
}

double	v3_dot(t_v3f a, t_v3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_v3f	v3_cross(t_v3f a, t_v3f b)
{
	t_v3f c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_v3f	v3_min(t_v3f a, t_v3f b)
{
	t_v3f c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_v3f	v3_plus(t_v3f a, t_v3f b)
{
	t_v3f c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_v3f	v3_scale(t_v3f a, double n)
{
	t_v3f c;

	c.x = a.x * n;
	c.y = a.y * n;
	c.z = a.z * n;
	return (c);
}

void	v3_dir(double diff, t_v2f *dir)
{
	double	x;
	double	y;

	x = dir->x;
	y = dir->y;
	dir->x = x * cos(diff) - y * sin(diff);
	dir->y = x * sin(diff) + y * cos(diff);
}

double	v3_magnitude(t_v3f a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_v3f	v3_norm(t_v3f a)
{
	t_v3f	c;
	double	l;

	l = v3_magnitude(a);
	c.x = a.x / l;
	c.y = a.y / l;
	c.z = a.z / l;
	return (c);
}


t_v2f	v3_to_v2(t_v3f a)
{
	t_v2f c;

	c.x = a.x;
	c.y = a.z;
	return (c);
}

