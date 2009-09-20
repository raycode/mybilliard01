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

wstring ConstString::name_CueBall() {
    return L"CUE_BALL";
}

wstring ConstString::name_Rack() {
    return L"rack01";
}

wstring ConstString::name_Ball_prefix() {
    return L"ball";
}

wstring ConstString::name_Pocket_prefix() {
    return L"pocket";
}

wstring ConstString::name_Rail_prefix() {
    return L"rail";
}

wstring ConstString::name_CueStick() {
    return L"cue_stick";
}

wstring ConstString::name_Background() {
    return L"background";
}

wstring ConstString::effectFilenameByNodeName( wstring nodeName ) {
    static const wstring effectShaderDirectory = L"..\\asset\\shaders\\";
    static const wstring defaultEffectFilename = L"textured phong.fx";

    const wstring effectFilename = effectShaderDirectory + nodeName + L".fx";
    if( FileSystemHelper::isFileExist( effectFilename ) )
        return effectFilename;

    return effectShaderDirectory + defaultEffectFilename;
}

wstring ConstString::effectFilename_shadowMap( size_t index ) {
    wstringstream filename;
    filename << L"../asset/shaders/shadow_map" << std::setw(2) << std::setfill<wchar_t>( '0' ) << index << L".fx";
    return filename.str();
}

wstring ConstString::effectFilename_depthCull() {
    return L"../asset/shaders/depth_cull.fx";
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

const wchar_t * ConstString::dllDirectory() {
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

