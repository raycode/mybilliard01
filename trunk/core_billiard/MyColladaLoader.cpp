#include "stdafx.h"
namespace my_collada {


MyColladaLoader::MyColladaLoader( wstring filename )
: filename_( filename ), dae_( new DAE() )
{
    collada_ = dae_->open( convertString< string >( filename ).c_str() );
    if( NULL == collada_ )
        throw exception();
}

domCOLLADA * MyColladaLoader::getCOLLADA() {
    return collada_;
}

DAE * MyColladaLoader::getDAE() {
    return &(*dae_);
}

daeElement * MyColladaLoader::idLookup( wstring id )
{
    return getDAE()->getDatabase()->idLookup( convertString< string >( id ), getCOLLADA()->getDocument() );
}


}
