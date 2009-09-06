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
// CUE_BALL
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string CUE_BALL_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

#include "shared.fxh"
#include "light0.fxh"

float4x4 matWorldViewProjection : WorldViewProjection;
float4x4 matWorld : World;
float4x4 matWorldView : WorldView;

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float3 Normal :   NORMAL0;
   
};

struct VS_OUTPUT 
{
   float4 Position :        POSITION0;
   float3 ViewDirection :   TEXCOORD0;
   float3 LightDirection :  TEXCOORD1;
   float3 Normal :          TEXCOORD2;
   
};

VS_OUTPUT CUE_BALL_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position         = mul( Input.Position, matWorldViewProjection );

   float3 fvWorld          = mul( Input.Position, matWorld );

   float3 fvEminusW        = fvEyePosition - fvWorld;
   Output.ViewDirection    = mul( fvEminusW, matView );

   float3 fvLminusW        = Light0_Position - fvWorld;   
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
> = float4( 0.49, 0.48, 0.48, 1.00 );
float4 fvSpecular
<
   string UIName = "fvSpecular";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.49, 0.49, 0.49, 1.00 );
float4 fvDiffuse
<
   string UIName = "fvDiffuse";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.51, 0.51, 0.49, 1.00 );
float fSpecularPower
<
   string UIName = "fSpecularPower";
   string UIWidget = "Numeric";
   bool UIVisible =  true;
   float UIMin = 1.00;
   float UIMax = 100.00;
> = float( 68.32 );
sampler2D baseMap;

struct PS_INPUT 
{
   float3 ViewDirection :   TEXCOORD0;
   float3 LightDirection:   TEXCOORD1;
   float3 Normal :          TEXCOORD2;
   
};

float4 CUE_BALL_Pass_0_Pixel_Shader_ps_main( PS_INPUT Input ) : COLOR0
{
   float3 fvLightDirection = normalize( Input.LightDirection );
   float3 fvNormal         = normalize( Input.Normal );
   float  fNDotL           = dot( fvNormal, fvLightDirection ); 
   
   float3 fvReflection     = normalize( ( ( 2.0f * fvNormal ) * ( fNDotL ) ) - fvLightDirection ); 
   float3 fvViewDirection  = normalize( Input.ViewDirection );
   float  fRDotV           = max( 0.00001f, dot( fvReflection, fvViewDirection ) );
   
   float4 fvTotalAmbient   = fvAmbient; 
   float4 fvTotalDiffuse   = fvDiffuse * fNDotL; 
   float4 fvTotalSpecular  = fvSpecular * pow( fRDotV, fSpecularPower );
   
   return( saturate( fvTotalAmbient + fvTotalDiffuse + fvTotalSpecular ) );
}



//--------------------------------------------------------------//
// Technique Section for CUE_BALL
//--------------------------------------------------------------//
technique CUE_BALL
{
   pass Pass_0
   {
      VertexShader = compile vs_1_1 CUE_BALL_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 CUE_BALL_Pass_0_Pixel_Shader_ps_main();
   }

}

