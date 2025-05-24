#version 410 core
in vec2 vUV;
out vec4 FragColor;

uniform float uTime;

void main() {
    vec2 uv = vUV;
    float angle = atan(uv.y, uv.x);
    float radius = length(uv);
    float swirl = sin(10.0 * radius - uTime * 2.0 + angle * 5.0);
    vec3 color = vec3(0.5 + 0.5 * sin(swirl + uTime), 0.1 + 0.8 * sin(swirl + uTime), 0.5 + 0.2 * sin(swirl + uTime));
    FragColor = vec4(color, 1.0);
}
