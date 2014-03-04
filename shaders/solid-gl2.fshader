uniform vec3 uColor;

void main() {
// TODO: Make back-facing fragments a different color
  gl_FragColor = vec4(uColor, 1.0);
}
