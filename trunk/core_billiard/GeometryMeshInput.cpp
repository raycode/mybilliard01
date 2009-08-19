#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


GeometryMeshInput::GeometryMeshInput( domInputLocalOffset_Array inputs )
{
    MY_FOR_EACH_COLLADA( domInputLocalOffset, input, inputs ) {

        domSourceRef const source = getSourceFromInput( *input );
        if( NULL == source ) continue;

        const wstring semantic = convertString( (*input)->getSemantic() );
        const int offset  = (size_t) (*input)->getOffset();
        const int set = (size_t) (*input)->getSet();
        domListOfFloats data = source->getFloat_array()->getValue();

        if( semantic == L"VERTEX" ) {
            storeEachSemantic( ETYPE_POSITION, offset, set, data );

        } else if( semantic == L"NORMAL" ) {
            storeEachSemantic( ETYPE_NORMAL, offset, set, data );

        } else if( semantic == L"BINORMAL" ) {
            storeEachSemantic( ETYPE_BINORMAL, offset, set, data );

        } else if( semantic == L"TANGENT" ) {
            storeEachSemantic( ETYPE_TANGENT, offset, set, data );

        } else if( semantic == L"COLOR" ) {
            storeEachSemantic( ETYPE_COLOR, offset, set, data );

        } else if( semantic == L"TEXCOORD" ) {
            storeEachSemantic( ETYPE_TEXCOORD, offset, set, data );
        }
    }
}

void GeometryMeshInput::storeEachSemantic( ESEMANTIC_TYPE semantic, size_t offset, size_t set, const domListOfFloats & data )
{
    offset_array_[ semantic ].resize( std::max( set +1, offset_array_[ semantic ].size() ) );
    source_array_[ semantic ].resize( std::max( set +1, source_array_[ semantic ].size() ) );
    offset_array_[ semantic ][ set ] = offset;
    source_array_[ semantic ][ set ] = data;
}

domSourceRef GeometryMeshInput::getSourceFromInput( domInputLocalOffsetRef input )
{
    daeElementRef candidate = input->getSource().getElement();
    if( NULL == candidate ) return NULL;

    if( candidate->typeID() == domVertices::ID() ) {
        domVerticesRef const vertice = daeDowncast< domVertices >( candidate );
        candidate = vertice->getInput_array()[0]->getSource().getElement();
    }

    return daeDowncast< domSource >( candidate );
}

void GeometryMeshInput::setNewIndices( const domListOfUInts & indexies ) {
    indices = indexies;
    currentPosition_ = 0;
}

size_t GeometryMeshInput::getStepOfOffset() {
    size_t sumOfOffset = 0;
    for( size_t i = 0; i < SIZE_OF_ETYPE; ++i ) {
        sumOfOffset += offset_array_[ i ].size();
    }
    return sumOfOffset;
}

bool GeometryMeshInput::hasVertex() {
    const size_t totalNumValues = indices.getCount();
    const size_t endOfPosition = currentPosition_ + getStepOfOffset();
    return totalNumValues >= endOfPosition;
}

void GeometryMeshInput::moveToNextVertex() {
    currentPosition_ = currentPosition_ + getStepOfOffset();
}

size_t GeometryMeshInput::getNumberOfNormalSet() {
    return source_array_[ ETYPE_NORMAL ].size();
}
size_t GeometryMeshInput::getNumberOfBiNormalSet() {
    return source_array_[ ETYPE_BINORMAL ].size();
}
size_t GeometryMeshInput::getNumberOfTangentSet() {
    return source_array_[ ETYPE_TANGENT ].size();
}
size_t GeometryMeshInput::getNumberOfColorSet() {
    return source_array_[ ETYPE_COLOR ].size();
}
size_t GeometryMeshInput::getNumberOfTexCoord2DSet() {
    return source_array_[ ETYPE_TEXCOORD ].size();
}

size_t GeometryMeshInput::getCurrentIndex( ESEMANTIC_TYPE semanticType, size_t whichSet ) {
    return (size_t) indices[ currentPosition_ + offset_array_[ semanticType ][ whichSet ] ];
}

domFloat * GeometryMeshInput::getCurrentSource( ESEMANTIC_TYPE semanticType, size_t whichSet, size_t numberOfUnit ) {
    return &(source_array_[ semanticType ][ whichSet ][ getCurrentIndex( semanticType, whichSet ) * numberOfUnit ]);
}

NxVec3 GeometryMeshInput::getVertex() {
    const size_t whichSet = 0;
    domFloat * const src = getCurrentSource( ETYPE_POSITION, whichSet, 3 );
    return NxVec3( (NxReal) *src, (NxReal) *(src+1), (NxReal) *(src+2) );
}

NxVec3 GeometryMeshInput::getNormal( size_t whichSet ) {
    domFloat * const src = getCurrentSource( ETYPE_NORMAL, whichSet, 3 );
    return NxVec3( (NxReal) *src, (NxReal) *(src+1), (NxReal) *(src+2) );
}

NxVec3 GeometryMeshInput::getBinormal( size_t whichSet ) {
    domFloat * const src = getCurrentSource( ETYPE_BINORMAL, whichSet, 3 );
    return NxVec3( (NxReal) *src, (NxReal) *(src+1), (NxReal) *(src+2) );
}

NxVec3 GeometryMeshInput::getTangent( size_t whichSet ) {
    domFloat * const src = getCurrentSource( ETYPE_TANGENT, whichSet, 3 );
    return NxVec3( (NxReal) *src, (NxReal) *(src+1), (NxReal) *(src+2) );
}

NxVec3 GeometryMeshInput::getColor( size_t whichSet ) {
    domFloat * const src = getCurrentSource( ETYPE_COLOR, whichSet, 3 );
    return NxVec3( (NxReal) *src, (NxReal) *(src+1), (NxReal) *(src+2) );
}

NxReal GeometryMeshInput::getTexCoord2D_U( size_t whichSet ) {
    domFloat * const src = getCurrentSource( ETYPE_TEXCOORD, whichSet, 2 );
    return (NxReal) (*src);
}

NxReal GeometryMeshInput::getTexCoord2D_V( size_t whichSet ) {
    domFloat * const src = getCurrentSource( ETYPE_TEXCOORD, whichSet, 2 );
    return (NxReal) (*(src+1));
}

}
