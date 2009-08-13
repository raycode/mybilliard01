#pragma once
namespace my_render_win32_dx9_imp {


class VertexBufferDX9Imp : IMPLEMENTS_( VertexBufferDX9 ) {
public: // from VertexBuffer
    virtual void appendNormal( float * normals ) OVERRIDE;
    virtual void appendTexCoord( float * texCoords ) OVERRIDE;

    virtual size_t getNumberOfVertex() OVERRIDE;
    virtual bool hasNormal() OVERRIDE;
    virtual size_t getNumberOfTexCoords() OVERRIDE;

public:
    VertexBufferDX9Imp( size_t numberOfPosition, float * positions );

private:
    typedef vector< float > Positions;
    Positions positions_;

    typedef vector< float > Normals;
    Normals normals_;

    typedef vector< float > TexCoords;
    typedef vector< TexCoords > TexCoords_Array;
    TexCoords_Array texCoords_Array_;
};


}
