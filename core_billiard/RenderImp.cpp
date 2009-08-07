#include "my_render_imp.h"
namespace my_render_imp {

void RenderImp::setScreenWidth( int width ) {
    width_ = width;
}

void RenderImp::setScreenHeight( int height ) {
    height_ = height;
}

int RenderImp::getScreenWidth() {
    return width_;
}

int RenderImp::getScreenHeight() {
    return height_;
}

wstring RenderImp::getFilenameOnly( wstring fullFilename ) {
    const size_t posOfBackslash = fullFilename.find_last_of( '\\' );
    const size_t posOfSlash = fullFilename.find_last_of( '/' );
    const size_t pos = std::max( posOfBackslash, posOfSlash );
    if( 0 == pos )
        return fullFilename;
    return wstring( fullFilename.c_str() + pos +1, fullFilename.c_str() + fullFilename.length() );
}

wstring RenderImp::getPathnameOnly( wstring fullFilename ) {
    const size_t pos = fullFilename.length() - getFilenameOnly( fullFilename ).length();
    return wstring( fullFilename.c_str(), fullFilename.c_str() + pos );
}

bool RenderImp::load( wstring filename ) {
    filename_ = getFilenameOnly( filename );
    pathname_ = getPathnameOnly( filename );
    scene_ = SceneImpPtr( new SceneImp( this ) );
    return scene_->load( filename );
}

void RenderImp::setUpAxis( domUpAxisType up ) {
    upAxis_ = up;
}

domUpAxisType RenderImp::getUpAxis() {
    return upAxis_;
}

bool RenderImp::render() {
    if( NULL == getScene() ) return false;

    updateCamera();
    updateSceneGraph();

    scene_->render( this );

    return true;
}

void RenderImp::updateCamera() {
    //InstanceCamera * const instanceCamera = GetActiveInstanceCamera();
    //if( NULL == instanceCamera ) return;

    //const float aspect = (float)(getScreenWidth())/(float)(getScreenHeight());
    // update parent of camera
}

void RenderImp::updateSceneGraph() {
    scene_->update(); 


}


Scene * RenderImp::getScene() {
    return &*scene_;
}

RenderImp::MatrixStackPtr RenderImp::createMatrix() {
    return MatrixStackPtr(new MatrixStackImp( this ));
}

RenderImp::MatrixStackImp::MatrixStackImp( RenderImp * render )
: render_( render )
{
    render_->pushMatrix();
}

RenderImp::MatrixStackImp::~MatrixStackImp()
{
    render_->popMatrix();
}

void RenderImp::pushMatrix() {

}

void RenderImp::popMatrix() {

}


}
