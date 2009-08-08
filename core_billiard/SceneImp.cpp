#include "my_render_imp.h"
namespace my_render_imp {


void SceneImp::update() {
    const float timeDelta = updateTimeDelta();
    updateTransformWithPhysics( timeDelta );
    updateCamera( timeDelta );
    updateSceneGraph( timeDelta );
 
    currentScene_->update( timeDelta );
}

void SceneImp::render() {
    currentScene_->render( getRender() );
}

bool SceneImp::load( wstring filename, Factory * factory ) {
    if( NULL == factory ) return false;
    factory_ = factory;

    dae_ = DAEPtr( new DAE() );

    collada_ = dae_->open( convertString< string >( filename ).c_str() );
    if( NULL == collada_ )
        return false;

    initRender();

    loadLibraryImagesArray();
    loadLibraryEffectsArray();
    loadLibraryMaterialsArray();
    loadLibraryAnimationsArray();
    loadLibraryGeometriesArray();
    loadLibraryVisualScenesArray();
    loadLibraryScene();

    addDefaultLight();
    addDefaultCamera();

    return true;
}

SceneImp::SceneImp()
: collada_( NULL ), currentScene_( NULL ), render_( NULL )
{
}

void SceneImp::setRender( Render * render )
{
    render_ = render;

    initRender();
}

bool SceneImp::initRender() {
    if( NULL == collada_ || NULL == render_ ) return false;

    initRenderUpAxis( render_, collada_ );
    // There can be more.
    return true;
}

void SceneImp::initRenderUpAxis( Render * render, domCOLLADA * collada ) {
    const domAsset::domUp_axis * const upAxis = collada->getAsset()->getUp_axis();
    if ( upAxis )
        render->setUpAxis( upAxis->getValue() );
}

wstring SceneImp::getCurrentVisualSceneID() {
    return currentScene_->getID();
}

bool SceneImp::setCurrentVisualScene( wstring sceneID ) {
    Node * const scene = getNode( sceneID );
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
    domLibrary_visual_scenes_Array vscenesArray = collada_->getLibrary_visual_scenes_array();
    for( size_t i = 0; i < vscenesArray.getCount(); ++i ) {
        domLibrary_visual_scenesRef vscenes = vscenesArray[ i ];
        if( NULL == vscenes ) continue;

        domVisual_scene_Array vsceneArray = vscenes->getVisual_scene_array();
        for( size_t j = 0; j < vsceneArray.getCount(); ++j ) {
            domVisual_sceneRef vscene = vsceneArray[ j ];
            if( NULL == vscene ) continue;

            const wstring nodeID = convertString( vscene->getId() );
            Node * const newNode = factory_->createVisualScene( vscene );
            if( NULL == newNode ) continue;

            visualScenes_.insert( VisualScenes::value_type( nodeID, newNode ) );
            appendNodes( newNode );
        }
    }
}

void SceneImp::loadLibraryGeometriesArray() {
    domLibrary_geometries_Array geosArray = collada_->getLibrary_geometries_array();
    for( size_t i = 0; i < geosArray.getCount(); ++i ) {
        domLibrary_geometriesRef geos = geosArray[ i ];
        if( NULL == geos ) continue;

        domGeometry_Array geoArray = geos->getGeometry_array();
        for( size_t j = 0; j < geoArray.getCount(); ++ j ) {
            domGeometryRef geo = geoArray[ j ];
            if( NULL == geo ) continue;

            const wstring geoID = convertString( geo->getId() );
            if( geoID.empty() ) continue;

            Geometry * const newGeo = factory_->createGeometry( geo );
            if( NULL == geo ) continue;

            geometries_.push_back( newGeo );
        }
    }
}

void SceneImp::appendNodes( Node * node ) {
    if( NULL != node->getParent() && false == node->getID().empty() )
        nodes_.insert( Nodes::value_type( node->getID(), node ) );

    if( node->getFirstChild() )
        appendNodes( node->getFirstChild() );
    if( node->getNextSibling() )
        appendNodes( node->getNextSibling() );
}

void SceneImp::loadLibraryScene() {
    domCOLLADA::domSceneRef scene = collada_->getScene();
    if( NULL == scene ) return;

    setCurrentVisualScene( getDefaultVisualSceneID() );

    // TODO: handle instance_physics
}

vector< wstring > SceneImp::getVisualSceneIDs() {
    vector< wstring > rst;
    domLibrary_visual_scenes_Array vscenes = collada_->getLibrary_visual_scenes_array();
    for( size_t i = 0; i < vscenes.getCount(); ++i ) {
        domLibrary_visual_scenes * const vscene = vscenes[ i ];
        if( NULL == vscene ) continue;
        rst.push_back( convertString( vscene->getId() ) );
    }
    return rst;
}

wstring SceneImp::getDefaultVisualSceneID() {
    domInstanceWithExtraRef ivscene = collada_->getScene()->getInstance_visual_scene();
    if( NULL == ivscene ) return L"";

    domVisual_scene * const vscene = daeDowncast< domVisual_scene >( ivscene->getUrl().getElement() );
    if( NULL == vscene ) return L"";

    return convertString( vscene->getId() );
}

Node * SceneImp::getNode( wstring nodeID ) {
    Nodes::const_iterator iter = nodes_.find( nodeID );
    if( iter == nodes_.end() ) return NULL;
    return &*(iter->second);
}

Geometry * SceneImp::getGeometryByID( wstring id ) {
    MY_FOR_EACH( Geometries, iter, geometries_ ) {
        if( id == (*iter)->getID() )
            return &**iter;
    }
    return NULL;
}

Geometry * SceneImp::getGeometryByName( wstring name ) {
    MY_FOR_EACH( Geometries, iter, geometries_ ) {
        if( name == (*iter)->getName() )
            return &**iter;
    }
    return NULL;
}

void SceneImp::addDefaultLight() {
    // TODO
}

void SceneImp::addDefaultCamera() {
    // TODO
}

wstring SceneImp::getFilenameOnly( wstring fullFilename ) {
    const size_t posOfBackslash = fullFilename.find_last_of( '\\' );
    const size_t posOfSlash = fullFilename.find_last_of( '/' );
    const size_t pos = std::max( posOfBackslash, posOfSlash );
    if( 0 == pos )
        return fullFilename;
    return wstring( fullFilename.c_str() + pos +1, fullFilename.c_str() + fullFilename.length() );
}

wstring SceneImp::getPathnameOnly( wstring fullFilename ) {
    const size_t pos = fullFilename.length() - getFilenameOnly( fullFilename ).length();
    return wstring( fullFilename.c_str(), fullFilename.c_str() + pos );
}

float SceneImp::updateTimeDelta() {
    // TODO
    return 0.f;
}

void SceneImp::updateTransformWithPhysics( float timeDelta ) {
    // TODO
}

void SceneImp::updateCamera( float timeDelta ) {
    // TODO
    //InstanceCamera * const instanceCamera = GetActiveInstanceCamera();
    //if( NULL == instanceCamera ) return;

    //const float aspect = (float)(getScreenWidth())/(float)(getScreenHeight());
    // update parent of camera
}

void SceneImp::updateSceneGraph( float timeDelta ) {
    // TODO
}

}