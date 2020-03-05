#include "scop.h"

void	m_cp(t_m *a, t_m b)
{
	int			i;
	int			size;

	i = 0;
	size = 16;
	while (i < size)
	{
		a->data[i] = b.data[i];
		i++;
	}
}

t_m	m_iden()
{
	int		i;
	t_m	temp;

	i = 0;
	while (i < 16) {
		temp.data[i] = (i % 5 == 0 ? 1 : 0);
		i++;
	}
	return (temp);
}

t_m	m_zero()
{
	int		i;
	t_m	temp;

	i = 0;
	while (i < 16) {
		temp.data[i] = 0;
		i++;
	}
	return (temp);
}



t_m	mat4_mul(t_m a, t_m b)
{
	int		h;
	int		w;
	int		z;
	t_m	m;

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
		{
			z = -1;
			m.data[h * 4 + w] = 0;
			while (++z < 4)
				m.data[h * 4 + w] += a.data[h * 4 + z] * b.data[z * 4 + w];
		}
	}
	return (m);
}

void	m_rotate_x(t_m *m, float angle)
{
	t_m	r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.data[5] = cos(theta);
	r.data[6] = sin(theta);
	r.data[9] = -sin(theta);
	r.data[10] = cos(theta);
	*m = mat4_mul(*m, r);
}

void	m_rotate_y(t_m *m, float angle)
{
	t_m	r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.data[0] = cos(theta);
	r.data[2] = -sin(theta);
	r.data[8] = sin(theta);
	r.data[10] = cos(theta);
	*m = mat4_mul(*m, r);
}

void	m_rotate_z(t_m *m, float angle)
{
	t_m	r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.data[0] = cos(theta);
	r.data[1] = sin(theta);
	r.data[4] = -sin(theta);
	r.data[5] = cos(theta);
	*m = mat4_mul(*m, r);
}


t_m	mat4_transpose(t_m m)
{
	register size_t	y;
	register size_t	x;
	t_m	t;

	y = 0;
	x = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4) {
			t.data[x * 4 + y] = m.data[y * 4 + x];
			x++;
		}
		y++;
	}
	m_cp(&m, t);
	return (m);
}
