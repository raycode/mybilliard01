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
// Shadow Map
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Shadow_Map_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

texture renderTexture_Tex : RenderColorTarget
<
   float2 RenderTargetDimensions = {512,512};
   string Format="D3DFMT_X8R8G8B8";
   float  ClearDepth=1.000000;
   int    ClearColor=-16777216;
>;
float4x4 Light0_WorldLightProjection : WorldViewProjection;

struct VS_INPUT 
{
   float4 Position : POSITION0;   
};

struct VS_OUTPUT 
{
   float4 Position :        POSITION0;
   float1 Depth :           TEXCOORD0;   
};

VS_OUTPUT Shadow_Map_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   float4 pos      = mul( Input.Position, Light0_WorldLightProjection );

   Output.Position = pos;

   Output.Depth    = pos.z / pos.w;

   return( Output );
   
}


float4 Shadow_Map_Pass_0_Pixel_Shader_ps_main( float1 inDepth: TEXCOORD0 ) : COLOR0
{
    float4 Depth;
    Depth.r = floor( inDepth[ 0 ] * 127.f ) / 127.f;
    Depth.g = floor( ( inDepth[ 0 ] - Depth.r ) * 127.f * 127.f ) / 127.f;
    Depth.b = 0.f;
    Depth.a = 1.f;
    return Depth;
}

//--------------------------------------------------------------//
// Pass 1
//--------------------------------------------------------------//
string Shadow_Map_Pass_1_ScreenAlignedQuad : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\ScreenAlignedQuad.3ds";

struct Shadow_Map_Pass_1_Vertex_Shader_VS_INPUT 
{
   float4 Position : POSITION0;
};

float  fInverseViewportWidth
<
   string UIName = "fInverseViewportWidth";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 0.00;
> = float( 0.00 );
float  fInverseViewportHeight
<
   string UIName = "fInverseViewportHeight";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 0.00;
> = float( 0.00 );

struct Shadow_Map_Pass_1_Vertex_Shader_VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 texCoord : TEXCOORD0;
};


Shadow_Map_Pass_1_Vertex_Shader_VS_OUTPUT Shadow_Map_Pass_1_Vertex_Shader_vs_main( Shadow_Map_Pass_1_Vertex_Shader_VS_INPUT Input )
{
   Shadow_Map_Pass_1_Vertex_Shader_VS_OUTPUT Output;

   Output.Position = Input.Position;

   Output.texCoord.x = 0.5 * (1 + Input.Position.x - fInverseViewportWidth);
   Output.texCoord.y = 0.5 * (1 - Input.Position.y - fInverseViewportHeight);

   return( Output );
}




float  Shadow_Map_Pass_1_Pixel_Shader_fInverseViewportWidth
<
   string UIName = "Shadow_Map_Pass_1_Pixel_Shader_fInverseViewportWidth";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 0.00;
> = float( 0.00 );
float  Shadow_Map_Pass_1_Pixel_Shader_fInverseViewportHeight
<
   string UIName = "Shadow_Map_Pass_1_Pixel_Shader_fInverseViewportHeight";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 0.00;
> = float( 0.00 );

sampler2D shadowMap = sampler_state
{
   Texture = (renderTexture_Tex);
   MINFILTER = LINEAR;
   MAGFILTER = LINEAR;
};

const float4 samples[4] =
{
   -1.0,  0.0, 0, 0.25,
    1.0,  0.0, 0, 0.25,
    0.0,  1.0, 0, 0.25,
    0.0, -1.0, 0, 0.25
};

float4 Shadow_Map_Pass_1_Pixel_Shader_ps_main( float2 texCoord: TEXCOORD0 ) : COLOR
{
   float col = 0;

   for( int i = 0; i < 4; ++i )
      col += samples[ i ].w *
         tex2D( shadowMap, texCoord +
            float2( samples[ i ].x * Shadow_Map_Pass_1_Pixel_Shader_fInverseViewportWidth,
                    samples[ i ].y * Shadow_Map_Pass_1_Pixel_Shader_fInverseViewportHeight )
         );

   return col;
}


//--------------------------------------------------------------//
// Technique Section for Shadow Map
//--------------------------------------------------------------//
technique Shadow_Map
{
   pass Pass_0
   <
      string Script = "RenderColorTarget0 = renderTexture_Tex;"
                      "ClearColor = (0, 0, 0, 255);"
                      "ClearDepth = 1.000000;";
   >
   {
      VertexShader = compile vs_1_1 Shadow_Map_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Shadow_Map_Pass_0_Pixel_Shader_ps_main();
   }

   pass Pass_1
   {
      VertexShader = compile vs_1_1 Shadow_Map_Pass_1_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Shadow_Map_Pass_1_Pixel_Shader_ps_main();
   }

}

