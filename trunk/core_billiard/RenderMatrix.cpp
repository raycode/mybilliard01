#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {

RenderMatrix::RenderMatrix( Render * render )
: render_( render )
{
    render_->pushMatrix();
    render_->loadIdentity();
}

RenderMatrix::~RenderMatrix() {
    render_->popMatrix();
}

void RenderMatrix::mult( NxMat34 rhs ) {
    render_->multMatrix( rhs );
}

}