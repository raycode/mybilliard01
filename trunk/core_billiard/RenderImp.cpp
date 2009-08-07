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

void RenderImp::pushMatrix() {

}

void RenderImp::popMatrix() {

}


}
