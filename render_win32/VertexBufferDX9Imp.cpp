#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


VertexBufferDX9Imp::VertexBufferDX9Imp( size_t numberOfPosition, float * positions )
: positions_( positions, positions + numberOfPosition )
{
    if( 0 == numberOfPosition || NULL == positions ) throw exception();
}

size_t VertexBufferDX9Imp::getNumberOfVertex()
{
    return positions_.size();
}

void VertexBufferDX9Imp::appendNormal( float * normals )
{
    normals_ = Normals( normals, normals + getNumberOfVertex() );
}

void VertexBufferDX9Imp::appendTexCoord( float * texCoords )
{
    TexCoords newTexCoords = TexCoords( texCoords, texCoords + getNumberOfVertex() );
    texCoords_Array_.push_back( newTexCoords );
}

bool VertexBufferDX9Imp::hasNormal()
{
    return normals_.size() != 0;
}

size_t VertexBufferDX9Imp::getNumberOfTexCoords()
{
    return texCoords_Array_.size();
}


}
