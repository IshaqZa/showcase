#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 texCo;
uniform sampler2D tex;
uniform bool isTex;

void main()
{
    if(isTex){
        FragColor = texture(tex, texCo);
    }else{
        FragColor = color;
    }
}