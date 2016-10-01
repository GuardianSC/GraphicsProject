#version 430

// UV from vert
in vec2 vUV;

layout(location = 0) uniform mat4 view; // Camera view

// Geometry pass data
layout(location = 1) uniform sampler2D albedoMap;
layout(location = 2) uniform sampler2D normalMap;
layout(location = 3) uniform sampler2D specularMap;
layout(location = 4) uniform sampler2D positionMap;

// Shadow pass data
layout(location = 5) uniform sampler2D shadowMap;
uniform float shadowBias = 0.1f;

// Light data
layout(location = 6) uniform vec4 lColor; // light color
layout(location = 7) uniform mat4 lightView; // the light direction = light forward
layout(location = 8) uniform mat4 lightProjection; // light projection

// FrameBuffer outputs
layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outAlbedo;
layout(location = 2) out vec4 outSpecular;

// Matrix that converts from clip space (-1, 1) to UV space(0, 1)
uniform mat4 clipToUV = 
mat4(0.5f, 0.0f, 0.0f, 0.0f,
	 0.0f, 0.5f, 0.0f, 0.0f,
	 0.0f, 0.0f, 0.5f, 0.0f,
	 0.5f, 0.5f, 0.5f, 1.0f);

void main()
{
	vec3 L = normalize((view * lightView[2]).xyz);   // Light direction
	vec3 N = normalize(texture(normalMap, vUV).xyz); // Surface normal
	vec4 P = texture(positionMap, vUV); // Surface position

	////////// Shadow map calculations //////////
	// Space transformation
	// View -> World -> Light -> Clip -> UV
	vec4 sUV = clipToUV * lightProjection * lightView * inverse(view) * vec4(P.xyz, 1);

	// Compare sampled Z value against projected Z position. If sample is closer, don't draw it in the shadow
	if (texture(shadowMap, sUV.xy).r < sUV.z - shadowBias)   discard;

	////////// Phong calculations //////////
	vec3 R = reflect(L, N); // Reflected ray from light
	vec3 E = normalize(view[3].xyz + L.xyz); // Vector of the light's reflected ray () and the viewer (usually a camera)
	float sP = 2f; //  Specular power

	float lamb = max(0, -dot(L, N)); // Lambertian (diffuse) term = dot product of light direction (L) and surface normal (N)
	float spec = max(0, -dot(E, R)); // Specular = dot product of a ;ight's reflected ray (R) and vector of sufrace to viewer (E)
	if (spec > 0)   spec = pow(spec, sP);

	outAlbedo = texture(albedoMap,	   vUV) * lamb * lColor;
	outSpecular = texture(specularMap, vUV) * spec * lColor;
	//outColor = vec4(N,1.0f) * outAlbedo + outSpecular;
	outColor = outAlbedo + outSpecular;
}