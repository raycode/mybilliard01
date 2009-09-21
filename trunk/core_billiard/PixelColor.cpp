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

PixelColor::PixelColor( float a, NxVec3 rgb )
{
    setA( clamp_from0_to255( (int)( a * 255 ) ) );
    setR( clamp_from0_to255( (int)( rgb.x * 255 ) ) );
    setG( clamp_from0_to255( (int)( rgb.y * 255 ) ) );
    setB( clamp_from0_to255( (int)( rgb.z * 255 ) ) );
}

PixelColor::PixelColor( float a, float r, float g, float b )
{
    setA( clamp_from0_to255( (int)( a * 255 ) ) );
    setR( clamp_from0_to255( (int)( r * 255 ) ) );
    setG( clamp_from0_to255( (int)( g * 255 ) ) );
    setB( clamp_from0_to255( (int)( b * 255 ) ) );
}

PixelColor::PixelColor( int a, int r, int g, int b )
{
    setA( clamp_from0_to255( a ) );
    setR( clamp_from0_to255( r ) );
    setG( clamp_from0_to255( g ) );
    setB( clamp_from0_to255( b ) );
}

PixelColor::PixelColor( unsigned int a, unsigned int r, unsigned int g, unsigned int b )
{
    setA( clamp_from0_to255( a ) );
    setR( clamp_from0_to255( r ) );
    setG( clamp_from0_to255( g ) );
    setB( clamp_from0_to255( b ) );
}

PixelColor::PixelColor( Color256 a, Color256 r, Color256 g, Color256 b )
{
    setA( a );
    setR( r );
    setG( g );
    setB( b );
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


PixelColor::Color256 PixelColor::clamp_from0_to255( int val ) {
    if( val > 255 ) return (Color256) 255;
    if( val < 0 ) return (Color256) 0;
    return (Color256) val;
}

PixelColor::Color256 PixelColor::clamp_from0_to255( unsigned int val ) {
    if( val > 255 ) return (Color256) 255;
    return (Color256) val;
}


}
