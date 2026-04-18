#version 400 core
out vec4 FragColor;
in vec3 fNor;
in vec2 uv;

//tileset data
uniform sampler2D tileSetTexture;
uniform ivec2 tileSize; //size of each tile in the tileset
uniform ivec2 tileSetSize; //size of the tileset in terms of x for rows and y for columns


//tilemap data
uniform usampler2D tileMapTexture; //grayscale tilemap texture

void main()
{
    vec2 flippedUV = vec2(uv.x, 1.0 - uv.y);
    //tilemap index
    ivec2 mapSize = textureSize(tileMapTexture, 0);
    ivec2 mapSample = ivec2(flippedUV * vec2(mapSize));
    uint tileIndex = texelFetch(tileMapTexture, mapSample, 0).r - 1;

    //tilesetOffset
    ivec2 offsetInt = ivec2(mod(tileIndex, tileSetSize.x), tileIndex / tileSetSize.y);
    
    //uv coordinate
    
    vec2 normalize = mod(flippedUV * mapSize, vec2(1,1));

    vec2 place = (normalize + offsetInt) / tileSetSize;

    FragColor = texture(tileSetTexture, place);
    if (tileIndex == -1u) FragColor = vec4(0,0,0,0);
}