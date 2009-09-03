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
// Screen-AlignedQuad
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Single Pass
//--------------------------------------------------------------//
string Screen_AlignedQuad_Single_Pass_ScreenAlignedQuad : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Advanced\\HeatHaze\\ScreenAlignedQuad.3ds";

float  outputWidthInverse : ViewportWidthInverse;
float  outputHeightInverse : ViewportHeightInverse;

struct VS_INPUT 
{
   float4 Position : POSITION0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 texCoord : TEXCOORD0;
};


VS_OUTPUT Screen_AlignedQuad_Single_Pass_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = Input.Position;

   Output.texCoord.x = 0.5 * (1 + Input.Position.x - outputWidthInverse );
   Output.texCoord.y = 0.5 * (1 - Input.Position.y - outputHeightInverse );

   return( Output );
}

float  inputWidthInverse
<
   string UIName = "inputWidthInverse";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 0.00 );
float  inputHeightInverse
<
   string UIName = "inputHeightInverse";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 0.00 );
texture inputTexture_Tex
<
   string ResourceName = "..\\textures\\Coin.dds";
>;
sampler2D inputTexture = sampler_state
{
   Texture = (inputTexture_Tex);
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   ADDRESSW = WRAP;
   MINFILTER = LINEAR;
   MIPFILTER = LINEAR;
   MAGFILTER = LINEAR;
};

float4 Screen_AlignedQuad_Single_Pass_Pixel_Shader_ps_main( float2 texCoord: TEXCOORD0 ) : COLOR
{
   return tex2D( inputTexture, texCoord );
}


//--------------------------------------------------------------//
// Technique Section for Screen-AlignedQuad
//--------------------------------------------------------------//
technique Screen_AlignedQuad
{
   pass Single_Pass
   {
      CULLMODE = NONE;

      VertexShader = compile vs_1_1 Screen_AlignedQuad_Single_Pass_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Screen_AlignedQuad_Single_Pass_Pixel_Shader_ps_main();
   }

}

