t_v2f	v2_scale(t_v2f a, double n)
{
	t_v2f c;

	c.x = a.x * n;
	c.y = a.y * n;
	return (c);
}

t_v2f	v2_min(t_v2f a, t_v2f b)
{
	t_v2f c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

t_v2f	v2_plus(t_v2f a, t_v2f b)
{
	t_v2f c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_v3f	v2_to_v3(t_v2f a)
{
	t_v3f c;

	c.x = a.x;
	c.y = 0;
	c.z = a.y;
	return (c);
}

float	v2_dot(t_v2f v)
{
	return (v.x * v.x + v.y * v.y);
}

double	v2_len(t_v2f v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double	v2_atan(t_v2f v1, t_v2f v2)
{
	return (atan2(v1.x * v2.y - v1.y * v2.x, v1.x * v2.x + v1.y * v2.y));
}

