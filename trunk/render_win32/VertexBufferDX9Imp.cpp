#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


struct VertexBufferDX9Imp::Pimpl {

    template< typename EachType, typename GroupType, typename StreamType >
    static void store_Array( GroupType & onto, StreamType * from, size_t howMany )
    {
        const size_t sizeInByte = EachType::sizeInByte;
        for( size_t i = 0; i < howMany; ++i ) {
            const size_t offset = i * sizeInByte;

            EachType tmp;
            memcpy( &(tmp.val), from + offset, sizeInByte );

            onto.push_back( tmp );
        }
    }

    template < typename EachType, typename GroupType >
    static void writeOntoDeviceForEach( float * buffer, const GroupType & src, size_t offset, size_t step )
    {
        size_t loc = 0;
        MY_FOR_EACH( GroupType, iter, src ) {
            memcpy( buffer + loc + offset, &(iter->val), EachType::sizeInByte );
            loc += step;
        }
    }

};


VertexBufferDX9Imp::VertexBufferDX9Imp( size_t numberOfPosition, const float * positions )
: vertexBufferDX9_( NULL )
{
    if( 0 == numberOfPosition || NULL == positions ) throw exception();

    Pimpl::store_Array< Position >( positions_, positions, numberOfPosition );
}

VertexBufferDX9Imp::~VertexBufferDX9Imp() {
    releaseVertexBufferDX9();
}


size_t VertexBufferDX9Imp::getNumberOfVertex()
{
    return positions_.size();
}

void VertexBufferDX9Imp::appendNormal_Array( float * normals )
{
    Pimpl::store_Array< Normal >( normals_, normals, getNumberOfVertex() );
}

void VertexBufferDX9Imp::appendTexCoord2D_Array( float * texCoords )
{
    TexCoords newTexCoords;
    Pimpl::store_Array< TexCoord2D >( newTexCoords, texCoords, getNumberOfVertex() );
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

unsigned long VertexBufferDX9Imp::getFVF()
{
    unsigned long fvf = D3DFVF_XYZ;

    if( hasNormal() ) fvf |= D3DFVF_NORMAL;

    if( getNumberOfTexCoords() >= 1 ) fvf |= D3DFVF_TEX0;
    if( getNumberOfTexCoords() >= 2 ) fvf |= D3DFVF_TEX1;
    if( getNumberOfTexCoords() >= 3 ) fvf |= D3DFVF_TEX2;
    if( getNumberOfTexCoords() >= 4 ) fvf |= D3DFVF_TEX3;
    if( getNumberOfTexCoords() >= 5 ) fvf |= D3DFVF_TEX4;
    if( getNumberOfTexCoords() >= 6 ) fvf |= D3DFVF_TEX5;
    if( getNumberOfTexCoords() >= 7 ) fvf |= D3DFVF_TEX6;
    if( getNumberOfTexCoords() >= 8 ) fvf |= D3DFVF_TEX7;
    if( getNumberOfTexCoords() >= 9 ) fvf |= D3DFVF_TEX8;

    return fvf;
}

size_t VertexBufferDX9Imp::getSizeInByteForEachVertex()
{
    const unsigned long fvf = getFVF();

    size_t sizeFoREach = 0;

    if( fvf & D3DFVF_XYZ ) sizeFoREach += Position::sizeInByte;

    if( fvf & D3DFVF_NORMAL ) sizeFoREach += Normal::sizeInByte;

    if( fvf & D3DFVF_TEX0 ) sizeFoREach += TexCoord2D::sizeInByte;
    if( fvf & D3DFVF_TEX1 ) sizeFoREach += TexCoord2D::sizeInByte;
    if( fvf & D3DFVF_TEX2 ) sizeFoREach += TexCoord2D::sizeInByte;
    if( fvf & D3DFVF_TEX3 ) sizeFoREach += TexCoord2D::sizeInByte;
    if( fvf & D3DFVF_TEX4 ) sizeFoREach += TexCoord2D::sizeInByte;
    if( fvf & D3DFVF_TEX5 ) sizeFoREach += TexCoord2D::sizeInByte;
    if( fvf & D3DFVF_TEX6 ) sizeFoREach += TexCoord2D::sizeInByte;
    if( fvf & D3DFVF_TEX7 ) sizeFoREach += TexCoord2D::sizeInByte;
    if( fvf & D3DFVF_TEX8 ) sizeFoREach += TexCoord2D::sizeInByte;

    return sizeFoREach;
}

size_t VertexBufferDX9Imp::getSizeInByte()
{
    return getSizeInByteForEachVertex() * getNumberOfVertex();
}

void VertexBufferDX9Imp::setVertexBufferDX9( LPDIRECT3DVERTEXBUFFER9 vertexBufferDX9 )
{
    vertexBufferDX9_ = vertexBufferDX9;
}

LPDIRECT3DVERTEXBUFFER9 VertexBufferDX9Imp::getVertexBufferDX9() {
    return vertexBufferDX9_;
}


void VertexBufferDX9Imp::writeOntoDevice( DWORD lockingFlags )
{
    float * vertices;
    const HRESULT hr = vertexBufferDX9_->Lock( 0, getSizeInByte(), (void**) &vertices, lockingFlags );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"VertexBufferDX9Imp::writeOntoDevice", hr );
        return;
    }

    const size_t offset_position = 0;
    const size_t offset_normal = Position::sizeInByte;
    const size_t offset_tex = offset_normal + Normal::sizeInByte;

    const size_t step = getSizeInByteForEachVertex();
    Pimpl::writeOntoDeviceForEach< Position >( vertices, positions_, offset_position, step );
    Pimpl::writeOntoDeviceForEach< Normal >( vertices, normals_, offset_normal, step );

    size_t offset_tex_each = 0;
    MY_FOR_EACH( TexCoords_Array, iter, texCoords_Array_ ) {
        Pimpl::writeOntoDeviceForEach< TexCoord2D >( vertices, *iter, offset_tex + offset_tex_each, step );
        offset_tex_each += TexCoord2D::sizeInByte;
    }

    vertexBufferDX9_->Unlock();
}

void VertexBufferDX9Imp::releaseVertexBufferDX9()
{
    SAFE_RELEASE( vertexBufferDX9_ );
}


}
