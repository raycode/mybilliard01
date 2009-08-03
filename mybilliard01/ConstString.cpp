#include "stdafx.h"
#include "ConstString.h"
namespace billiard {

wstring ConstString::windowTitle() {
	return L"Billiard";
}

wstring ConstString::effectFilename() {
	return L"..\\asset\\SimpleSample.fx";
}

wstring colladaPhysXFilename() {
	return L"..\\asset\\billiard01.physx.dae";
}

wstring colladaVisualAssetFilename() {
	return L"..\\asset\\billiard01.dae";
}


}

