#pragma once
#include <string>
using namespace std;
namespace core_billiard {

class ConstString {
public:
	static wstring windowTitle();
	static wstring effectFilename();
	static wstring colladaPhysXFilename();
	static wstring colladaVisualAssetFilename();
    static wstring dllDirectoryForColladaDOM();
};

}