#include "stdafx.h"
#include "my_collada.h"
namespace core_billiard {


MyColladaLoader::MyColladaLoader( wstring filename )
: filename_( filename )
{
    dae_ = new DAE();
}



}
