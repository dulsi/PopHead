R"(

#version 330 core

layout (location = 0) in vec2 aPos;

uniform vec2 lightPos;

out DATA
{
	vec2 fragPos;
	flat vec2 lightPos;
} vs_out;

layout (std140) uniform SharedData
{
	mat4 gameWorldVPM;
	mat4 guiVPM;
};

void main()
{
	vec4 vertexPos = gameWorldVPM * vec4(aPos, 0, 1);
	vs_out.fragPos = vertexPos.xy;
	vs_out.lightPos = vec2(gameWorldVPM * vec4(lightPos, 0, 1));
	gl_Position = vertexPos;
}

)"

