uniform vec3 uLight, uLight2, uColor;

varying vec3 vNormal;
varying vec3 vPosition;

void main() {
// TODO: implement specular highlights (both light sources)
// TODO: implement phong lighting on back-facing fragments too
  vec3 toLight = uLight - vec3(vPosition);
  vec3 toLight2 = uLight2 - vec3(vPosition);
  toLight = normalize(toLight);
  toLight2 = normalize(toLight2);
  vec3 normal = normalize(vNormal);
 
  float diffuse = max(0.0, dot(normal, toLight));
  diffuse += max(0.0, dot(normal, toLight2));
  vec3 intensity =  vec3(0.1,0.1,0.1) + uColor * diffuse;
 
  gl_FragColor = vec4(intensity.x, intensity.y, intensity.z, 1.0);
}
