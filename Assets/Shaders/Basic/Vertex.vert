#version 450

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TextureCoordinates;

layout (location = 0) out vec2 OutTextureCoordinates;

layout (binding = 0, set = 0) uniform set0 {
	mat4 Projection;
	mat4 View;
} SceneInfo;

void main()
{
	OutTextureCoordinates = TextureCoordinates;

	vec4 FinalPos = SceneInfo.Projection * SceneInfo.View * vec4(Position, 1.0);
	gl_Position = vec4(FinalPos.xyz, 1.0);
}