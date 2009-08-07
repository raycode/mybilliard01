#include "my_render_imp.h"
namespace my_render_imp {


void SceneImp::update() {
    const float timeDelta = calculateTimeDelta();

    updateTransformWithPhysics( timeDelta );
    updateCamera( timeDelta );
    updateSceneGraph( timeDelta );
 
    sceneRoot_->update( timeDelta );
}

void SceneImp::render() {
    sceneRoot_->render( getRender() );
}

bool SceneImp::load( wstring filename ) {
    dae_ = DAEPtr( new DAE() );

    collada_ = dae_->open( convertString< string >( filename ).c_str() );
    if( NULL == collada_ )
        return false;

    loadLibraryImagesArray();
    loadLibraryEffectsArray();
    loadLibraryMaterialsArray();
    loadLibraryAnimationsArray();
    loadInstanceVisualScene();

    addDefaultLight();
    addDefaultCamera();

    return true;
}

void SceneImp::setRender( Render * render )
{
    render_ = render;
    setRenderUpAxis( render );
}

void SceneImp::setRenderUpAxis( Render * render ) {
    const domAsset::domUp_axis * const upAxis = collada_->getAsset()->getUp_axis();
    if ( upAxis )
        render->setUpAxis( upAxis->getValue() );
}

void SceneImp::loadLibraryImagesArray() {

}

void SceneImp::loadLibraryEffectsArray() {

}

void SceneImp::loadLibraryMaterialsArray() {

}

void SceneImp::loadLibraryAnimationsArray() {

}

void SceneImp::loadInstanceVisualScene() {

}

void SceneImp::addDefaultLight() {

}

void SceneImp::addDefaultCamera() {

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

float SceneImp::calculateTimeDelta() {
    return 0.f;
}

void SceneImp::updateTransformWithPhysics( float timeDelta ) {

}

void SceneImp::updateCamera( float timeDelta ) {
    //InstanceCamera * const instanceCamera = GetActiveInstanceCamera();
    //if( NULL == instanceCamera ) return;

    //const float aspect = (float)(getScreenWidth())/(float)(getScreenHeight());
    // update parent of camera
}

void SceneImp::updateSceneGraph( float timeDelta ) {

}

}