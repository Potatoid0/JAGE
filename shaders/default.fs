//
//  default.fs
//  JAGE
//
//  Created by Benjamin Wulf on 1/16/26.
//

#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform sampler2D secondTexture;
uniform float opacity;


void main()
{
    //FragColor = texture(ourTexture, texCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(ourTexture, texCoord), texture(secondTexture, vec2(texCoord.x*-1, texCoord.y)), opacity);
}
