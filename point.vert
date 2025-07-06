#version 410 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in float a_OnCurve;

uniform float u_PointSize;

out float v_OnCurve;

void main()
{
    v_OnCurve = a_OnCurve;

    gl_Position = vec4(a_Position, 1.0, 1.0);
    gl_PointSize = u_PointSize;
}
