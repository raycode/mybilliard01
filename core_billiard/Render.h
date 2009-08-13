#pragma once
namespace my_render {

INTERFACE_ Render {
public:
    virtual void render() = 0;
    virtual void addRenderEventListener( RenderEventListener * eventListener ) = 0;

    virtual void setUpAxis( domUpAxisType up ) = 0;
    virtual domUpAxisType getUpAxis() = 0;

#define ERenderClear_TARGET            0x00000001l  /* Clear target surface */
#define ERenderClear_ZBUFFER           0x00000002l  /* Clear target z buffer */
#define ERenderClear_STENCIL           0x00000004l  /* Clear stencil planes */

    virtual void clear( int Flags, NxU32 Color, float Z, NxU32 Stencil ) = 0;
    virtual bool beginScene() = 0;
    virtual void endScene() = 0;

    virtual Surface * getBackBuffer( size_t whichBackBuffer ) = 0;
    virtual void releaseSurface( Surface * ) = 0;

    virtual void pushMatrix() = 0;
    virtual void popMatrix() = 0;
    virtual void loadIdentity() = 0;
    virtual void multMatrix( NxMat34 ) = 0;

    enum EPrimitiveType {
        EPrimitive_POINTLIST = 1,
        EPrimitive_LINELIST = 2,
        EPrimitive_LINESTRIP = 3,
        EPrimitive_TRIANGLELIST = 4,
        EPrimitive_TRIANGLESTRIP = 5,
        EPrimitive_TRIANGLEFAN = 6,
        EPrimitive_FORCE_DWORD = 0x7fffffff,
    };

    virtual void drawPrimitive(
        EPrimitiveType primitiveType,
        NxU32 startVertex,
        NxU32 primitiveCount ) = 0;

    virtual void drawIndexedPrimitive(
        EPrimitiveType primitiveType,
        int baseVertexIndex,
        NxU32 minIndex,
        NxU32 numVertices,
        NxU32 startIndex,
        NxU32 primitiveCount ) = 0;

public: // render state
    enum ERenderStateType {
        ERenderState_ZENABLE = 7,
        ERenderState_FILLMODE = 8,
        ERenderState_SHADEMODE = 9,
        ERenderState_ZWRITEENABLE = 14,
        ERenderState_ALPHATESTENABLE = 15,
        ERenderState_LASTPIXEL = 16,
        ERenderState_SRCBLEND = 19,
        ERenderState_DESTBLEND = 20,
        ERenderState_CULLMODE = 22,
        ERenderState_ZFUNC = 23,
        ERenderState_ALPHAREF = 24,
        ERenderState_ALPHAFUNC = 25,
        ERenderState_DITHERENABLE = 26,
        ERenderState_ALPHABLENDENABLE = 27,
        ERenderState_FOGENABLE = 28,
        ERenderState_SPECULARENABLE = 29,
        ERenderState_FOGCOLOR = 34,
        ERenderState_FOGTABLEMODE = 35,
        ERenderState_FOGSTART = 36,
        ERenderState_FOGEND = 37,
        ERenderState_FOGDENSITY = 38,
        ERenderState_RANGEFOGENABLE = 48,
        ERenderState_STENCILENABLE = 52,
        ERenderState_STENCILFAIL = 53,
        ERenderState_STENCILZFAIL = 54,
        ERenderState_STENCILPASS = 55,
        ERenderState_STENCILFUNC = 56,
        ERenderState_STENCILREF = 57,
        ERenderState_STENCILMASK = 58,
        ERenderState_STENCILWRITEMASK = 59,
        ERenderState_TEXTUREFACTOR = 60,
        ERenderState_WRAP0 = 128,
        ERenderState_WRAP1 = 129,
        ERenderState_WRAP2 = 130,
        ERenderState_WRAP3 = 131,
        ERenderState_WRAP4 = 132,
        ERenderState_WRAP5 = 133,
        ERenderState_WRAP6 = 134,
        ERenderState_WRAP7 = 135,
        ERenderState_CLIPPING = 136,
        ERenderState_LIGHTING = 137,
        ERenderState_AMBIENT = 139,
        ERenderState_FOGVERTEXMODE = 140,
        ERenderState_COLORVERTEX = 141,
        ERenderState_LOCALVIEWER = 142,
        ERenderState_NORMALIZENORMALS = 143,
        ERenderState_DIFFUSEMATERIALSOURCE = 145,
        ERenderState_SPECULARMATERIALSOURCE = 146,
        ERenderState_AMBIENTMATERIALSOURCE = 147,
        ERenderState_EMISSIVEMATERIALSOURCE = 148,
        ERenderState_VERTEXBLEND = 151,
        ERenderState_CLIPPLANEENABLE = 152,
        ERenderState_POINTSIZE = 154,
        ERenderState_POINTSIZE_MIN = 155,
        ERenderState_POINTSPRITEENABLE = 156,
        ERenderState_POINTSCALEENABLE = 157,
        ERenderState_POINTSCALE_A = 158,
        ERenderState_POINTSCALE_B = 159,
        ERenderState_POINTSCALE_C = 160,
        ERenderState_MULTISAMPLEANTIALIAS = 161,
        ERenderState_MULTISAMPLEMASK = 162,
        ERenderState_PATCHEDGESTYLE = 163,
        ERenderState_DEBUGMONITORTOKEN = 165,
        ERenderState_POINTSIZE_MAX = 166,
        ERenderState_INDEXEDVERTEXBLENDENABLE = 167,
        ERenderState_COLORWRITEENABLE = 168,
        ERenderState_TWEENFACTOR = 170,
        ERenderState_BLENDOP = 171,
        ERenderState_POSITIONDEGREE = 172,
        ERenderState_NORMALDEGREE = 173,
        ERenderState_SCISSORTESTENABLE = 174,
        ERenderState_SLOPESCALEDEPTHBIAS = 175,
        ERenderState_ANTIALIASEDLINEENABLE = 176,
        ERenderState_MINTESSELLATIONLEVEL = 178,
        ERenderState_MAXTESSELLATIONLEVEL = 179,
        ERenderState_ADAPTIVETESS_X = 180,
        ERenderState_ADAPTIVETESS_Y = 181,
        ERenderState_ADAPTIVETESS_Z = 182,
        ERenderState_ADAPTIVETESS_W = 183,
        ERenderState_ENABLEADAPTIVETESSELLATION = 184,
        ERenderState_TWOSIDEDSTENCILMODE = 185,
        ERenderState_CCW_STENCILFAIL = 186,
        ERenderState_CCW_STENCILZFAIL = 187,
        ERenderState_CCW_STENCILPASS = 188,
        ERenderState_CCW_STENCILFUNC = 189,
        ERenderState_COLORWRITEENABLE1 = 190,
        ERenderState_COLORWRITEENABLE2 = 191,
        ERenderState_COLORWRITEENABLE3 = 192,
        ERenderState_BLENDFACTOR = 193,
        ERenderState_SRGBWRITEENABLE = 194,
        ERenderState_DEPTHBIAS = 195,
        ERenderState_WRAP8 = 198,
        ERenderState_WRAP9 = 199,
        ERenderState_WRAP10 = 200,
        ERenderState_WRAP11 = 201,
        ERenderState_WRAP12 = 202,
        ERenderState_WRAP13 = 203,
        ERenderState_WRAP14 = 204,
        ERenderState_WRAP15 = 205,
        ERenderState_SEPARATEALPHABLENDENABLE = 206,
        ERenderState_SRCBLENDALPHA = 207,
        ERenderState_DESTBLENDALPHA = 208,
        ERenderState_BLENDOPALPHA = 209,
        ERenderState_FORCE_DWORD = 0x7fffffff
    };
   
    virtual void getRenderState( ERenderStateType State, NxU32 * pValue ) = 0;
    virtual void setRenderState( ERenderStateType State, NxU32 Value ) = 0;

public:
    typedef int VertexBufferID;
    typedef int IndexBufferID;

public: virtual ~Render() {}
};

}