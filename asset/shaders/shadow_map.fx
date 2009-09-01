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

float4x4 matWorldViewProjection : WorldViewProjection;

struct VS_INPUT 
{
   float4 Position : POSITION0;   
};

struct VS_OUTPUT 
{
   float4 Position :        POSITION0;
   float4 PositionOnUV :    TEXCOORD0;   
};

VS_OUTPUT Shadow_Map_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   float4 pos = mul( Input.Position, matWorldViewProjection );
   Output.Position = pos;
   Output.PositionOnUV = pos;

   return( Output );
   
}


struct PS_INPUT 
{
   float4 PositionOnUV :        TEXCOORD0;
};

float4 Shadow_Map_Pass_0_Pixel_Shader_ps_main( PS_INPUT Input ) : COLOR0
{
   float4 Output = Input.PositionOnUV.z;
   return Output;
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

