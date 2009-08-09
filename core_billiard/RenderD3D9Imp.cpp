#include "stdafx.h"
#include "my_render_d3d9_imp.h"
namespace my_render_d3d9_imp {


void RenderD3D9Imp::setScreenWidth( int width ) {
    width_ = width;
}

void RenderD3D9Imp::setScreenHeight( int height ) {
    height_ = height;
}

int RenderD3D9Imp::getScreenWidth() {
    return width_;
}

int RenderD3D9Imp::getScreenHeight() {
    return height_;
}

void RenderD3D9Imp::setUpAxis( domUpAxisType up ) {
    upAxis_ = up;
}

domUpAxisType RenderD3D9Imp::getUpAxis() {
    return upAxis_;
}

bool RenderD3D9Imp::openWindow() {
    return false;
}

void RenderD3D9Imp::closeWindow() {

}

void RenderD3D9Imp::pushMatrix() {

}

void RenderD3D9Imp::popMatrix() {

}

void RenderD3D9Imp::loadIdentity() {

}

void RenderD3D9Imp::multMatrix( NxMat34 ) {

}

void RenderD3D9Imp::beginScene() {

}

void RenderD3D9Imp::endScene() {

}

void RenderD3D9Imp::clear( int Flags, NxU32 Color, float Z, NxU32 Stencil ) {

}

void RenderD3D9Imp::Present() {

}

void RenderD3D9Imp::drawPrimitive(
    EPrimitiveType primitiveType,
    NxU32 startVertex,
    NxU32 primitiveCount )
{
}

void RenderD3D9Imp::drawIndexedPrimitive(
    EPrimitiveType primitiveType,
    int baseVertexIndex,
    NxU32 minIndex,
    NxU32 numVertices,
    NxU32 startIndex,
    NxU32 primitiveCount )
{

}

void RenderD3D9Imp::GetRenderState( ERenderStateType State, NxU32 * pValue ) {

}

void RenderD3D9Imp::SetRenderState( ERenderStateType State, NxU32 Value ) {

}

}
