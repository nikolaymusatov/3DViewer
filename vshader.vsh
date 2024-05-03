attribute vec3 vertexPosition;
uniform mat4 mvpMatrix;

void main(void)
{
//vec4 eyeCoords = modelViewMatrix * vec4(vertexPosition, 1.0);
    gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);
}
