#version 400 core
out vec4 FragColor;
in vec3 fNor;
in vec2 uv;

//tileset data
uniform sampler2D tileSetTexture;
uniform vec2 tileSize; //size of each tile in the tileset
uniform vec2 tileSetSize; //size of the tileset in terms of x for rows and y for columns


//tilemap data
uniform usampler2D tileMapTexture; //grayscale tilemap texture

void main()
{
    ivec2 mapSize = textureSize(tileMapTexture, 0);
    ivec2 mapSample = ivec2(uv * vec2(mapSize));
    uint tileIndex = texelFetch(tileMapTexture, mapSample, 0).r;
    vec4 diffuse = texture(tileSetTexture, uv);
    FragColor = vec4(diffuse.r, diffuse.g, diffuse.b, 1);

    if (tileIndex == 0u)
    {
        FragColor = vec4(1, 0, 0, 1);
    }
    else if (tileIndex == 1u)
    {
        FragColor = vec4(0, 0, 1, 1);
    }

    FragColor.a=1;
    
}