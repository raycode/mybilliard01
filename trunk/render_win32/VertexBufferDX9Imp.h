#pragma once
namespace my_render_win32_dx9_imp {


class VertexBufferDX9Imp : IMPLEMENTS_( VertexBufferDX9 ) {
public: // from VertexBuffer
    virtual void appendNormal_Array( float * normals_3floatsForEach ) OVERRIDE;
    virtual void appendTexCoord2D_Array( float * texCoords_2floatsForEach ) OVERRIDE;

    virtual size_t getNumberOfVertex() OVERRIDE;
    virtual bool hasNormal() OVERRIDE;
    virtual size_t getNumberOfTexCoords() OVERRIDE;

public: // from VertexBufferDX9
    virtual size_t getSizeInByte() OVERRIDE;
    virtual unsigned long getFVF() OVERRIDE;
    virtual size_t getSizeInByteForEachVertex() OVERRIDE;

    virtual void setVertexBufferDX9( LPDIRECT3DVERTEXBUFFER9 ) OVERRIDE;
    virtual LPDIRECT3DVERTEXBUFFER9 getVertexBufferDX9() OVERRIDE;

    virtual void writeOntoDevice( DWORD lockingFlags ) OVERRIDE;
    virtual void releaseVertexBufferDX9() OVERRIDE;

public:
    VertexBufferDX9Imp( size_t numberOfPosition, const float * positions_3floatsForEach );
    ~VertexBufferDX9Imp();

private:
    struct Position {
        float val[3];
        enum { sizeInByte = 3 * sizeof(float) };
    };
    typedef vector< Position > Positions;
    Positions positions_;

private:
    struct Normal {
        float val[3];
        enum { sizeInByte = 3 * sizeof(float) };
    };
    typedef vector< Normal > Normals;
    Normals normals_;

private:
    struct TexCoord2D {
        float val[2];
        enum { sizeInByte = 2 * sizeof(float) };
    };
    typedef vector< TexCoord2D > TexCoords;
    typedef vector< TexCoords > TexCoords_Array;
    TexCoords_Array texCoords_Array_;

private:
    LPDIRECT3DVERTEXBUFFER9 vertexBufferDX9_;

private:
    struct Pimpl;
    MY_UNIT_TEST_BACKDOOR;
};


}
