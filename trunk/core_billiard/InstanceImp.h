#pragma once
namespace my_render_imp {


class InstanceImp : IMPLEMENTS_INTERFACE( Instance ) {
public: // from Instance
    virtual wstring getURL() OVERRIDE;
    virtual Base * getResolvedReference() OVERRIDE;

public:
    InstanceImp( InstanceResolver * resolver, wstring url );

private:
    InstanceResolver * resolver_;
    wstring url_;
    Base * resolvedReference_;
};


}
