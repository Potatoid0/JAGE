//
//  default.vs
//  JAGE
//
//  Created by Benjamin Wulf on 1/16/26.
//

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec3 ourPos;

uniform float offset;

void main()
{
    gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
    ourPos.x = aPos.x + offset;
    ourPos.y = aPos.y + offset;
    ourPos.z = aPos.z + offset;
}
