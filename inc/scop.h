/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 13:55:20 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/17 15:35:39 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOPE_H
# define SCOPE_H

# ifdef __APPLE__
#  define __gl_h_
#  define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
# endif

# include <OpenGl/OpenGl.h>
# include <OpenGl/gl3.h>
# include <OpenGL/gl.h>
# include <GLFW/glfw3.h>

# include <stdio.h>
# include <stdlib.h>

# include "/nfs/2013/g/gmevelec/perso/libs/libloadimage/inc/loadimage.h"

# define WIDTH 1024
# define HEIGHT 768
# define FOV 70
# define NEAR_PLANE 0.1
# define FAR_PLANE 1000

# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE		"\x1B[37m"
# define RESET		"\033[0m"


//////////////////////////////////////////////
/*
** t_vec3f
*/
typedef struct	s_vec3f
{
	GLfloat		x;
	GLfloat		y;
	GLfloat		z;
}				t_vec3f;

/*
** t_vec2f
*/
typedef struct	s_vec2f
{
	GLfloat		x;
	GLfloat		y;
}				t_vec2f;

/*
** t_elem_face
*/

typedef struct	s_elem
{
	int		v;
	int		t;
	int		n;
}				t_elem;

/*
** t_face
*/
typedef struct	s_face
{
	t_elem			*elem;
	int				num_elems;
	int				has_textures;
	int				has_normals;
}				t_face;

/*
** t_mesh
*/
typedef struct	s_mesh
{
	t_vec3f		*vertex;
	int			num_vertex;
	
	t_vec2f		*textures;
	int			num_textures;
	
	t_vec3f		*normals;
	int			num_normals;

	GLuint		*indices;
	int			num_indices;

	t_face		*faces;
	int			num_faces;
}				t_mesh;

//////////////////////////////////////////////
/*
** t_vertice
*/
typedef struct 		s_vertice
{
	GLfloat		*array;
	int 		count;
}					t_vertice;

/*
** t_indice
*/
typedef struct 		s_indice
{
	GLuint		*array;
	int 		count;
}					t_indice;

/*
** t_texture_coord
*/
typedef struct 		s_texture_coord
{
	GLfloat		*array;
	int 		count;
}					t_texture_coord;

/*
** t_normal
*/
typedef struct 		s_normal
{
	GLfloat		*array;
	int 		count;
}					t_normal;

/*
** t_vertex_shader
*/
typedef struct 		s_vertex_shader
{
	GLchar			**shader;
	unsigned int 	size;
}					t_vertex_shader;

/*
** t_fragment_shader
*/
typedef struct 		s_fragment_shader
{
	GLchar			**shader;
	unsigned int 	size;
}					t_fragment_shader;

/*
** t_shader
*/
typedef struct 		s_shader
{
	GLuint				vertex_shader_id;
	GLuint				fragment_shader_id;
	GLuint 				program_id;
	t_vertex_shader		vertex_shader;
	t_fragment_shader	fragment_shader;
}					t_shader;

/*
** t_raw_model
*/
typedef struct 		s_raw_model
{
	GLuint		vaoid;
	GLuint		vertex_count;
}					t_raw_model;

/*
** t_texture
*/
typedef struct		s_texture
{
	GLuint			texture_id;
	GLuint			vertex_count;
	t_raw_model		model;
}					t_texture;

/*
** t_entity
*/
typedef struct 		s_entity
{
	GLuint		entity_id;
	t_texture 	texture;
	t_vec3f		position;
	t_vec3f		rot;
	GLfloat		scale;
}					t_entity;

/*
** t_camera
*/
typedef struct 		s_camera
{
	t_vec3f			position;
	GLfloat			pitch;
	GLfloat			yaw;
	GLfloat			roll;
}					t_camera;

typedef GLfloat vec3_t[3];
typedef GLfloat vec4_t[4];

/////////////////////////////////////////////////////////////

// typedef struct	s_material
// {
// 	char		*name;
	
// 	float		ambient[3];
// 	float		diffuse[3];
// 	float		specular[3];
// 	float		transmittance[3];
// 	float		emission[3];
// 	float		shininess;
// 	float		ior;
// 	float		dissolve;
// 	int			illum;
// 	int			dummy;

// 	char		*ambient_texname;
// 	char		*diffuse_texname;
// 	char		*specular_texname;
// 	char		*specular__highlight_texname;
// 	char		*bump_texname;
// 	char		*displacement_texname;
// 	char		*alpha_texname;
// }				t_material;

// typedef struct	s_tag
// {
// 	char		*name;
// 	int			*int_values;
// 	float		*float_values;
// 	char		**string_values;
// }				t_tag;

// typedef struct	s_mesh
// {
// 	float			*positions;
// 	float			*normals;
// 	float			*tex_coords;
// 	unsigned int	*indices;
// 	unsigned char	*num_vertices;
// 	int				*material_ids;
// 	t_tag			*tags;
// }				t_mesh;

// typedef struct	s_shape
// {
// 	char		*name;
// 	t_mesh		mesh;
// }				t_shape;

/////////////////////////////////////////////////////////////

/*
** t_obj_vertex
*/
typedef struct 		s_obj_vertex
{
	vec4_t		xyzw;
}					t_obj_vertex;

/*
** t_obj_texture
*/
typedef struct 		s_obj_texture
{
	vec3_t		uvw;
}					t_obj_texture;

