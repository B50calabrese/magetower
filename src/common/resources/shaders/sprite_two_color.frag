#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D sprite;
uniform vec4 spriteColor1;
uniform vec4 spriteColor2;

void main()
{   
    vec4 texColor = texture(sprite, TexCoords);

    if (texColor == vec4(1.0, 1.0, 1.0, 1.0)) {
      color = texColor;
    } else {
      vec4 evaluatedColor = mix(spriteColor1, spriteColor2, TexCoords.x);
      color = evaluatedColor * texColor;
    }   
}