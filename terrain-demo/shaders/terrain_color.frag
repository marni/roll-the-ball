#version 330 core


// this comes from vert shader
// all in model space
in struct VertexModelspace {
    vec4 normal;
    vec4 color;
} vertex;


// data in camera space
in struct VertexCameraspace {
    vec4 position;
    vec4 normal;
    vec4 lightPosition;
} vertexCameraspace;


// OUTPUT color
out vec4 outColor;


// Light emission properties
// You probably want to put it as a uniform
vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);





/**
 * Calculates the diffuse component of our fragment
 * @param materialDiffuseColor The diffuse material color we are using.
 * @param normal The models normal in camera space.
 * @param lightDirection The normalized direction from the fragment towards the light.
 * @returns The resulting diffuse fragment.
 */
vec4 calculateDiffuseColor(vec4 materialDiffuseColor, vec4 normal, vec4 lightDirection) {
    
    // Cosine of the angle between the normal and the light direction,
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendicular to the triangle -> 0
    //  - light is behind the triangle -> 0
    float normalLightDotProduct = dot(normal, lightDirection);
    normalLightDotProduct = clamp(normalLightDotProduct, 0.0, 1.0);
    
    // The diffuse color depends on color of the light,
    // the normal light direction dot product
    // and the diffuse material.
    vec4 diffuseColor = lightColor  * normalLightDotProduct * materialDiffuseColor;
    
    return diffuseColor;
}


/**
 * Calculates the specular component of our fragment
 * @param materialSpecularColor The specular material color we are using.
 * @param normal The models normal in camera space.
 * @param lightDirection The normalized direction from the fragment towards the light.
 * @param specularExponent the exponent used to scale the size of the specular component.
 * @returns The resulting specular fragment color.
 */
vec4 calculateSpecularColor(vec4 materialSpecularColor, vec4 normal, vec4 lightDirection, float specularExponent) {
    
    // Eye vector (towards the camera)
    vec4 eyeDirection = vec4(0.0, 0.0, 0.0, 1.0) - vertexCameraspace.position;
    eyeDirection = normalize(eyeDirection);
    
    // Direction in which the triangle reflects the light
    vec4 lightReflectionDirection = reflect(-lightDirection, normal);
    
    // We need to make sure that it's possible for the light to hit the plane.
    // By multiplying the color with this are removing specular light bleed from behind objects.
    float normalLightDotProduct = dot(normal, lightDirection);
    normalLightDotProduct = ceil(clamp(normalLightDotProduct, 0.0, 1.0));
    
    // Cosine of the angle between the Eye vector and the Reflect vector,
    // clamped to 0
    //  - Looking into the reflection -> 1
    //  - Looking elsewhere -> < 1
    float eyeReflectionDotProduct = dot(eyeDirection, lightReflectionDirection);
    eyeReflectionDotProduct = clamp(eyeReflectionDotProduct, 0.0, 1.0);
    
    // The specular color depends on the color of the light,
    // the eye light reflection dot product by a power to control the size of the specular,
    // and our specular material.
    vec4 specularColor =
                        lightColor
                        * pow(eyeReflectionDotProduct, specularExponent)
                        * materialSpecularColor
                        * normalLightDotProduct;
    
    return specularColor;
}





void main() {
    
    // The texture function uses the texture and the interpolated coordinate
    // to find the color of the current fragment.
    // vec4 textureColor = texture(textureBuffer, fragmentTextureCoordinate.xy);
    
    // The output color of each fragment is set to be the result of
    // multiplying the vertex color with the texture color.
    // vec4 coloredTexture = textureColor * fragmentColor;
    
    vec4 materialDiffuseColor = vertex.color;
    vec4 materialAmbientColor = materialDiffuseColor * 0.1;
    vec4 materialSpecularColor = vec4(1.0, 1.0, 1.0, 1.0);
    float specularExponent = 5.0;
    
    // Normal of the computed fragment, in camera space
    vec4 normal = normalize(vertexCameraspace.normal);
    
    // Direction of the light (from the fragment to the light)
    vec4 lightDirection = vertexCameraspace.lightPosition - vertexCameraspace.position;
    lightDirection = normalize(lightDirection);
    
    vec4 diffuseColor = calculateDiffuseColor(materialDiffuseColor, normal, lightDirection);
    vec4 specularColor = calculateSpecularColor(materialSpecularColor, normal, lightDirection, specularExponent);
    
    outColor = materialAmbientColor + diffuseColor + specularColor;
}



