#pragma once
#define GLEW_STATIC
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"

#ifdef _DEBUG
#include <cstdio>
#include <iostream>
#define glog(detail, extra) \
do{\
	std::cout << "In " << __FILE__ << " at "   \
			  << __FUNCTION__ << " on line "   \
			  << __LINE__<< ": " << detail     \
			  << ", " << extra << std::endl;   \
}while(0)
#else
#define glog(detail, extra)
#endif

#define glog_glCompileShader(shader)\
do{\
glCompileShader(shader);\
GLint success = GL_FALSE;\
glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &success);\
if (success == gL_FALSE)\
{\
	char *log = (char*)malloc(length);\
	glGetShaderInfoLog(shader, length, 0, log);\
	glog("Shader failed to compile!\n", log);\
	free(log);\
}\
}while(0)

#define glog_glLinkProgram(shader) \
do{\
glLinkProgram(shader);\
GLint success = GL_FALSE;\
glGetProgramiv(shader, GL_LINK_STATUS, &success);\
if(success == GL_FALSE)\
{\
	int length = 0;\
	glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);\
	char *log = (char*)malloc(length);\
	glGetProgramInfoLog(shader, length, 0, log);\
	std::cout << log << std::endl;\
	free(log);\
}\
}while(0)