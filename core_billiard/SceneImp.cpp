#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


SceneImp::SceneImp()
    : collada_( NULL )
    , currentCamera_( NULL )
{
    dae_ = DAEPtr( new DAE() );
    colladaFactory_ = & defaultFactory_;
    renderFactory_ = & nullRenderFactory_;
    currentScene_ = & nullNode_;
}


void SceneImp::update( float elapsedTime ) {
    currentScene_->update( elapsedTime );
}

void SceneImp::display( Render * render ) {
    currentScene_->display( render );
}

void SceneImp::setColladaFactoryBeforeLoad( ColladaFactory * factory ) {
    colladaFactory_ = ( ( NULL == factory ) ? & defaultFactory_ : factory );
}

void SceneImp::setRenderFactory( RenderBufferFactory * renderFactory ) {
    renderFactory_ = (( NULL == renderFactory ) ? &nullRenderFactory_ : renderFactory );
    updateDevice();
}

void SceneImp::unload() {
    dae_ = DAEPtr( new DAE() );
    visualScenes_.clear();
    nodes_.clear();
    geometries_.clear();
}

bool SceneImp::load( wstring filename ) {
    unload();

    string szFilename = convertString< string >( filename );
    collada_ = dae_->open( szFilename.c_str() );
    if( NULL == collada_ ) return false;

    storeFilename( filename );

    loadUpAxis( collada_ );
    loadLibraryImagesArray();
    loadLibraryEffectsArray();
    loadLibraryMaterialsArray();
    loadLibraryAnimationsArray();
    loadLibraryGeometriesArray();
    loadLibraryVisualScenesArray();
    loadLibraryScene();
    setDefaultsAfterLoad();

    updateDevice();
    return true;
}

void SceneImp::updateDevice() {
    MY_FOR_EACH( Geometries, geo, geometries_ ) {
        GeometryMesh * const mesh = (*geo)->getMesh();
        const size_t numPrim = mesh->getNumberOfPrimitives();
        for( size_t i = 0; i < numPrim; ++i ) {
            GeometryMeshPrimitive * const prim = mesh->getPrimitive( i );
            prim->buildDeviceBuffer( renderFactory_ );
        }
    }
}

void SceneImp::setDefaultsAfterLoad() {
    setCurrentVisualScene( getDefaultVisualSceneID() );
}

void SceneImp::storeFilename( wstring filename ) {
    filename_ = getFilenameOnly( filename );
    pathname_ = getPathnameOnly( filename );
}

bool SceneImp::loadUpAxis( domCOLLADA * collada ) {
    if( NULL == collada ) return false;
    if( NULL == collada->getAsset() ) return false;
    const domAsset::domUp_axis * const upAxis = collada->getAsset()->getUp_axis();
    if( NULL == upAxis ) return false;

    upAxis_ = upAxis->getValue();
    return true;
}

wstring SceneImp::getCurrentVisualSceneID() {
    return currentScene_->getID();
}

bool SceneImp::setCurrentVisualScene( wstring sceneID ) {
    Node * const scene = getVisualScene( sceneID );
    if( NULL == scene ) return false;

    currentScene_ = scene;
    return true;
}

daeElement * SceneImp::idLookup( wstring id )
{
    return dae_->getDatabase()->idLookup( convertString( id ), collada_->getDocument() );
}

void SceneImp::loadLibraryImagesArray() {
    // TODO
}

void SceneImp::loadLibraryEffectsArray() {
    // TODO
}

void SceneImp::loadLibraryMaterialsArray() {
    // TODO
}

void SceneImp::loadLibraryAnimationsArray() {
    // TODO
}

void SceneImp::loadLibraryVisualScenesArray() {
    MY_FOR_EACH_COLLADA( domLibrary_visual_scenes, vscenes, collada_->getLibrary_visual_scenes_array() ) {
        MY_FOR_EACH_COLLADA( domVisual_scene, vscene, (*vscenes)->getVisual_scene_array() ) {

            const wstring newNodeID = convertString( (*vscene)->getId() );
            if( newNodeID.empty() ) continue;

            Node * const newVisualScene = colladaFactory_->createVisualScene( *vscene );
            if( NULL == newVisualScene ) continue;

            visualScenes_.insert( VisualScenes::value_type( newNodeID, newVisualScene ) );
            loadNodesFromVisualScene( newVisualScene );
        }
    }
}

