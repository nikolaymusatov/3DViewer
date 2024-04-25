attribute vec3 vertexPosition;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjMatrix;

void main(void)
{
    vec4 eyeCoords = modelViewMatrix * vec4(vertexPosition, 1.0);
    gl_Position = modelViewProjMatrix * vec4(vertexPosition, 1.0);
}
