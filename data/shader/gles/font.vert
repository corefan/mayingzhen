// Atttributes
attribute vec3 a_position;
attribute vec2 a_texCoord0;
attribute vec4 a_color0;

// Uniforms
uniform mat4 u_worldViewProjectionMatrix;

// Varyings
varying vec2 v_texCoord;
varying vec4 v_color;


void main()
{
    gl_Position = u_worldViewProjectionMatrix * vec4(a_position, 1);
    v_texCoord = a_texCoord0;
    v_color = a_color0;
}
