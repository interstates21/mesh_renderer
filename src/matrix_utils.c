#include "scop.h"

void	m_rotate_x(t_m *m, float angle)
{
	t_m		r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.data[5] = cos(theta);
	r.data[6] = sin(theta);
	r.data[9] = -sin(theta);
	r.data[10] = cos(theta);
	m_fast_mult(m, r);
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
	m_fast_mult(m, r);
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
	m_fast_mult(m, r);
}


t_m	m4_trans(t_m m)
{
	register size_t	y;
	register size_t	x;
	t_m	t;

	y = 0;
	x = 0;
	while (y < MATRIX_SIZE)
	{
		x = 0;
		while (x < MATRIX_SIZE) {
			t.data[x * MATRIX_SIZE + y] = m.data[y * MATRIX_SIZE + x];
			x++;
		}
		y++;
	}
	m_cp(&m, t);
	return (m);
}
