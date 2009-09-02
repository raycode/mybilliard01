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
    // Output the depth as computed by
    // the vertex shader
    float4 Depth;
    Depth.w = 1.0;
    Depth.x = floor( inDepth.x * 127 ) / 127;
    Depth.y = floor( ( inDepth.x - Depth.x ) * 127 * 127 ) / 127;
    Depth.z = 0;
    return Depth;
}

//--------------------------------------------------------------//
// Technique Section for Shadow Map
//--------------------------------------------------------------//
technique Shadow_Map
{
   pass Pass_0
   {
      VertexShader = compile vs_1_1 Shadow_Map_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Shadow_Map_Pass_0_Pixel_Shader_ps_main();
   }

}

