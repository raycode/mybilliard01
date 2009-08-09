#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


GeometryMeshInput::GeometryMeshInput( domInputLocalOffset_Array inputs )
: inputs_( inputs )
, positions_( NULL )
, normals_( NULL )
, binormals_( NULL )
, tangents_( NULL )
, colors_( NULL )
{
    // inputs with offsets
    for( size_t i = 0; i < inputs.getCount(); ++i )
    {
        domInputLocalOffsetRef input = inputs[ i ];
        if( NULL == input ) continue;

        domSource * const source = getSource( input );
        if( NULL == source ) continue;

        const int offset  = (size_t) input->getOffset();
        const wstring semantic = convertString( input->getSemantic() );
        domListOfFloats data = source->getFloat_array()->getValue();

        if( semantic == L"VERTEX" ) {
            position_offset_ = offset;
            positions_ = & data;

        } else if( semantic == L"NORMAL" ) {
            normal_offset_ = offset;
            normals_ = & data;

        } else if( semantic == L"BINORMAL" ) {
            binormal_offset_ = offset;
            binormals_ = & data;

        } else if( semantic == L"TANGENT" ) {
            tangent_offset_ = offset;
            tangents_ = & data;

        } else if( semantic == L"COLOR" ) {
            color_offset_ = offset;
            colors_ = & data;

        } else if( semantic == L"TEXCOORD" ) {
            texture_offset_Array_.push_back( offset );
            textures_Array_.push_back( & data );
        }
    }
}

domSource * GeometryMeshInput::getSource( domInputLocalOffsetRef input )
{
    const wstring semantic = convertString( input->getSemantic() );

    domElement * candidate = input->getSource().getElement();
    if( NULL == candidate ) return NULL;

    if( candidate->typeID() == domVertices::ID() ) {
        domVertices * const vertice = daeDowncast< domVertices >( candidate );
        candidate = vertice->getInput_array()[0]->getSource().getElement();
    }

    return daeDowncast< domSource >( candidate );
}

void GeometryMeshInput::setIndexies( domListOfUInts indexies ) {
    indexies_ = indexies;
    currentPosition_ = 0;
}

size_t GeometryMeshInput::getMaxOffset() {
    int max_offset = max( max( max( max(
        position_offset_,
        normal_offset_ ),
        binormal_offset_ ),
        tangent_offset_ ),
        color_offset_ );

    MY_FOR_EACH( vector< int >, iter, texture_offset_Array_ ) {
        max_offset = std::max( max_offset, *iter );
    }

    return (size_t) max_offset;
}

bool GeometryMeshInput::hasNext() {
    const size_t totalNumValues = indexies_.getCount();
    const size_t totalNumOffsets = getMaxOffset() + 1;
    const size_t nextPosition = currentPosition_ + totalNumOffsets;
    return totalNumValues >= nextPosition + totalNumOffsets;
}

void GeometryMeshInput::getNext() {
    const size_t totalNumOffsets = getMaxOffset() + 1;
    currentPosition_ = currentPosition_ + totalNumOffsets;
}

bool GeometryMeshInput::hasNormal() {
    return NULL != normals_;
}

bool GeometryMeshInput::hasBinormal() {
    return NULL != binormals_;
}

bool GeometryMeshInput::hasTangent() {
    return NULL != tangents_;
}

bool GeometryMeshInput::hasColor() {
    return NULL != colors_;
}

size_t GeometryMeshInput::getCurrentIndex( size_t offset ) {
    return (size_t) indexies_[ currentPosition_ + offset ];
}

NxVec3 GeometryMeshInput::getVertex() {
    domFloat * const ptr = &((*positions_)[ getCurrentIndex( position_offset_ ) * 3 ]);
    return NxVec3( (NxReal) *ptr, (NxReal) *(ptr+1), (NxReal) *(ptr+2) );
}

NxVec3 GeometryMeshInput::getNormal() {
    domFloat * const ptr = &((*normals_)[ getCurrentIndex( normal_offset_ ) * 3 ]);
    return NxVec3( (NxReal) *ptr, (NxReal) *(ptr+1), (NxReal) *(ptr+2) );
}

GeometryMeshPrimitiveImp::Tex2D GeometryMeshInput::getTexCoord( size_t index ) {
    domFloat * const ptr = &((*(textures_Array_[ index ]))[ getCurrentIndex( texture_offset_Array_[ index ] ) * 2 ] ) ;
    GeometryMeshPrimitiveImp::Tex2D uv;
    uv.u = (NxReal) (*ptr);
    uv.v = (NxReal) (*(ptr+1));
    return uv;
}

size_t GeometryMeshInput::getNumTexture() {
    return textures_Array_.size();
}

NxVec3 GeometryMeshInput::getBinormal() {
    domFloat * const ptr = &((*binormals_)[ getCurrentIndex( binormal_offset_ ) * 3 ]);
    return NxVec3( (NxReal) *ptr, (NxReal) *(ptr+1), (NxReal) *(ptr+2) );
}

NxVec3 GeometryMeshInput::getTangent() {
    domFloat * const ptr = &((*tangents_)[ getCurrentIndex( tangent_offset_ ) * 3 ]);
    return NxVec3( (NxReal) *ptr, (NxReal) *(ptr+1), (NxReal) *(ptr+2) );
}

NxVec3 GeometryMeshInput::getColor() {
    domFloat * const ptr = &((*colors_)[ getCurrentIndex( color_offset_ ) * 3 ]);
    return NxVec3( (NxReal) *ptr, (NxReal) *(ptr+1), (NxReal) *(ptr+2) );
}


}
