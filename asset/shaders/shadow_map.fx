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
// Render To Texture
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 1
//--------------------------------------------------------------//
string Render_To_Texture_Pass_1_Teapot : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Teapot.3ds";

texture renderTexture_Tex : RenderColorTarget
<
   float2 RenderTargetDimensions = {512,512};
   string Format="D3DFMT_A8R8G8B8";
   float  ClearDepth=1.000000;
   int    ClearColor=0;
>;
float4x4 matViewProjection : ViewProjection;
struct VS_OUTPUT
{
   float4 Pos: POSITION;
};
VS_OUTPUT Render_To_Texture_Pass_1_Vertex_Shader_main( float4 Pos: POSITION )
{
   VS_OUTPUT Out = (VS_OUTPUT) 0; 
   Out.Pos = mul(Pos,matViewProjection);
   return Out;
}






float4 Render_To_Texture_Pass_1_Pixel_Shader_main( float4 Diff: COLOR0 ) : COLOR
{
    float4 c; 
    c[0] = 1.0;
    c[1] = 0.0;
    c[2] = 0.0;
    c[3] = 1.0;

    return c;
}


//--------------------------------------------------------------//
// Pass 2
//--------------------------------------------------------------//
string Render_To_Texture_Pass_2_Teapot : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Teapot.3ds";

float4x4 matProjection : Projection;
float4x4 matTeapotXForm
<
   string UIName = "matTeapotXForm";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
> = float4x4( 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 240.00, 0.00, 0.00, 0.00, 1.00 );
struct Render_To_Texture_Pass_2_Vertex_Shader_VS_OUTPUT
{
   float4 Pos: POSITION;
   float2 Tex: TEXCOORD0;
};
Render_To_Texture_Pass_2_Vertex_Shader_VS_OUTPUT Render_To_Texture_Pass_2_Vertex_Shader_main( float4 Pos: POSITION,
                float2 Tex:  TEXCOORD0 )
{
   Render_To_Texture_Pass_2_Vertex_Shader_VS_OUTPUT Out = (Render_To_Texture_Pass_2_Vertex_Shader_VS_OUTPUT) 0; 
   Out.Pos = mul( Pos, mul(matTeapotXForm,matProjection) );
   Out.Tex = Tex;
   return Out;
}








float4 ambient
<
   string UIName = "ambient";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.50, 0.50, 0.50, 1.00 );
sampler renderTexture = sampler_state
{
   Texture = (renderTexture_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
   MIPFILTER = LINEAR;
};
float4 Render_To_Texture_Pass_2_Pixel_Shader_main( float4 Diff: COLOR0,
             float2 Tex: TEXCOORD0 ) : COLOR
{
    return tex2D( renderTexture, Tex ) + ambient;
}





//--------------------------------------------------------------//
// Technique Section for Render To Texture
//--------------------------------------------------------------//
technique Render_To_Texture
{
   pass Pass_1
   <
      string Script = "RenderColorTarget0 = renderTexture_Tex;"
                      "ClearColor = (0, 0, 0, 0);"
                      "ClearDepth = 1.000000;";
   >
   {
      VertexShader = compile vs_1_1 Render_To_Texture_Pass_1_Vertex_Shader_main();
      PixelShader = compile ps_2_0 Render_To_Texture_Pass_1_Pixel_Shader_main();
   }

   pass Pass_2
   {
      VertexShader = compile vs_1_1 Render_To_Texture_Pass_2_Vertex_Shader_main();
      PixelShader = compile ps_2_0 Render_To_Texture_Pass_2_Pixel_Shader_main();
   }

}

