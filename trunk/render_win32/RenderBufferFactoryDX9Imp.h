#pragma once
namespace my_render_win32_dx9_imp {


class RenderBufferFactoryDX9Imp : IMPLEMENTS_INTERFACE( RenderBufferFactoryDX9 ) {
public: // from RenderBufferFactory
    virtual EffectShader * createEffectShader( wstring filename ) OVERRIDE;

    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, const float * positions ) OVERRIDE;
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) OVERRIDE;
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) OVERRIDE;

    virtual Texture * createTexture( wstring filename ) OVERRIDE;
    virtual RenderTarget * createRenderTarget( size_t width, size_t height ) OVERRIDE;

    virtual bool destroyEffectShader( EffectShader *) OVERRIDE;
    virtual bool destroyVertexBuffer( VertexBuffer *) OVERRIDE;
    virtual bool destroyTexture( Texture * ) OVERRIDE;
    virtual bool destroyRenderTarget( RenderTarget * ) OVERRIDE;

public: // from RenderEventListener
    virtual void init() OVERRIDE;
    virtual void displayReset( RenderBufferFactory *, int x, int y, int width, int height ) OVERRIDE;
    virtual void update( RenderBufferFactory *, float elapsedTime ) OVERRIDE;
    virtual void display( Render * ) OVERRIDE {}
    virtual void displayLost() OVERRIDE;
    virtual void destroy() OVERRIDE;

public:
    RenderBufferFactoryDX9Imp( LPDIRECT3DDEVICE9 d3dDevice );

private:
    LPDIRECT3DDEVICE9 getD3D9Device();

private: // resource manage
    void pushBackToReadyQueue( int resourceType, ReleasableResourceDX9Ptr newResource );
    void pushBackToActiveQueue( int resourceType, ReleasableResourceDX9Ptr newResource );
    bool destroy( ReleasableResourceDX9 * victim );
    void destroyAll();

    void acquireResources();
    void acquireResourcesByType( int resourceType );
    void releaseResourceByType( int resourceType );

    void acquireEffectPool();
    void releaseEffectPool();

    EffectShaderDX9Ptr findEffectShaderFromAlreadyCreated( wstring filename );
    TextureDX9Ptr findTextureFromAlreadyCreated( wstring filename );


private:
    LPDIRECT3DDEVICE9 d3dDevice_;

    MY_SMART_PTR( ID3DXEffectPool );
    ID3DXEffectPoolPtr d3dEffectPool_;

private:
    enum { E_STATIC_VERTICES, E_DYNAMIC_VERTICES, E_STREAM_VERTICES,
           E_RENDER_TARGETS, E_TEXTURES, E_EFFECT_SHADERS, SIZE_OF_RESOURCE_TYPES };
    enum { EREADY_QUEUE, EACTIVE_QUEUE, SIZE_OF_QUEUE };
    typedef list< ReleasableResourceDX9Ptr > ReleasableResources;
    ReleasableResources resources_[ SIZE_OF_RESOURCE_TYPES ][ SIZE_OF_QUEUE ];
    bool bNeedToUpdate_;

    MY_UNIT_TEST_BACKDOOR;
};


}
