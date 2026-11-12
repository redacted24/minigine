#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 aPos;
in vec3 FragPos;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos; // position of the light source in the world.

void main()
{
  // Texture
  FragColor = texture(texture1, TexCoord);

  // ambient
  float ambientStrength = 0.2;
  vec3 ambient = lightColor * ambientStrength;

  // diffuse
  vec3 norm = normalize(Normal); // normalize to avoid transformation issues
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0); // prevent negative values
  vec3 diffuse = diff * lightColor;

  // final result
  vec3 result = (ambient + diffuse) * FragColor.rgb;
  FragColor = vec4(result, 1.0);
}
