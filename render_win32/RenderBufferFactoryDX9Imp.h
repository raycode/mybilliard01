#pragma once
namespace my_render_win32_dx9_imp {


class RenderBufferFactoryDX9Imp : IMPLEMENTS_( RenderBufferFactoryDX9 ) {
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

    virtual bool releaseEffectShader( EffectShader *) OVERRIDE;
    virtual bool releaseVertexShader( VertexShader *) OVERRIDE;
    virtual bool releasePixelShader( PixelShader *) OVERRIDE;
    virtual bool releaseVertexBuffer( VertexBuffer *) OVERRIDE;
    virtual bool releaseIndexBuffer( IndexBuffer *) OVERRIDE;
    virtual bool releaseSurface( Surface * ) OVERRIDE;
    virtual bool releaseTexture( Texture * ) OVERRIDE;

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

private: // upload
    void uploadVertexBuffers( const list< VertexBufferDX9Ptr > & among, DWORD usage, D3DPOOL pool, DWORD lockingFlags );
    void uploadIndexBuffers( const list< IndexBufferDX9Ptr > & among, DWORD usage, D3DPOOL pool, DWORD lockingFlags );

    void uploadStaticBuffers();
    void uploadDynamicBuffers();
    void uploadSteamBuffers();

private: // release
    void releaseStaticBuffers();
    void releaseDynamicBuffers();
    void releaseStreamBuffers();

    template < typename ElementType, typename EachType >
    static bool release( ElementType resource, typename EachType & among ) {
        MY_FOR_EACH( typename EachType, iter, among ) {
            if( resource != &**iter ) continue;
            among.erase( iter );
            return true;
        }
        return false;
    }

private:
    LPDIRECT3DDEVICE9 d3dDevice_;

private:
    enum { EREADY_QUEUE = 0, EACTIVE_QUEUE, SIZE_OF_QUEUE };

    typedef list< VertexBufferDX9Ptr > StaticVertices;
    StaticVertices staticVertices_[SIZE_OF_QUEUE];

    typedef list< VertexBufferDX9Ptr > DynamicVertices;
    DynamicVertices dynamicVertices_[SIZE_OF_QUEUE];

    typedef list< VertexBufferDX9Ptr > StreamVertices;
    StreamVertices streamVertices_[SIZE_OF_QUEUE];

    typedef list< IndexBufferDX9Ptr > StaticIndexies;
    StaticIndexies staticIndexies_[SIZE_OF_QUEUE];

    typedef list< IndexBufferDX9Ptr > DynamicIndexies;
    DynamicIndexies dynamicIndexies_[SIZE_OF_QUEUE];

    typedef list< IndexBufferDX9Ptr > StreamIndexies;
    StreamIndexies streamIndexies_[SIZE_OF_QUEUE];

    typedef list< SurfaceDX9ImpPtr > Surfaces;
    Surfaces surfaces_[SIZE_OF_QUEUE];

    typedef list< EffectShaderPtr > EffectShaders;
    EffectShaders effectShaders_;

private:
    bool bNeedToUpdate_;

    MY_UNIT_TEST_BACKDOOR;
};


}
