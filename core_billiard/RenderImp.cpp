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

void RenderImp::setUpAxis( domUpAxisType up ) {
    upAxis_ = up;
}

domUpAxisType RenderImp::getUpAxis() {
    return upAxis_;
}

bool RenderImp::openWindow() {
    return false;
}

void RenderImp::closeWindow() {

}

void RenderImp::pushMatrix() {

}

void RenderImp::popMatrix() {

}

void RenderImp::loadIdentity() {

}

void RenderImp::multMatrix( NxMat34 ) {

}

void RenderImp::beginScene() {

}

void RenderImp::endScene() {

}

void RenderImp::clear( int Flags, NxU32 Color, float Z, NxU32 Stencil ) {

}

void RenderImp::Present() {

}

void RenderImp::drawPrimitive(
    EPrimitiveType primitiveType,
    NxU32 startVertex,
    NxU32 primitiveCount )
{
}

void RenderImp::drawIndexedPrimitive(
    EPrimitiveType primitiveType,
    int baseVertexIndex,
    NxU32 minIndex,
    NxU32 numVertices,
    NxU32 startIndex,
    NxU32 primitiveCount )
{

}

void RenderImp::GetRenderState( ERenderStateType State, NxU32 * pValue ) {

}

void RenderImp::SetRenderState( ERenderStateType State, NxU32 Value ) {

}

}
