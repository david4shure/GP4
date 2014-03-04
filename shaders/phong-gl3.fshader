#version 130
uniform vec3 uLight, uLight2, uColor; 
 
in vec3 vNormal; // normal to surface
in vec3 vPosition; // position of point on surface
 
out vec4 fragColor;
 
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
 
  fragColor = vec4(intensity.x, intensity.y, intensity.z, 1.0);
}
