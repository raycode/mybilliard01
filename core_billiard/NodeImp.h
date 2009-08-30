#pragma once
namespace my_render_imp {


class NodeImp : public BaseImp, IMPLEMENTS_INTERFACE( Node ) {
public: // from Node
    virtual Node * getParent() OVERRIDE;
    virtual Node * getNextSibling() OVERRIDE;
    virtual Node * getFirstChild() OVERRIDE;
    virtual size_t getNbChild() OVERRIDE;
    virtual wstring getSID() OVERRIDE;

    virtual bool hasParent() OVERRIDE;
    virtual bool hasNextSibling() OVERRIDE;
    virtual bool hasFirstChild() OVERRIDE;

    virtual void display() OVERRIDE;
    virtual void display_positionOnly() OVERRIDE;

public:
    NodeImp();

public: // set
    void setParent( NodeImp * parent );
    void setNextSibling( NodeImp * nextSibling );
    void appendChild( NodeImp * child );
    void setSID( wstring sid );

    void appendInstanceGeometry( Instance * instanceGeometry );

private: // from Node
    wstring sid_;
    NodeImp * parent_;
    NodeImp * nextSibling_;
    NodeImp * firstChildren_;
    size_t nbChildren_;

private: // instance
    typedef vector< Instance * > Instances;
    Instances instanceGeometries_;

private: // render
    void renderInstanceGeometries();
    void renderInstanceGeometries_positionOnly();
};


}