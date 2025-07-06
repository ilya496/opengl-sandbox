#version 410 core

out vec4 FragColor;

in float v_OnCurve;

void main()
{
    float dist = length(gl_PointCoord - vec2(0.5));
    float alpha = smoothstep(0.5, 0.45, dist);
    if (alpha < 0.01)
    {
        discard;
    }

    if (v_OnCurve > 0.5)
    {
        FragColor = vec4(1.0, 1.0, 1.0, alpha);
    }
    else
    {
        FragColor = vec4(1.0, 0.0, 0.0, alpha);
    }
}