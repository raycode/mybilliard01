#include "StdAfx.h"
#include "my_render_imp.h"
namespace my_render_imp {


PixelColor::PixelColor()
{
    pixelColor_ = 0u;
}

PixelColor::PixelColor( NxU32 argb )
{
    setARGB( argb );
}

PixelColor::PixelColor( int a, int r, int g, int b )
{
    setA( (Color256) a );
    setR( (Color256) b );
    setG( (Color256) g );
    setB( (Color256) b );
}

PixelColor::PixelColor( unsigned int a, unsigned int r, unsigned int g, unsigned int b )
{
    setA( (Color256) a );
    setR( (Color256) b );
    setG( (Color256) g );
    setB( (Color256) b );
}

PixelColor::PixelColor( Color256 a, Color256 r, Color256 g, Color256 b )
{
    setA( (Color256) a );
    setR( (Color256) b );
    setG( (Color256) g );
    setB( (Color256) b );
}

PixelColor::operator NxU32 ()
{
    return pixelColor_;
}

NxU32 PixelColor::getARGB() {
    return pixelColor_;
}

void PixelColor::setARGB( NxU32 pixelColor ) {
    pixelColor_ = pixelColor;
}

PixelColor::Color256 PixelColor::getA() {
    return (pixelColor_ >> 24) & 0xff;
}

PixelColor::Color256 PixelColor::getR() {
    return (pixelColor_ >> 16) & 0xff;
}

PixelColor::Color256 PixelColor::getG() {
    return (pixelColor_ >> 8) & 0xff;
}

PixelColor::Color256 PixelColor::getB() {
    return (pixelColor_ >> 0) & 0xff;
}

void PixelColor::setA( Color256 a ) {
    pixelColor_ = ((a & 0xff) << 24) + (pixelColor_ & 0xffffff);
}

void PixelColor::setR( Color256 r ) {
    pixelColor_ = ((r & 0xff) << 16) + (pixelColor_ & 0xff00ffff);
}

void PixelColor::setG( Color256 g ) {
    pixelColor_ = ((g & 0xff) << 8) + (pixelColor_ & 0xffff00ff);
}

void PixelColor::setB( Color256 b ) {
    pixelColor_ = ((b & 0xff) << 0) + (pixelColor_ & 0xffffff00);
}


}