/*
** t_obj_normal
*/
typedef struct 		s_obj_normal
{
	vec3_t		ijk;
}					t_obj_normal;

/*
** t_obj_face
*/
typedef struct 		s_obj_face
{
	GLenum 		type;
	int 		num_elems;
	int 		*vertex_indices;
	int 		*uvw_indices;
	int 		*norm_indices;
}					t_obj_face;

/*
** t_obj_model
*/
typedef struct 		s_obj_model
{
	int 			num_vertex;
	int 			num_textures;
	int 			num_normals;
	int 			num_faces;
	int 			num_faces_tri;

	int 			has_textures;
	int 			has_normals;

	t_obj_vertex	*vertices;
	t_obj_texture	*textures;
	t_obj_normal	*normals;
	t_obj_face		*faces;
}					t_obj_model;

/*
** t_env
*/
typedef struct		s_env
{
	void 	*mlx;
	GLFWwindow* 	window;
	t_raw_model		raw_model;
	t_entity		entity;
	t_bmp			bmp;
	t_camera		camera;
	t_shader		shader;

	t_indice		indice;
	t_vertice		vertices;
	t_texture_coord	texture_coord;
	t_normal		normal;

	GLuint			transf_mat_id;
	GLfloat			transf_mat[16];
	GLuint			proj_mat_id;
	GLfloat			proj_mat[16];
	GLuint			view_mat_id;
	GLfloat			view_mat[16];

	int 			pause;
	int 			draw_type;

	t_texture_coord	texture_array;
	t_obj_model		*obj_model;

///////////////////////////////
	t_mesh			mesh;
///////////////////////////////

}					t_env;

/*
** get_next_line.c
*/
int					get_next_line(int fd, char **line);

/*
** init_env.c
*/
void				init_entity(t_env *env);
void				init_camera(t_env *env);
void				init_options(t_env *env);
void				init_env(t_env *env);

/*
** init_glfw.c
*/
void				init_glfw(t_env *env);

/*
** init_model.c
*/
void 				init_model(const char **argv, t_env *env);

/*
** loader.c
*/
t_raw_model			load_to_vao(t_env *env, t_indice indices);
int					create_vao();
void				store_data_in_attribute_list(int attribute_number, int coord_size, int n, t_env *env);
void				unbind_vao();
void 				bind_indices_buffer(GLuint *indices, int length);

/*
** renderer.c
*/
void				prepare();
void				render(t_env *env);
void 				renderer(t_env *env);
void				create_projection_matrix(t_env *env);

/*
** shader.c
*/
void				bind_attributes(GLuint program_id);
void				start(GLuint program_id);
void 				stop();
void				shader_program(t_env *env);
void				shader_error(GLuint shader_id);
GLuint				load_shader(GLuint type, t_env *env);

/*
** get_shaders.c
*/
int					get_length_file(char *file);
void				stock_shader(GLchar **shader, char *file);
void				get_shaders(t_env *env);

/*
** texture.c
*/
//GLuint				load_bmp(char *file, t_env *env);
//void				load_header(FILE *file, t_bmp *bmp, char *header);
//GLuint				load_texture(t_bmp *bmp);
//GLuint				load_image(t_env *env, char *filename);

/*
** maths.c
*/
float				convert_to_rad(float angle);
void				scale_mat(GLfloat mat[16], t_vec3f vect);
void				create_transformation_matrix(GLfloat mat[16], t_vec3f trans,
									t_vec3f rot, GLfloat scale);
void				create_view_matrix(GLfloat mat[16], t_camera camera);

/*
** matrix.c
*/
void				set_identity(GLfloat mat[16]);
void				translate_mat(GLfloat mat[16], t_vec3f vect);
void				init_tab_rot_mat(GLfloat tab[26], t_vec3f vect, float angle);
void				rotate_mat(GLfloat mat[16], t_vec3f vect, float angle);

/*
** load_matrix.c
*/
void				load_matrix(GLuint location, GLfloat mat[16]);
void				load_transformation_matrix(GLuint transf_matrix, GLfloat mat[16]);
void				load_projection_matrix(GLuint projection_matrix, GLfloat mat[16]);
void				load_view_matrix(GLuint view_matrix, GLfloat mat[16], t_camera camera);

/*
** entity.c
*/
void				increase_position(t_entity *entity, GLfloat x, GLfloat y, GLfloat z);
void				increase_rotation(t_entity *entity, GLfloat x, GLfloat y, GLfloat z);

/*
** camera.c
*/
void				increase_cam_position(t_camera *camera, GLfloat x, GLfloat y, GLfloat z);

/*
** parser.c
*/
t_raw_model			load_obj_model(const char *filename, t_env *env);
void				process_vertex(char **vertex_data, float *normalsArray, int i, t_env *env);

/*
** check_obj.c
*/
void				check_vertice(char *line, int nb_line);
void				check_texture(char *line, int nb_line, t_env *env);
void				check_normal(char *line, int nb_line, t_env *env);
void				check_face(char *line, int nb_line, t_env *env);

/*
** parser_obj.c
*/
int 				first_pass(FILE *fp, t_obj_model *mdl);
int					malloc_model(t_obj_model *mdl);
void				free_model(t_obj_model *mdl);
int 				second_pass(FILE *fp, t_obj_model *mdl);

#endif
