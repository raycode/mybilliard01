#include "StdAfx.h"
#include "my_app.h"


struct ConstEffectFilename::Pimp {

    static const wstring defaultEffectFilename_;

};

const wstring ConstEffectFilename::Pimp::defaultEffectFilename_ = L"..\\asset\\shaders\\textured phong.fx";
ConstEffectFilename::Pimp::EffectFilenames ConstEffectFilename::Pimp::effectFilenames_;


wstring ConstEffectFilename::getEffectFilenameByNodeName( wstring nodeName )
{
    Pimp::init();
    Pimp::EffectFilenames::const_iterator iter = Pimp::effectFilenames_.find( nodeName );
    if( iter == Pimp::effectFilenames_.end() ) return Pimp::defaultEffectFilename_;
    return iter->second;
}


