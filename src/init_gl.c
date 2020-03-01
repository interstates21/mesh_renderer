#include "scop.h"

static void	init_gl_version(void) {
	const int	maj = 4;
	const int	min = 0;
	
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


static void calc_monitor_viewport(t_env *env) {
    int w;
    int h;

    w = WIDTH;
    h = HEIGHT;
    glfwGetFramebufferSize(env->window, &w, &h);
    ft_putstr("Viewport: ");
    ft_putnbr(w);
    ft_putstr(", ");
    ft_putnbr(h);
    ft_putchar('\n');
    glViewport(0, 0, w, h);
}

void	init_gl(t_env *env)
{
    if (!glfwInit())
		ft_putendl("Failed to init GLFW");
	init_gl_version();
	env->window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);
	if (env->window == NULL)
	{
    	glfwTerminate();
    	print_err("Failed to init Window");
	}
    ft_putstr("Window: ");
    ft_putnbr(WIDTH);
    ft_putstr(", ");
    ft_putnbr(HEIGHT);
    ft_putchar('\n');
	glfwMakeContextCurrent(env->window);
    calc_monitor_viewport(env);
}
