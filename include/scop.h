#ifndef SCOP_H
# define SCOP_H

/*
** User librairies
*/
# include "libft.h"
 #include <fcntl.h>

/*
** External librairies
*/
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <GLFW/glfw3.h>

# define WINDOW_NAME "Eternal beauty of graphics shit"
# define OPENGL_VERSION "4.0"
# define BUFFER_SIZE 128
# define COOLDOWN 20
# define WIDTH 1600
# define HEIGHT 800
# define FOV 90
# define MATRIX_SIZE 4
# define MATRIX_FULL_SIZE 16
# define CAMERA_NEAR 0.001
# define CAMERA_FAR 100.0
# define ASPECT_RATIO (WIDTH / (float)HEIGHT)
/*
** Camera zoom
*/
# define ZP GLFW_KEY_KP_ADD
# define ZM GLFW_KEY_KP_SUBTRACT

/*
** Camera movement
*/
# define CF GLFW_KEY_W
# define CB GLFW_KEY_S
# define CL GLFW_KEY_A
# define CR GLFW_KEY_D
# define CU GLFW_KEY_LEFT_SHIFT
# define CD GLFW_KEY_LEFT_CONTROL

/*
** Model movement
*/
# define TF GLFW_KEY_I
# define TB GLFW_KEY_K
# define TL GLFW_KEY_J
# define TR GLFW_KEY_L
# define TU GLFW_KEY_PAGE_UP
# define TD GLFW_KEY_PAGE_DOWN
# define RM GLFW_KEY_MINUS
# define RP GLFW_KEY_EQUAL

/*
** Modifiers
*/
# define MW GLFW_KEY_1
# define MS GLFW_KEY_2
# define MG GLFW_KEY_3
# define MM GLFW_KEY_4
# define MC GLFW_KEY_C
# define MF GLFW_KEY_R
# define MT GLFW_KEY_T

# define MAX_KEYS 348

# define FREE 0
# define LOCKED 1

typedef struct	s_v3f
{
	double	x;
	double	y;
	double	z;
	double	option;
}				t_v3f;

typedef struct	s_m
{
	float	data[16];
}				t_m;

typedef struct	s_texture
{
	unsigned char	*img;
	int				size;
	int				w;
	int				h;
	int				resolution;
}				t_texture;

typedef struct	s_cam
{
	t_v3f	pos;
	t_v3f	dir;
	t_v3f	target;
	t_v3f	up;
	t_v3f	right;
	t_v3f	front;
	t_v3f	inertia;
	float	velocity;
}				t_cam;

typedef struct	s_key
{
	short	code;
	short	cooldown;
}				t_key;

typedef struct	s_model
{
	t_m			translation;
	t_m			rotation;
	GLfloat			*vertices;
	GLuint			*indices;
	unsigned int	size_indices;
	unsigned int	size_vertices;
	unsigned int	num_indices;
	t_v3f			center_axis;
	t_v3f			inertia;
	t_texture		texture;
	float			velocity;
	char			*filename;
}				t_model;

typedef struct	s_sim
{
	t_m	model;
	t_m	view;
	t_m	projection;
	t_m	mvp;
}				t_sim;

typedef struct	s_buffer
{
	GLuint	vao;
	GLuint	vbo;
	GLuint	ebo;
	GLuint	texture;
}				t_buffer;

typedef struct	s_shader
{
	GLuint	program;
	GLint	mvploc;
	GLint	cmdloc;
	GLint	smdloc;
	GLint	tmdloc;
	GLint	gmdloc;
	GLint	mmdloc;
	GLint	texloc;
}				t_shader;


typedef struct	s_mod
{
	short	wireframe;
	short	focus;
	short	shading;
	short	color;
	short	greyscale;
	short	mapping;
	short	texture;
}				t_mod;

typedef struct	s_env
{
	GLFWwindow	*window;
	t_sim		sim;
	t_cam		cam;
	t_key		key[MAX_KEYS];
	t_mod		mod;
	t_buffer	buffer;
	t_shader	shader;
	t_model		model;
}				t_env;


typedef struct	s_v2f
{
	double	x;
	double	y;
}				t_v2f;

typedef struct	s_v4f
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_v4f;



void			mat4_set(t_m *m, float f);
void			m_cp(t_m *a, t_m b);
t_m			mat4_add(t_m a, t_m b);
t_m			mat4_sub(t_m a, t_m b);
t_m			m_mult(t_m a, t_m b);
void	m_fast_mult(t_m *a, t_m b);
t_m			mat4_scale(t_m m, float f);
t_m			m4_trans(t_m m);
void			m_rotate_x(t_m *m, float angle);
void			m_rotate_y(t_m *m, float angle);
void			m_rotate_z(t_m *m, float angle);


/*
** init.c
*/
void			init_glfw_env(void);
void			init_glfw_win(t_env *env);
void			init_matrices(t_env *env);
void			init_cam(t_env *env);
void			init(t_env *env);

/*
** callback.c
*/
void			key_handle(t_env *env);
void			key_action(t_env *env);
void			key_toggle(t_key *key, short *var, int v0, int v1);

/*
** shader.c
*/
void			update_shader_uniforms(t_env *env);
const GLchar	*get_shader_source(char *filename);
GLuint			create_shader(char *filename, int shader_type);
GLuint			create_shader_program(GLuint shader_vert, GLuint shader_frag);
void			build_shader_program(t_env *env);

/*
** buffer.c
*/
void			create_texture(t_env *env);
void			create_buffers(t_env *env, int mode);

/*
** parsing.c
*/
void			load_obj(t_env *env, char *filename);
GLfloat			*append_vertices(GLfloat *array, char *line, int *length);
GLuint			*append_indices(GLuint *array, char *line, int *length);
t_v3f			compute_center_axis(GLfloat	*vertices, int num_vertices);
void			center_vertices(t_env *env, int length);

/*
** texture.c
*/
void			load_bmp(t_env *env, char *filename);
void			get_image(t_texture *texture, char *buffer, int i);

/*
** utils.c
*/
void			clean_glfw(t_env *env);
// int				array_len(void **tab);
GLuint			*gluint_array_copy(GLuint *array, int length, int m);
/*
** coordinate_system.c
*/
void			set_projection_matrix(t_env *env, float fov);
void			compute_mvp_matrix(t_env *env);

/*
** movement.c
*/
void			translate(t_m *m, t_v3f v);
void			rotate(t_m *m, t_v3f v);
void			model_move_inertia(t_env *env, float inertia);
void			model_move_demo(t_env *env);

/*
** camera.c
*/
void			camera_zoom(t_env *env);
void			camera_move_inertia(t_env *env, float inertia, int mode);
void			camera_center(t_env *env);
void			camera_look_at_target(t_env *env);

void    		print_err(char *str);
void			init_gl(t_env *env);

t_v3f	v(double x, double y, double z);
double	v3_dot(t_v3f a, t_v3f b);
t_v3f	v3_min(t_v3f a, t_v3f b);
t_v3f	v3_plus(t_v3f a, t_v3f b);
t_v3f	v3_scale(t_v3f a, double n);
void	v3_dir(double diff, t_v2f *dir);
double	v3_magnitude(t_v3f a);
t_v3f	v3_norm(t_v3f a);
t_v3f	v3_cross(t_v3f a, t_v3f b);
t_v2f	v3_to_v2(t_v3f a);
t_m	m_zero();
t_m	m_iden();
#endif
