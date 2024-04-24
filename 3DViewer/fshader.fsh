// uniform sampler2D qt_Texture0;
// varying highp vec4 qt_TexCoord0;
uniform bool renderTexture;
uniform vec4 pColor;

void main(void)
{
    gl_FragColor = pColor;
}
