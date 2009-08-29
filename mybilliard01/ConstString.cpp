#include "my_app.h"
#include "ConstString.h"
namespace my_utility {


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

wstring ConstString::dllDirectory() {
    return L"..\\dll";
}

wstring ConstString::soundFilename_BallBounce() {
    const wstring filename = L"..\\asset\\sound\\ball.strong.01.wav";
    assert( FileSystemHelper::isFileExist( filename ) );
    return filename;
}

}

