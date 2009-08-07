#pragma once
namespace my_render_imp {


class RenderImp : IMPLEMENTS_ Render {
public:
    virtual void setScreenWidth( int width );
    virtual void setScreenHeight( int height );

    virtual int getScreenWidth();
    virtual int getScreenHeight();

    virtual bool load( wstring filename );
    virtual void setUpAxis( domUpAxisType up );
    virtual domUpAxisType getUpAxis();

    virtual bool render();

    virtual Scene * getScene();

public: // matrix
    INTERFACE_ MatrixStack {
    public:
    public: virtual ~MatrixStack() {}
    };
    MY_SMART_PTR( MatrixStack );

    MatrixStackPtr createMatrix();

private: // update
    void updateCamera();
    void updateSceneGraph();

private: // load
    static wstring getFilenameOnly( wstring fullFilename );
    static wstring getPathnameOnly( wstring fullFilename );

    wstring filename_, pathname_;

private:
    domUpAxisType upAxis_;
    int width_, height_;
    SceneImpPtr scene_;

private: // matrix
    void pushMatrix();
    void popMatrix();

    class MatrixStackImp : IMPLEMENTS_ MatrixStack {
    public:
        MatrixStackImp( RenderImp * render );
        ~MatrixStackImp();
    private:
        RenderImp * render_;
    };
};

}