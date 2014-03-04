#version 130

uniform vec3 uColor;

out vec4 fragColor;

void main() {
  // TODO: Make back-facing fragments a different color
  if (gl_FrontFacing) {
    fragColor = vec4(uColor, 1.0);
  }
  else {
    fragColor = vec4(vec3(1.0, 0, 1.0), 1.0);
  }
}
