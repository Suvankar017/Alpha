#version 460 core

// Scalers
uniform bool _Bool;
uniform int _Int;
uniform uint _UInt;
uniform float _Float;
uniform double _Double;

// Vectors
uniform bvec2 _BVec2;
uniform bvec3 _BVec3;
uniform bvec4 _BVec4;

uniform ivec2 _IVec2;
uniform ivec3 _IVec3;
uniform ivec4 _IVec4;

uniform uvec2 _UVec2;
uniform uvec3 _UVec3;
uniform uvec4 _UVec4;

uniform vec2 _Vec2;
uniform vec3 _Vec3;
uniform vec4 _Vec4;

uniform dvec2 _DVec2;
uniform dvec3 _DVec3;
uniform dvec4 _DVec4;

// Matrices
uniform mat2 _Mat2;
uniform mat2x3 _Mat2x2;
uniform mat2x4 _Mat2x4;

uniform mat3x2 _Mat3x2;
uniform mat3 _Mat3;
uniform mat3x4 _Mat3x4;

uniform mat4x2 _Mat4x2;
uniform mat4x3 _Mat4x3;
uniform mat4 _Mat4;



layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_UV;

void main()
{
	
}