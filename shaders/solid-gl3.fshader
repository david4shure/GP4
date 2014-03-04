#version 130

uniform vec3 uColor;

out vec4 fragColor;

void main() {
// TODO: Make back-facing fragments a different color
  fragColor = vec4(uColor, 1.0);
}