void SceneImp::loadLibraryGeometriesArray() {
    MY_FOR_EACH_COLLADA( domLibrary_geometries, geoes, collada_->getLibrary_geometries_array() ) {
        MY_FOR_EACH_COLLADA( domGeometry, geo, (*geoes)->getGeometry_array() ) {

            const wstring newGeoID = convertString( (*geo)->getId() );
            if( newGeoID.empty() ) continue;

            Geometry * const newGeo = colladaFactory_->createGeometry( *geo );
            if( NULL == newGeo ) continue;

            geometries_.push_back( newGeo );
        }
    }
}

void SceneImp::loadNodesFromVisualScene( Node * node ) {
    if( NULL == node ) return;
    if( node->hasParent() && false == node->getID().empty() )
        nodes_.insert( Nodes::value_type( node->getID(), node ) );

    if( node->hasFirstChild() )
        loadNodesFromVisualScene( node->getFirstChild() );
    if( node->hasNextSibling() )
        loadNodesFromVisualScene( node->getNextSibling() );
}

void SceneImp::loadLibraryScene() {
    domCOLLADA::domSceneRef scene = collada_->getScene();
    if( NULL == scene ) return;

    setCurrentVisualScene( getDefaultVisualSceneID() );
}

vector< wstring > SceneImp::getVisualSceneIDs() {
    vector< wstring > visualSceneIDs;
    MY_FOR_EACH_COLLADA( domLibrary_visual_scenes, vscenes, collada_->getLibrary_visual_scenes_array() ) {
        MY_FOR_EACH_COLLADA( domVisual_scene, vscene, (*vscenes)->getVisual_scene_array() ) {
            visualSceneIDs.push_back( convertString( (*vscene)->getId() ) );
        }
    }
    return visualSceneIDs;
}

bool SceneImp::hasDefaultVisualSceneID() {
    if( NULL == collada_ ) return false;
    if( NULL == collada_->getScene() ) return false;
    if( NULL == collada_->getScene()->getInstance_visual_scene() ) return false;
    return true;
}

wstring SceneImp::getDefaultVisualSceneID() {
    if( false == hasDefaultVisualSceneID() ) return L"";

    domInstanceWithExtraRef ivscene = collada_->getScene()->getInstance_visual_scene();
    domVisual_scene * const vscene = daeDowncast< domVisual_scene >( ivscene->getUrl().getElement() );
    if( NULL == vscene ) return L"";

    return convertString( vscene->getId() );
}

Node * SceneImp::getNode( wstring nodeID ) {
    Nodes::const_iterator iter = nodes_.find( nodeID );
    if( iter == nodes_.end() ) return NULL;
    return iter->second;
}

Node * SceneImp::getVisualScene( wstring id ) {
    Nodes::const_iterator iter = visualScenes_.find( id );
    if( iter == visualScenes_.end() ) return NULL;
    return iter->second;
}

Geometry * SceneImp::getGeometryByID( wstring id ) {
    MY_FOR_EACH( Geometries, iter, geometries_ )
        if( id == (*iter)->getID() ) return *iter;
    return NULL;
}

Geometry * SceneImp::getGeometryByName( wstring name ) {
    MY_FOR_EACH( Geometries, iter, geometries_ )
        if( name == (*iter)->getName() ) return &**iter;
    return NULL;
}

wstring SceneImp::getFilenameOnly( wstring fullFilename ) {
    const size_t posOfBackslash = fullFilename.find_last_of( '\\' );
    const bool bFoundBackslash = (wstring::npos != posOfBackslash);

    const size_t posOfSlash = fullFilename.find_last_of( '/' );
    const bool bFoundSlash = (wstring::npos != posOfSlash);

    if( false == bFoundBackslash && false == bFoundSlash )
        return fullFilename;

    size_t pos = 0;
    if( bFoundSlash && bFoundBackslash )
        pos = std::max( posOfBackslash, posOfSlash );
    else if( bFoundSlash )
        pos = posOfSlash;
    else pos = posOfBackslash;

    return wstring( fullFilename.c_str() + pos +1, fullFilename.c_str() + fullFilename.length() );
}

wstring SceneImp::getPathnameOnly( wstring fullFilename ) {
    const size_t pos = fullFilename.length() - getFilenameOnly( fullFilename ).length();
    return wstring( fullFilename.c_str(), fullFilename.c_str() + std::max( pos, 1u ) -1u );
}


}