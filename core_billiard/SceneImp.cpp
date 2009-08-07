#include "my_render_imp.h"
namespace my_render_imp {


void SceneImp::update() {

    if( sceneRoot_ )
        sceneRoot_->update( 0.f );
}

void SceneImp::render( RenderImp * render ) {
    if( NULL == sceneRoot_ )
        return;

    sceneRoot_->render( render );
}

SceneImp::SceneImp( RenderImp * render )
: render_( render )
{
}

bool SceneImp::load( wstring filename ) {
    dae_ = DAEPtr( new DAE() );

    collada_ = dae_->open( convertString< string >( filename ).c_str() );
    if( NULL == collada_ )
        return false;

    loadUpAxis();
    loadLibraryImagesArray();
    loadLibraryEffectsArray();
    loadLibraryMaterialsArray();
    loadLibraryAnimationsArray();
    loadInstanceVisualScene();

    addDefaultLight();
    addDefaultCamera();

    return true;
}

void SceneImp::loadUpAxis() {
    const domAsset::domUp_axis * const upAxis = collada_->getAsset()->getUp_axis();
    if ( upAxis )
        render_->setUpAxis( upAxis->getValue() );
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

}