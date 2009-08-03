#pragma once
#include <string>
using namespace std;
namespace billiard {

class ConstString {
public:
	static wstring windowTitle();
	static wstring effectFilename();
	static wstring colladaPhysXFilename();
	static wstring colladaVisualAssetFilename();
};

}