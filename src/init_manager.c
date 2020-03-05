#include "scop.h"

	// t_vec3	up;

	// up = vec3(0, 1, 0);
	// env->cam.pos = vec3(0, 0, 3);
	// env->cam.target = vec3(0, 0, 0);
	// env->cam.dir = vec3_normalize(vec3_sub(env->cam.pos, env->cam.target));
	// env->cam.right = vec3_normalize(vec3_cross(up, env->cam.dir));
	// env->cam.up = vec3_cross(env->cam.dir, env->cam.right);
	// env->cam.front = vec3_cross(env->cam.up, env->cam.right);
	// vec3_set(&env->cam.inertia, 0);
	// env->cam.velocity = 0.005;

static void	init_cam(t_env *env)
{
	t_v3f	up;

	up = v(0, 1, 0);
	env->cam.velocity = 0.005;
	env->cam.target = v(0, 0, 0);
	env->cam.pos = v(0, 0, 3);
	env->cam.dir = v3_norm(v3_min(env->cam.pos, env->cam.target));
	env->cam.right = v3_norm(v3_cross(up, env->cam.dir));
	env->cam.up = v3_cross(env->cam.dir, env->cam.right);
	env->cam.front = v3_cross(env->cam.up, env->cam.right);
	env->cam.inertia = v(0, 0, 0);
	env->sim.model = m_iden();
	env->sim.view = m_iden();
	set_projection_matrix(env, FOV);
	env->model.translation = m_iden();
	env->model.inertia = v(0, 0, 0);
	env->model.rotation = m_iden();
	env->model.center_axis = v(0, 0, 0);
}

static void	init_modes(t_env *env)
{
	env->mod.wireframe = GL_FILL;
	env->mod.shading = 0;
	env->mod.focus = 1;
	env->mod.greyscale = 0;
	env->mod.mapping = 0;
	env->mod.texture = 0;
	env->mod.color = 0;
	env->model.velocity = 0.33;
}

static void	init_keys(t_env *env)
{
	register size_t	i;

	i = 0;
	while (i < MAX_KEYS) {
		env->key[i].cooldown = 0;
		i++;
	}
}


t_env	init_manager(char *filename)
{
	t_env			env;

	env.model.filename = filename;
	init_keys(&env);
	init_gl(&env);
	init_cam(&env);
	init_modes(&env);

	return (env);
}

