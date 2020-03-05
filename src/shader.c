/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:53:46 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/12 11:40:02 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			update_shader_uniforms(t_world *world)
{
	glUniformMatrix4fv(world->shader.mvploc, 1, GL_FALSE, world->mvp.data);
	glUniform1i(world->shader.smdloc, world->mode == BASIC);
	glUniform1i(world->shader.cmdloc, 0);
	glUniform1i(world->shader.gmdloc, world->mode == GREYSCALE);
	glUniform1i(world->shader.mmdloc, 0);
	glUniform1i(world->shader.tmdloc, world->mode == TEXTURED);
}

const GLchar	*get_shader_source(char *filename)
{
	int		fd;
	int		ret;
	char	buffer[BUFFER_SIZE];
	char	*source;
	char	*del;

	source = ft_strnew(BUFFER_SIZE);
	if ((fd = open(filename, O_RDONLY)) == -1)
		print_err("shader source file opening failed.");
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		del = source;
		source = ft_strjoin(source, buffer);
		free(del);
	}
	close(fd);
	return (source);
}

GLuint			create_shader(char *filename, int shader_type)
{
	GLint			success;
	GLuint			shader;
	const GLchar	*shader_source;

	shader_source = get_shader_source(filename);
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	free((void*)shader_source);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
		print_err("shader compilation failed.");
	return (shader);
}

GLuint			create_shader_program(GLuint shader_vert, GLuint shader_frag)
{
	GLint	success;
	GLuint	shader_program;

	shader_program = glCreateProgram();
	glAttachShader(shader_program, shader_vert);
	glAttachShader(shader_program, shader_frag);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
		print_err("shader program compilation failed.");
	glDeleteShader(shader_vert);
	glDeleteShader(shader_frag);
	return (shader_program);
}

void			build_shader_program(t_world *world)
{
	GLuint	shader_vert;
	GLuint	shader_frag;
	// GLfloat timeValue = glfwGetTime();
	// GLfloat greenValue = (sin(timeValue) / 2) + 0.5;

	shader_vert = create_shader("./shader/vertex.glsl", GL_VERTEX_SHADER);
	shader_frag = create_shader("./shader/fragment.glsl", GL_FRAGMENT_SHADER);
	world->shader.program = create_shader_program(shader_vert, shader_frag);
	world->shader.mvploc = glGetUniformLocation(world->shader.program, "mvp");
	world->shader.smdloc = glGetUniformLocation(world->shader.program, "smod");
	world->shader.cmdloc = glGetUniformLocation(world->shader.program, "cmod");
	world->shader.tmdloc = glGetUniformLocation(world->shader.program, "tmod");
	world->shader.gmdloc = glGetUniformLocation(world->shader.program, "gmod");
	world->shader.mmdloc = glGetUniformLocation(world->shader.program, "mmod");
	world->shader.texloc = glGetUniformLocation(world->shader.program, "ltexture");
}
