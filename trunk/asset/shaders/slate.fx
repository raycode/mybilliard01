//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// slate
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string slate_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

#include "shared.fxh"
#include "light00.fxh"

float4x4 matWorldViewProjection : WorldViewProjection;
float4x4 matWorldView : WorldView;
float4x4 matWorld : World;


struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   float3 Normal :   NORMAL0;
};

struct VS_OUTPUT 
{
   float4 Position :           POSITION0;
   float2 Texcoord :           TEXCOORD0;
   float3 ViewDirection :      TEXCOORD1;
   float3 LightDirection :     TEXCOORD2;
   float3 Normal :             TEXCOORD3;
   float3 PositionFromLight00: TEXCOORD4;   
};

VS_OUTPUT slate_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position         = mul( Input.Position, matWorldViewProjection );
   Output.Texcoord         = Input.Texcoord * 2;

   float3 fvWorld          = mul( Input.Position, matWorld );

   float3 fvEminusW        = fvEyePosition - fvWorld;
   Output.ViewDirection    = mul( fvEminusW, matView );

   float3 fvLminusW        = Light00_Position - fvWorld;   
   Output.LightDirection   = mul( fvLminusW, matView );

   float3 fvNormal         = Input.Normal;
   Output.Normal           = mul( fvNormal, matWorldView );

   float4 posFromLight00   = mul( Input.Position, Light00_WorldViewProjection );

   Output.PositionFromLight00.x = ( posFromLight00.x / posFromLight00.w + 1 ) * 0.5f;
   Output.PositionFromLight00.y = (-posFromLight00.y / posFromLight00.w + 1 ) * 0.5f;
   Output.PositionFromLight00.z = posFromLight00.z / posFromLight00.w;
   
   return( Output );
   
}



const float4 fvAmbient
<
   string UIName = "fvAmbient";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.52, 0.52, 0.52, 1.00 );
const float4 fvSpecular;
const float4 fvDiffuse
<
   string UIName = "fvDiffuse";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.52, 0.51, 0.49, 1.00 );
const float  fSpecularPower;
texture base_Tex
<
   string ResourceName = "..\\textures\\green.jpg";
>;
sampler2D baseMap = sampler_state
{
   Texture = (base_Tex);
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   MINFILTER = LINEAR;
   MAGFILTER = LINEAR;
   MIPFILTER = LINEAR;
};
sampler2D shadowMap0;


struct PS_INPUT 
{
   float2 Texcoord :            TEXCOORD0;
   float3 PositionFromLight00 : TEXCOORD4;   
};

#include "func_pixel.fxh"

float4 slate_Pass_0_Pixel_Shader_ps_main( PS_INPUT Input ) : COLOR0
{
   const float  depthOnShadowMap0 = sampleDepthValue( shadowMap0, Input.PositionFromLight00.xy );
   const float  actualDepth       = Input.PositionFromLight00.z;
   const float  depthUnderObject  = clamp( actualDepth - depthOnShadowMap0, 1, 2 );
   const bool   bUnderShadow      = ( depthUnderObject > 0 );

   const float4 baseColor         = tex2D( baseMap, Input.Texcoord );
   float4 color_OutShadow   = clamp( ( fvAmbient + fvDiffuse ) * baseColor, 0, 1 );
   float4 color_UnderShadow = clamp( fvAmbient * baseColor / depthUnderObject, 0, 1 );
   color_OutShadow.a = 1;
   color_UnderShadow.a = 1;
   
//   return color_UnderShadow;
   return color_OutShadow;
   return( bUnderShadow ? color_UnderShadow : color_OutShadow );
}



//--------------------------------------------------------------//
// Technique Section for slate
//--------------------------------------------------------------//
technique slate
{
   pass Pass_0
   {
      VertexShader = compile vs_1_1 slate_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 slate_Pass_0_Pixel_Shader_ps_main();
   }

}

