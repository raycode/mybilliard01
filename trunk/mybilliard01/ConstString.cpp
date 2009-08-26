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

wstring ConstString::colladaPhysXFilename() {
	return L"asset\\1ball1box.physx.dae";
}

wstring ConstString::colladaVisualAssetFilename() {
	return L"asset\\1ball1box.dae";
}

wstring ConstString::dllDirectory() {
    return L"..\\dll";
}

}

