#pragma once
namespace my_render_imp {


class PixelColor {
public: 
    typedef unsigned char Color256;

public:
    NxU32 getARGB();
    void setARGB( NxU32 );

    Color256 getA();
    Color256 getR();
    Color256 getG();
    Color256 getB();

    void setA( Color256 );
    void setR( Color256 );
    void setG( Color256 );
    void setB( Color256 );

public:
    PixelColor();
    explicit PixelColor( NxU32 argb );
    explicit PixelColor( Color256 a, Color256 r, Color256 g, Color256 b );
    explicit PixelColor( int a, int r, int g, int b );
    explicit PixelColor( unsigned int a, unsigned int r, unsigned int g, unsigned int b );
    explicit PixelColor( float a, NxVec3 rgb );
    explicit PixelColor( float a, float r, float g, float b );

public:
    operator NxU32 ();

private:
    NxU32 pixelColor_;

private:
    Color256 clamp_from0_to255( int );
    Color256 clamp_from0_to255( unsigned int );
};


}
