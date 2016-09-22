#pragma once
#include "glObjects.h"
#include "GLM\fwd.hpp"
#include <cstring>

void clearFramebuffer(const frameBuffer &Framebuffer);

namespace tdraw_internal
{
	void tdraw_begin(const Shader &shader, const Geometry &g, const frameBuffer &Framebuffer);
	void tdraw_close(const Shader &shader, const Geometry &g, const frameBuffer &Framebuffer);

	size_t tdraw_format(size_t idx, size_t tex, const glm::mat4 &val);
	size_t tdraw_format(size_t idx, size_t tex, const glm::vec3 &val);
	size_t tdraw_format(size_t idx, size_t tex, const glm::vec4 &val);
	size_t tdraw_format(size_t idx, size_t tex, int   val);
	size_t tdraw_format(size_t idx, size_t tex, float val);
	size_t tdraw_format(size_t idx, size_t tex, const Texture &val);


	template<typename T, typename ...U>
	void tdraw_unpack(size_t idx, size_t tex, T val, U &&...uniforms)
	{
		tex += tdraw_format(idx, tex, val);
		tdraw_unpack(idx + 1, tex, uniforms...);
	}

	template<typename T>
	void tdraw_unpack(size_t idx, size_t tex, T val)
	{
		tdraw_format(idx, tex, val);
	}
}

template<typename ...U>
void tdraw(const Shader &s, const Geometry &g, const frameBuffer &Framebuffer, U ... uniforms)
{
	tdraw_internal::tdraw_begin(s, g, Framebuffer);

	// uniform location, texture slot location
	tdraw_internal::tdraw_unpack(0, 0, uniforms...);

	tdraw_internal::tdraw_close(s, g, Framebuffer);
}



inline void tdraw(const Shader &s, const Geometry &g, const frameBuffer &Framebuffer)
{
	tdraw_internal::tdraw_begin(s, g, Framebuffer);
	tdraw_internal::tdraw_close(s, g, Framebuffer);
}