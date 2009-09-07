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
// ball 7
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string ball_7_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

#include "shared.fxh"
#include "light00.fxh"

float4x4 matWorldViewProjection : WorldViewProjection;
float4x4 matWorld : World;
float4x4 matWorldView : WorldView;

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   float3 Normal :   NORMAL0;
};

struct VS_OUTPUT 
{
   float4 Position :        POSITION0;
   float2 Texcoord :        TEXCOORD0;
   float3 ViewDirection :   TEXCOORD1;
   float3 LightDirection :  TEXCOORD2;
   float3 Normal :          TEXCOORD3;
};

VS_OUTPUT ball_7_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position         = mul( Input.Position, matWorldViewProjection );
   Output.Texcoord         = Input.Texcoord;

   float3 fvWorld          = mul( Input.Position, matWorld );

   float3 fvEminusW        = fvEyePosition - fvWorld;
   Output.ViewDirection    = mul( fvEminusW, matView );

   float3 fvLminusW        = Light00_Position - fvWorld;   
   Output.LightDirection   = mul( fvLminusW, matView );

   float3 fvNormal         = Input.Normal;
   Output.Normal           = mul( fvNormal, matWorldView );

   return( Output );
   
}



float4 fvAmbient
<
   string UIName = "fvAmbient";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.27, 0.26, 0.26, 1.00 );
float4 fvSpecular
<
   string UIName = "fvSpecular";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.70, 0.70, 0.70, 0.37 );
float4 fvDiffuse
<
   string UIName = "fvDiffuse";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 1.00, 0.99, 0.95, 1.00 );
float fSpecularPower
<
   string UIName = "fSpecularPower";
   string UIWidget = "Numeric";
   bool UIVisible =  true;
   float UIMin = 1.00;
   float UIMax = 100.00;
> = float( 16.00 );
texture base_Tex
<
   string ResourceName = "..\\textures\\poolb7.dds";
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

struct PS_INPUT 
{
   float2 Texcoord :        TEXCOORD0;
   float3 ViewDirection :   TEXCOORD1;
   float3 LightDirection:   TEXCOORD2;
   float3 Normal :          TEXCOORD3;
   
};

float4 ball_7_Pass_0_Pixel_Shader_ps_main( PS_INPUT Input ) : COLOR0
{
   const float3 lightDirection   = normalize( Input.LightDirection );
   const float3 normal           = normalize( Input.Normal );
   const float  N_Dot_L          = dot( normal, lightDirection ); 
   const float  diffuseAttn      = clamp( N_Dot_L, 0.f, 1.f );

   const float3 reflection       = normalize( ( ( 2.f * normal ) * ( N_Dot_L ) ) - lightDirection ); 
   const float3 viewDirection    = normalize( Input.ViewDirection );
   const float  R_Dot_V          = dot( reflection, viewDirection );
   const float  specularAttn     = pow( clamp( R_Dot_V, 0.00001f, 1.f ), fSpecularPower );
   
   float4 fvBaseColor            = tex2D( baseMap, Input.Texcoord );
   
   return ( fvAmbient + diffuseAttn * fvDiffuse ) * fvBaseColor + specularAttn * fvSpecular;
}



//--------------------------------------------------------------//
// Technique Section for ball 7
//--------------------------------------------------------------//
technique ball_7
{
   pass Pass_0
   {
      VertexShader = compile vs_1_1 ball_7_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 ball_7_Pass_0_Pixel_Shader_ps_main();
   }

}

