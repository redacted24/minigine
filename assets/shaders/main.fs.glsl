#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 lightColor;

void main()
{
  FragColor = texture(texture1, TexCoord);
  FragColor = vec4(FragColor.rgb * lightColor, 1.0);
}
