// attribute highp vec4 qt_Vertex;
// attribute highp vec4 qt_MultiTexCoord0;
// uniform highp mat4 qt_ModelViewProjectionMatrix;
// varying highp vec4 qt_TexCoord0;
attribute vec3 vertexPosition;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjMatrix;

void main(void)
{
    vec4 eyeCoords = modelViewMatrix * vec4(vertexPosition, 1.0);
    gl_Position = modelViewProjMatrix * vec4(vertexPosition, 1.0);
    // gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    // qt_TexCoord0 = qt_MultiTexCoord0;
}
