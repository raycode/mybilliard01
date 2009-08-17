#pragma once
namespace my_render_win32_dx9_imp {


class RenderBufferFactoryDX9Imp : IMPLEMENTS_INTERFACE( RenderBufferFactoryDX9 ) {
public: // from RenderBufferFactory
    virtual EffectShader * createEffectShader( wstring filename ) OVERRIDE;

    virtual VertexShader * createVertexShader_1_1( wstring filename, wstring entry ) OVERRIDE;
    virtual VertexShader * createVertexShader_2_0( wstring filename, wstring entry ) OVERRIDE;
    virtual VertexShader * createVertexShader_2_0_sw( wstring filename, wstring entry ) OVERRIDE;

    virtual PixelShader * createPixelShader_2_0( wstring filename, wstring entry ) OVERRIDE;
    virtual PixelShader * createPixelShader_2_sw( wstring filename, wstring entry ) OVERRIDE;

    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, const float * positions ) OVERRIDE;
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) OVERRIDE;
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) OVERRIDE;

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, const unsigned int * indexies ) OVERRIDE;
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, const unsigned int * indexies ) OVERRIDE;
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, const unsigned int * indexies ) OVERRIDE;

    virtual Surface * getBackBuffer( size_t whichBackBuffer ) OVERRIDE;

    virtual Texture * createTexture( wstring filename ) OVERRIDE;

    virtual bool destroyEffectShader( EffectShader *) OVERRIDE;
    virtual bool destroyVertexShader( VertexShader *) OVERRIDE;
    virtual bool destroyPixelShader( PixelShader *) OVERRIDE;
    virtual bool destroyVertexBuffer( VertexBuffer *) OVERRIDE;
    virtual bool destroyIndexBuffer( IndexBuffer *) OVERRIDE;
    virtual bool destroySurface( Surface * ) OVERRIDE;
    virtual bool destroyTexture( Texture * ) OVERRIDE;

public: // from RenderEventListener
    virtual void init( RenderBufferFactory * ) OVERRIDE;
    virtual void displayReset( int x, int y, int width, int height ) OVERRIDE;
    virtual void update( RenderBufferFactory *, float elapsedTime ) OVERRIDE;
    virtual void display( Render * ) OVERRIDE {}
    virtual void displayLost() OVERRIDE;
    virtual void destroy() OVERRIDE;

public:
    RenderBufferFactoryDX9Imp( LPDIRECT3DDEVICE9 d3dDevice );

private:
    LPDIRECT3DDEVICE9 getD3D9Device();

private: // resource manage
    void pushBackToReadyQueue( int resourceType, ReleasableResourceDX9 * newResource );
    void pushBackToActiveQueue( int resourceType, ReleasableResourceDX9 * newResource );
    bool destroy( ReleasableResourceDX9 * victim );
    void destroyAll();
    void acquireResources();
    void releaseByResourceType( int resourceType );


private:
    LPDIRECT3DDEVICE9 d3dDevice_;

private:
    enum { E_STATIC_VERTICES, E_DYNAMIC_VERTICES, E_STREAM_VERTICES,
           E_STATIC_INDICES, E_DYNAMIC_INDICES, E_STREAM_INDICES,
           E_EFFECT_SHADERS, E_VERTEX_SHADERS, E_PIXEL_SHADERS,
           E_SURFACES, E_TEXTURE, SIZE_OF_RESOURCETYPES };
    enum { EREADY_QUEUE, EACTIVE_QUEUE, SIZE_OF_QUEUE };
    typedef list< ReleasableResourceDX9Ptr > ReleasableResources;
    ReleasableResources resources_[ SIZE_OF_RESOURCETYPES ][ SIZE_OF_QUEUE ];
    bool bNeedToUpdate_;

    MY_UNIT_TEST_BACKDOOR;
};


}
