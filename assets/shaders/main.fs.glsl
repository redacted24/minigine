#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 aPos;
in vec3 FragPos;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos; // position of the light source in the world.

// TODO: currently specular lighting calculated from world view
uniform vec3 viewPos;

void main()
{
  // Texture
  FragColor = texture(texture1, TexCoord);

  // ambient
  float ambientStrength = 0.5;
  vec3 ambient = lightColor * ambientStrength;

  // diffuse
  vec3 norm = normalize(Normal); // normalize to avoid transformation issues
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0); // prevent negative values
  vec3 diffuse = diff * lightColor;

  // specular
  float specularStrength = 0.5;
  vec3 viewDir = normalize(viewPos - FragPos);
  // NOTE: negative lightdir due to subtraction order earlier
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 48);
  vec3 specular = specularStrength * spec * lightColor;

  // final result
  vec3 result = (ambient + diffuse + specular) * FragColor.rgb;
  FragColor = vec4(result, 1.0);
}
