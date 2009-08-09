#pragma once
namespace my_render_d3d9_imp {


class RenderD3D9Imp : IMPLEMENTS_( Render ) {
public:
    RenderD3D9Imp();

public: // from Render
    virtual void setScreenWidth( int width );
    virtual void setScreenHeight( int height );

    virtual int getScreenWidth();
    virtual int getScreenHeight();

    virtual void setUpAxis( domUpAxisType up );
    virtual domUpAxisType getUpAxis();

    virtual bool openWindow( wstring title, bool bWindowed );
    virtual void closeWindow();
    virtual void setErrorNotify( RenderErrorNotify * errorNotify );

    virtual void pushMatrix();
    virtual void popMatrix();
    virtual void loadIdentity();
    virtual void multMatrix( NxMat34 );

    virtual void beginScene();
    virtual void endScene();

    virtual void clear( int Flags, NxU32 Color, float Z, NxU32 Stencil );
    virtual void Present();

    virtual void drawPrimitive(
        EPrimitiveType primitiveType,
        NxU32 startVertex,
        NxU32 primitiveCount );

    virtual void drawIndexedPrimitive(
        EPrimitiveType primitiveType,
        int baseVertexIndex,
        NxU32 minIndex,
        NxU32 numVertices,
        NxU32 startIndex,
        NxU32 primitiveCount );

    virtual void GetRenderState( ERenderStateType State, NxU32 * pValue );
    virtual void SetRenderState( ERenderStateType State, NxU32 Value );

private:
    domUpAxisType upAxis_;
    int width_, height_;
    RenderErrorNotify * errorNotify_;
};

}