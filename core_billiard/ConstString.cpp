#include "stdafx.h"
namespace my_utility {


    // We can change these implementation to be using external XML file.
wstring ConstString::windowTitle() {
	return L"Billiard";
}

wstring ConstString::effectFilename() {
	return L"asset\\SimpleSample.fx";
}

wstring ConstString::colladaPhysXFilename() {
	return L"asset\\1ball1box.physx.dae";
}

wstring ConstString::colladaVisualAssetFilename() {
	return L"asset\\1ball1box.dae";
}

wstring ConstString::dllDirectoryForColladaDOM() {
    return L"..\\collada_dom\\dll";
}

}

