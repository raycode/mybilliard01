#pragma once
namespace my_render_imp {


class NodeImp : IMPLEMENTS_ Node {
public: // from Node
    virtual Node * getParent();
    virtual Node * getNextSibling();
    virtual Node * getFirstChild();
    virtual size_t getNbChild();

public:
    void update( float time );
    void render( RenderImp * render ) const;

    NodeImp();

    void updateOrient( float time );
    void updateLocalMatrix();

private: // from Node
    NodeImp * parent_;
    NodeImp * nextSibling_;
    NodeImp * firstChildren_;
    size_t nbChildren_;

private:
    InstanceGeometries instanceGeometries_;

private:
    bool isNeedToUpdate() const;
    bool needToUpdateLocalMatrix_, needToUpdateLocalToWorldMatrix_;
};


}