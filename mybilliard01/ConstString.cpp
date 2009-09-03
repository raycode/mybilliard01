#include "stdafx.h"
#include "my_app.h"
#include "ConstString.h"
namespace my_utility {
    using namespace std;
    using namespace std::tr1;


    // We can change these implementation to be using external XML file.
wstring ConstString::windowTitle() {
	return L"Billiard";
}

wstring ConstString::effectFilenameByNodeName( wstring nodeName ) {
    static const wstring effectShaderDirectory = L"..\\asset\\shaders\\";
    static const wstring defaultEffectFilename = L"textured phong.fx";

    const wstring effectFilename = effectShaderDirectory + nodeName + L".fx";
    if( FileSystemHelper::isFileExist( effectFilename ) )
        return effectFilename;

    return effectShaderDirectory + defaultEffectFilename;
}

wstring ConstString::shadowMapEffectShaderFilename() {
    return L"../asset/shaders/shadow_map.fx";
}

wstring ConstString::effectFilename_Blur() {
    return L"../asset/shaders/blur.fx";
}

wstring ConstString::effectFilename_HDR() {
    return L"../asset/shaders/hdr.fx";
}

wstring ConstString::effectFilename_SSAO() {
    return L"../asset/shaders/ssao.fx";
}

wstring ConstString::dllDirectory() {
    return L"..\\dll";
}

wstring ConstString::soundFilename_BallStrong( size_t index )
{
    wostringstream filename;
    filename << L"..\\asset\\sound\\ball.strong." << std::setw(2) << std::setfill<wchar_t>('0') << index << L".wav";
    if( false == FileSystemHelper::isFileExist( filename.str() ) ) return L"";
    return filename.str();
}
wstring ConstString::soundFilename_BallWeak( size_t index )
{
    wostringstream filename;
    filename << L"..\\asset\\sound\\ball.weak." << std::setw(2) << std::setfill< wchar_t >('0') << index << L".wav";
    if( false == FileSystemHelper::isFileExist( filename.str() ) ) return L"";
    return filename.str();
}
wstring ConstString::soundFilename_BallBreak( size_t index )
{
    wostringstream filename;
    filename << L"..\\asset\\sound\\break." << std::setw(2) << std::setfill< wchar_t >('0') << index << L".wav";
    if( false == FileSystemHelper::isFileExist( filename.str() ) ) return L"";
    return filename.str();
}
wstring ConstString::soundFilename_Chalk( size_t index )
{
    wostringstream filename;
    filename << L"..\\asset\\sound\\chalk." << std::setw(2) << std::setfill< wchar_t >('0') << index << L".wav";
    if( false == FileSystemHelper::isFileExist( filename.str() ) ) return L"";
    return filename.str();
}
wstring ConstString::soundFilename_Pocket( size_t index )
{
    wostringstream filename;
    filename << L"..\\asset\\sound\\pocket." << std::setw(2) << std::setfill< wchar_t >('0') << index << L".wav";
    if( false == FileSystemHelper::isFileExist( filename.str() ) ) return L"";
    return filename.str();
}
wstring ConstString::soundFilename_CueStrong( size_t index )
{
    wostringstream filename;
    filename << L"..\\asset\\sound\\cue.strong." << std::setw(2) << std::setfill< wchar_t >('0') << index << L".wav";
    if( false == FileSystemHelper::isFileExist( filename.str() ) ) return L"";
    return filename.str();
}
wstring ConstString::soundFilename_CueWeak( size_t index )
{
    wostringstream filename;
    filename << L"..\\asset\\sound\\cue.weak." << std::setw(2) << std::setfill< wchar_t >('0') << index << L".wav";
    if( false == FileSystemHelper::isFileExist( filename.str() ) ) return L"";
    return filename.str();
}
wstring ConstString::soundFilename_BounceOnRail( size_t index )
{
    wostringstream filename;
    filename << L"..\\asset\\sound\\bump." << std::setw(2) << std::setfill< wchar_t >('0') << index << L".wav";
    if( false == FileSystemHelper::isFileExist( filename.str() ) ) return L"";
    return filename.str();
}


}

