#include "stdafx.h"
namespace my_collada {


MyColladaLoader::MyColladaLoader( wstring filename )
: filename_( filename ), dae_( new DAE() )
{
    collada_ = dae_->open( convertString< string >( filename ).c_str() );
    if( NULL == collada_ )
        throw exception();
}

domCOLLADA * MyColladaLoader::getCOLLADA() {
    return collada_;
}

DAE * MyColladaLoader::getDAE() {
    return &(*dae_);
}

daeElement * MyColladaLoader::idLookup( wstring id )
{
    return getDAE()->getDatabase()->idLookup( convertString< string >( id ), getCOLLADA()->getDocument() );
}

domVisual_scene * MyColladaLoader::getInstancedVisualScene()
{
    domCOLLADA::domScene * const scene = getCOLLADA()->getScene();
    domInstanceWithExtraRef instance_visual_scene = scene->getInstance_visual_scene();
    const xsAnyURI url = instance_visual_scene->getUrl();

    domVisual_scene * const visual_scene = daeDowncast< domVisual_scene >( url.getElement() );
    return visual_scene;
}

vector< domMesh * > MyColladaLoader::getMeshByNodeID( wstring nodeId )
{
    domNode * const node = daeDowncast< domNode >( idLookup( nodeId ) );
    domInstance_geometry_Array instance_geometries = node->getInstance_geometry_array();

    vector< domMesh * > rst;
    for( size_t i = 0; i < instance_geometries.getCount(); ++i ) {
        domGeometry * const geometry = daeDowncast< domGeometry >( instance_geometries[ i ]->getUrl().getElement() );
        rst.push_back( &(*geometry->getMesh()) );
    }
    return rst;
}


}
