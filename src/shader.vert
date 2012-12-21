// From glmdraw.c

attribute vec3 v_position;
attribute vec3 v_color;
uniform mat4 model, view, projection;
varying vec3 color;
uniform mat4 mvpMatrix;

varying vec3 normal;
void main() {
  // gl_Position = mvpMatrix * vec4(v_position, 1.0);
  gl_Position = projection * view * model * vec4(v_position, 1.0);
  color = v_color;

  // normal = gl_NormalMatrix * gl_Normal;
  // gl_TexCoord[0] = gl_MultiTexCoord0;
} 
