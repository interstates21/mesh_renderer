#include "scop.h"

void	set_projection_matrix(t_env *env, float fov)
{
	float	s;
	float	far;
	float	near;

	far = CAMERA_FAR;
	near = CAMERA_NEAR;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	env->projection = m_zero();
	env->projection.data[0] = s / ASPECT_RATIO;
	env->projection.data[5] = s;
	env->projection.data[10] = -(far + near) / (far - near);
	env->projection.data[11] = -1;
	env->projection.data[14] = -2 * far * near / (far - near);
}

void	compute_mvp_matrix(t_env *env)
{
	env->mvp = m_mult(m4_trans(env->model),
		m_mult(env->view, env->projection));
}
