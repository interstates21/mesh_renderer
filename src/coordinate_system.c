#include "scop.h"

void	set_projection_matrix(t_env *env, float fov)
{
	float	s;
	float	far;
	float	near;

	far = CAMERA_FAR;
	near = CAMERA_NEAR;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	env->sim.projection = m_zero();
	env->sim.projection.m[0] = s / ASPECT_RATIO;
	env->sim.projection.m[5] = s;
	env->sim.projection.m[10] = -(far + near) / (far - near);
	env->sim.projection.m[11] = -1;
	env->sim.projection.m[14] = -2 * far * near / (far - near);
}

void	compute_mvp_matrix(t_env *env)
{
	env->sim.mvp = mat4_mul(mat4_transpose(env->sim.model),
		mat4_mul(env->sim.view, env->sim.projection));
}
