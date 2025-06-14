#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
    vec4 texColor = texture(texture1, TexCoord);
    
    // Discard pixels with very low alpha (optional, for sharper edges)
    if(texColor.a < 0.1)
        discard;
        
    FragColor = texColor;
}