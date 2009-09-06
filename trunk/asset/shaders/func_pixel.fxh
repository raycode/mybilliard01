
float sampleDepthValue( in sampler2D shadowMap, in float2 texCoord )
{
   const float4 colorOnShadowMap = tex2D( shadowMap, texCoord );
   const float  depthOnShadowMap = colorOnShadowMap.r
                                 + colorOnShadowMap.g / 127.f;
   return depthOnShadowMap;
}

