#include "scop.h"

void       m_cp(t_m *a, t_m b)
{
	register size_t			i;
	register size_t			size;

	i = 0;
	size = MATRIX_FULL_SIZE;
	while (i < size)
	{
		a->data[i] = b.data[i];
		i++;
	}
}

t_m        m_iden()
{
	register size_t		i;
	t_m					temp;

	i = 0;
	while (i < MATRIX_FULL_SIZE) {
		temp.data[i] = (i % 5 == 0 ? 1 : 0);
		i++;
	}
	return (temp);
}

t_m         m_zero()
{
	register size_t		i;
	t_m					temp;

	i = 0;
	while (i < MATRIX_FULL_SIZE) {
		temp.data[i] = 0;
		i++;
	}
	return (temp);
}
