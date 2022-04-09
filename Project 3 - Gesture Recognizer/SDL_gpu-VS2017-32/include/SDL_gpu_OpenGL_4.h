#ifndef _SDL_GPU_OPENGL_4_H__
#define _SDL_GPU_OPENGL_4_H__

#include "SDL_gpu.h"

#if !defined(SDL_GPU_DISABLE_OPENGL) && !defined(SDL_GPU_DISABLE_OPENGL_4)

    // Hacks to fix compile errors due to polluted namespace
    #ifdef _WIN32
    #define _WINUSER_H
    #define _WINGDI_H
    #endif
    
    #include "glew.h"
	
	#if defined(GL_EXT_bgr) && !defined(GL_BGR)
		#define GL_BGR GL_BGR_EXT
	#endif
	#if defined(GL_EXT_bgra) && !defined(GL_BGRA)
		#define GL_BGRA GL_BGRA_EXT
	#endif
	#if defined(GL_EXT_abgr) && !defined(GL_ABGR)
		#define GL_ABGR GL_ABGR_EXT
	#endif
#endif


#define GPU_CONTEXT_DATA ContextData_OpenGL_4
#define GPU_IMAGE_DATA ImageData_OpenGL_4
#define GPU_TARGET_DATA TargetData_OpenGL_4



#define GPU_DEFAULT_TEXTURED_VERTEX_SHADER_SOURCE \
"#version 400\n\
\
in vec2 gpu_Vertex;\n\
in vec2 gpu_TexCoord;\n\
in vec4 gpu_Color;\n\
uniform mat4 gpu_ModelViewProjectionMatrix;\n\
\
out vec4 color;\n\
out vec2 texCoord;\n\
\
void main(void)\n\
{\n\
	color = gpu_Color;\n\
	texCoord = vec2(gpu_TexCoord);\n\
	gl_Position = gpu_ModelViewProjectionMatrix * vec4(gpu_Vertex, 0.0, 1.0);\n\
}"

#define GPU_DEFAULT_UNTEXTURED_VERTEX_SHADER_SOURCE \
"#version 400\n\
\
in vec2 gpu_Vertex;\n\
in vec4 gpu_Color;\n\
uniform mat4 gpu_ModelViewProjectionMatrix;\n\
\
out vec4 color;\n\
\
void main(void)\n\
{\n\
	color = gpu_Color;\n\
	gl_Position = gpu_ModelViewProjectionMatrix * vec4(gpu_Vertex, 0.0, 1.0);\n\
}"


#define GPU_DEFAULT_TEXTURED_FRAGMENT_SHADER_SOURCE \
"#version 400\n\
\
in vec4 color;\n\
in vec2 texCoord;\n\
\
uniform sampler2D tex;\n\
\
out vec4 fragColor;\n\
\
void main(void)\n\
{\n\
    fragColor = texture(tex, texCoord) * color;\n\
}"

#define GPU_DEFAULT_UNTEXTURED_FRAGMENT_SHADER_SOURCE \
"#version 400\n\
\
in vec4 color;\n\
\
out vec4 fragColor;\n\
\
void main(void)\n\
{\n\
    fragColor = color;\n\
}"


typedef struct ContextData_OpenGL_4
{
	SDL_Color last_color;
	GPU_bool last_use_texturing;
	unsigned int last_shape;
	GPU_bool last_use_blending;
	GPU_BlendMode last_blend_mode;
	GPU_Rect last_viewport;
	GPU_Camera last_camera;
	GPU_bool last_camera_inverted;
	
	GPU_bool last_depth_test;
	GPU_bool last_depth_write;
	
	GPU_Image* last_image;
	GPU_Target* last_target;
	float* blit_buffer;  // Holds sets of 4 vertices, each with interleaved position, tex coords, and colors (e.g. [x0, y0, z0, s0, t0, r0, g0, b0, a0, ...]).
	unsigned short blit_buffer_num_vertices;
	unsigned short blit_buffer_max_num_vertices;
	unsigned short* index_buffer;  // Indexes into the blit buffer so we can use 4 vertices for every 2 triangles (1 quad)
	unsigned int index_buffer_num_vertices;
	unsigned int index_buffer_max_num_vertices;
	
    // Tier 3 rendering
    unsigned int blit_VAO;
    unsigned int blit_VBO[2];  // For double-buffering
    unsigned int blit_IBO;
    GPU_bool blit_VBO_flop;
    
	GPU_AttributeSource shader_attributes[16];
	unsigned int attribute_VBO[16];
} ContextData_OpenGL_4;

typedef struct ImageData_OpenGL_4
{
    int refcount;
    GPU_bool owns_handle;
	Uint32 handle;
	Uint32 format;
} ImageData_OpenGL_4;

typedef struct TargetData_OpenGL_4
{
    int refcount;
	Uint32 handle;
	Uint32 format;
} TargetData_OpenGL_4;



#endif
