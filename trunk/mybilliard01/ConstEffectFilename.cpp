#include "StdAfx.h"

using namespace std;
#include "ConstEffectFilename.h"


struct ConstEffectFilename::Pimp {

    static wstring defaultEffectFilename_;

    typedef map< wstring, wstring > EffectFilenames;
    static EffectFilenames effectFilenames_;

    static void init() {
        if( false == effectFilenames_.empty() ) return;

        effectFilenames_.insert( EffectFilenames::value_type( L"CUE_BALL", L"..\\asset\\shaders\\textured pong.fx" ) );
    }
};

wstring ConstEffectFilename::Pimp::defaultEffectFilename_ = L"..\\asset\\SimpleSample.fx";
ConstEffectFilename::Pimp::EffectFilenames ConstEffectFilename::Pimp::effectFilenames_;


wstring ConstEffectFilename::getEffectFilenameByNodeName( wstring nodeName )
{
    Pimp::init();
    Pimp::EffectFilenames::const_iterator iter = Pimp::effectFilenames_.find( nodeName );
    if( iter == Pimp::effectFilenames_.end() ) return Pimp::defaultEffectFilename_;
    return iter->second;
}


