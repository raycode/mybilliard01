#pragma once
namespace my_render_win32_dx9_imp {


class VertexBufferDX9Imp : IMPLEMENTS_INTERFACE( VertexBufferDX9 ) {
public: // from VertexBuffer
    virtual bool appendTexCoord1D_Array( const float * texCoords_1floatsForEach, size_t usageIndex ) OVERRIDE;
    virtual bool appendTexCoord2D_Array( const float * texCoords_2floatsForEach, size_t usageIndex ) OVERRIDE;
    virtual bool appendTexCoord3D_Array( const float * texCoords_3floatsForEach, size_t usageIndex ) OVERRIDE;
    virtual bool appendTexCoord4D_Array( const float * texCoords_4floatsForEach, size_t usageIndex ) OVERRIDE;
    virtual bool appendNormal_Array( const float * normals_3floatsForEach, size_t usageIndex ) OVERRIDE;
    virtual bool appendBinormal_Array( const float * binormal_3floatsForEach, size_t usageIndex ) OVERRIDE;
    virtual bool appendTangent_Array( const float * tangent_3floatsForEach, size_t usageIndex ) OVERRIDE;
    virtual bool appendUV_Array( const float * ut_2floatsForEach, size_t usageIndex ) OVERRIDE;
    virtual bool appendColor_Array( const NxU32 * color_3UnsignedIntForEach, size_t usageIndex ) OVERRIDE;

    virtual size_t getNumberOfVertex() OVERRIDE;

public: // from VertexBufferDX9
    virtual size_t getSizeInByteForEachVertex() OVERRIDE;
    virtual LPDIRECT3DVERTEXDECLARATION9 getVertexDeclarationDX9() OVERRIDE;
    virtual LPDIRECT3DVERTEXBUFFER9 getVertexBufferDX9() OVERRIDE;

public: // from ReleasableResource
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    VertexBufferDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, size_t numberOfPosition, const float * positions_3floatsForEach, DWORD usage, D3DPOOL pool, DWORD lockingFlags  );
    ~VertexBufferDX9Imp();

private:
    size_t getSizeInByteForTotal();

    D3DVERTEXELEMENT9 * getVertexElement();
    void writeOntoDevice( DWORD lockingFlags );

    size_t updateOffset();
    void writeOntoBuffer( float * buffer, size_t step );
    bool isUsageIndexInUse( int usage, size_t usageIndex );

    LPDIRECT3DDEVICE9 getD3D9Device();

private:
    struct Storage {
        unsigned int val[4];
    };

    class StorageContainer {
    private:
        size_t offset_;
        size_t usageIndex_;
        D3DDECLTYPE declType_;
        size_t sizeInByteForEach_;

    public:
        typedef vector< Storage > Storage_Array;
        Storage_Array v;

        StorageContainer( const void * src, size_t howMany, size_t usageIndex, D3DDECLTYPE declType )
            : usageIndex_( usageIndex )
            , declType_( declType )
            , sizeInByteForEach_( getSizeOfDeclType( declType ) )
        {
            Storage tmp;
            for( size_t i = 0; i < howMany; ++i ) {
                const size_t offset = i * sizeInByteForEach();
                memcpy( (BYTE*) &(tmp.val), ((BYTE*) src) + offset, sizeInByteForEach() );
                v.push_back( tmp );
            }
        }

        size_t sizeInByteForEach() const { return sizeInByteForEach_; }

        D3DDECLTYPE getDeclarationType() const { return declType_; }

        size_t getUsageIndex() const { return usageIndex_; }

        void setOffset( size_t offset ) { offset_ = offset; }

        size_t getOffset() const { return offset_; }

        bool empty() const { return v.empty(); }

        void copyOntoBuffer( float * buffer, size_t step ) {
            size_t loc = 0;
            MY_FOR_EACH( Storage_Array, iter, v ) {
                memcpy( ((BYTE*) buffer) + loc + getOffset(), (BYTE*)&(iter->val), sizeInByteForEach() );
                loc += step;
            }
        }

        static size_t getSizeOfDeclType( D3DDECLTYPE declType ) {
            if( D3DDECLTYPE_FLOAT1 == declType ) return sizeof(float);
            if( D3DDECLTYPE_FLOAT2 == declType ) return sizeof(float) * 2;
            if( D3DDECLTYPE_FLOAT3 == declType ) return sizeof(float) * 3;
            if( D3DDECLTYPE_FLOAT4 == declType ) return sizeof(float) * 4;
            if( D3DDECLTYPE_D3DCOLOR == declType ) return sizeof(D3DCOLOR);
            return sizeof(float) * 4;
        }
    };

    enum { NumberOfStorageContainers = 16 };
    typedef vector< StorageContainer > StorageContainer_Array;
    StorageContainer_Array storageContainer_array_[ NumberOfStorageContainers ];


private:
    LPDIRECT3DDEVICE9 d3d9Device_;
    DWORD usage_;
    D3DPOOL pool_;
    DWORD lockingFlags_;
    vector< D3DVERTEXELEMENT9 > vertexElementDX9_;

private:
    LPDIRECT3DVERTEXDECLARATION9 vertexDeclarationDX9_;
    LPDIRECT3DVERTEXBUFFER9 vertexBufferDX9_;

private:
    struct Pimpl;
    MY_UNIT_TEST_BACKDOOR;
};


}
