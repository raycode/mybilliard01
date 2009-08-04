#include "stdafx.h"
namespace my_collada {


MyColladaLoader::MyColladaLoader( wstring filename )
: filename_( filename )
{
    dae_ = new DAE();
}



}
