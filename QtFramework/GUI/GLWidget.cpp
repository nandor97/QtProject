#include "GLWidget.h"
#include <GL/glu.h>
#include "Test/TestFunctions.h"
#include "Parametric/ParametricCurves3.h"

#include <iostream>
using namespace std;

#include <Core/Exceptions.h>

namespace cagd
{
//--------------------------------
// special and default constructor
//--------------------------------
GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
{
}

//--------------------------------------------------------------------------------------
// this virtual function is called once before the first call to paintGL() or resizeGL()
//--------------------------------------------------------------------------------------

GLWidget::~GLWidget()
{
    for (GLuint i = 0; i < 6; ++i)
    {
        if(_pc[i])
            delete _pc[i], _pc[i] = 0;
        if(_image_of_pc[i])
            delete _image_of_pc[i], _image_of_pc[i] = 0;
    }
}

void GLWidget::initializeGL()
{
    _pc_index = 0;
    // creating a perspective projection matrix
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    _aspect = (float)width() / (float)height();
    _z_near = 1.0;
    _z_far = 1000.0;
    _fovy = 45.0;

    gluPerspective(_fovy, _aspect, _z_near, _z_far);

    // setting the model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _eye[0] = _eye[1] = 0.0, _eye[2] = 6.0;
    _center[0] = _center[1] = _center[2] = 0.0;
    _up[0] = _up[2] = 0.0, _up[1] = 1.0;

    gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

    // enabling depth test
    glEnable(GL_DEPTH_TEST);

    // setting the color of background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // initial values of transformation parameters
    _angle_x = _angle_y = _angle_z = 0.0;
    _trans_x = _trans_y = _trans_z = 0.0;
    _zoom = 1.0;

    try
    {
        // initializing the OpenGL Extension Wrangler library
        GLenum error = glewInit();

        if (error != GLEW_OK)
        {
            throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
        }

        if (!glewIsSupported("GL_VERSION_2_0"))
        {
            throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                            "Try to update your driver or buy a new graphics adapter!");
        }

        // create and store your geometry in display lists or vertex buffer objects
        // ...
        //homework
        glEnable (GL_POINT_SMOOTH);
        glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable (GL_LINE_SMOOTH);
        glHint (GL_LINE_SMOOTH_HINT , GL_NICEST);
        glEnable (GL_POLYGON_SMOOTH);
        glHint (GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        glHint (GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST);

        glEnable (GL_DEPTH_TEST);

        glewInit();

        _pc.ResizeColumns(6);
        _image_of_pc.ResizeColumns(6);

        GLuint div_point_count =200;
        GLenum usage_flag = GL_STATIC_DRAW;

        //spiral on cone

        RowMatrix<ParametricCurve3::Derivative> derivative_spiral(3);

        derivative_spiral(0) = spiral_on_cone::d0;
        derivative_spiral(1) = spiral_on_cone::d1;
        derivative_spiral(2) = spiral_on_cone::d2;

        _pc[0] = 0;
        _pc[0] = new ParametricCurve3(derivative_spiral,spiral_on_cone::u_min, spiral_on_cone::u_max);

        if(!_pc[0]){
            throw Exception("_pc is null!");
        }

        _image_of_pc[0] = 0;
        _image_of_pc[0] = _pc[0]->GenerateImage(div_point_count,usage_flag);
        if(!_image_of_pc[0]){
            throw("Image_pc is null!");
        }

        if(!_image_of_pc[0]-> UpdateVertexBufferObjects(usage_flag)){
            cout<<"Could not create the vertex buffer object of the parametric curve!"<<endl;
        }

        //cochleoid

        RowMatrix<ParametricCurve3::Derivative> derivative_cochleoid(3);

        derivative_cochleoid(0) = cochleoid::d0;
        derivative_cochleoid(1) = cochleoid::d1;
        derivative_cochleoid(2) = cochleoid::d2;

        _pc[1] = 0;
        _pc[1] = new ParametricCurve3(derivative_cochleoid,cochleoid::u_min, cochleoid::u_max);

        if(!_pc[1]){
            throw Exception("_pc is null!");
        }

        _image_of_pc[1] = 0;
        _image_of_pc[1] = _pc[1]->GenerateImage(div_point_count,usage_flag);
        if(!_image_of_pc[1]){
            throw("Image_pc is null!");
        }

        if(!_image_of_pc[1]-> UpdateVertexBufferObjects(usage_flag)){
            cout<<"Could not create the vertex buffer object of the parametric curve!"<<endl;
        }

        //torus knot

        RowMatrix<ParametricCurve3::Derivative> derivative_torus_knot(3);

        derivative_torus_knot(0) = torus_knot::d0;
        derivative_torus_knot(1) = torus_knot::d1;
        derivative_torus_knot(2) = torus_knot::d2;

        _pc[2] = 0;
        _pc[2] = new ParametricCurve3(derivative_torus_knot,torus_knot::u_min, torus_knot::u_max);

        if(!_pc[2]){
            throw Exception("_pc is null!");
        }

        _image_of_pc[2] = 0;
        _image_of_pc[2] = _pc[2]->GenerateImage(div_point_count,usage_flag);
        if(!_image_of_pc[2]){
            throw("Image_pc is null!");
        }

        if(!_image_of_pc[2]-> UpdateVertexBufferObjects(usage_flag)){
            cout<<"Could not create the vertex buffer object of the parametric curve!"<<endl;
        }

        //ellipse

        RowMatrix<ParametricCurve3::Derivative> derivative_ellipse(3);

        derivative_ellipse(0) = ellipse::d0;
        derivative_ellipse(1) = ellipse::d1;
        derivative_ellipse(2) = ellipse::d2;

        _pc[3] = 0;
        _pc[3] = new ParametricCurve3(derivative_ellipse,ellipse::u_min, ellipse::u_max);

        if(!_pc[3]){
            throw Exception("_pc is null!");
        }

        _image_of_pc[3] = 0;
        _image_of_pc[3] = _pc[3]->GenerateImage(div_point_count,usage_flag);
        if(!_image_of_pc[3]){
            throw("Image_pc is null!");
        }

        if(!_image_of_pc[3]-> UpdateVertexBufferObjects(usage_flag)){
            cout<<"Could not create the vertex buffer object of the parametric curve!"<<endl;
        }

        //epicycloid

        RowMatrix<ParametricCurve3::Derivative> derivative_epicycloid(3);

        derivative_epicycloid(0) = epicycloid::d0;
        derivative_epicycloid(1) = epicycloid::d1;
        derivative_epicycloid(2) = epicycloid::d2;

        _pc[4] = 0;
        _pc[4] = new ParametricCurve3(derivative_epicycloid,epicycloid::u_min, epicycloid::u_max);

        if(!_pc[4]){
            throw Exception("_pc is null!");
        }

        _image_of_pc[4] = 0;
        _image_of_pc[4] = _pc[4]->GenerateImage(div_point_count,usage_flag);
        if(!_image_of_pc[4]){
            throw("Image_pc is null!");
        }

        if(!_image_of_pc[4]-> UpdateVertexBufferObjects(usage_flag)){
            cout<<"Could not create the vertex buffer object of the parametric curve!"<<endl;
        }
        //hypocycloid
        RowMatrix<ParametricCurve3::Derivative> derivative_hypocycloid(3);

        derivative_hypocycloid(0) = hypocycloid::d0;
        derivative_hypocycloid(1) = hypocycloid::d1;
        derivative_hypocycloid(2) = hypocycloid::d2;

        _pc[5] = 0;
        _pc[5] = new ParametricCurve3(derivative_hypocycloid,hypocycloid::u_min, hypocycloid::u_max);

        if(!_pc[5]){
            throw Exception("_pc is null!");
        }

        _image_of_pc[5] = 0;
        _image_of_pc[5] = _pc[5]->GenerateImage(div_point_count,usage_flag);
        if(!_image_of_pc[5]){
            throw("Image_pc is null!");
        }

        if(!_image_of_pc[5]-> UpdateVertexBufferObjects(usage_flag)){
            cout<<"Could not create the vertex buffer object of the parametric curve!"<<endl;
        }

        //Ciclic curve

        _cc = 0;
        _n = 2; //rogziti a kontrolpontok szamat 2*n +1
        _cc = new(nothrow)CyclicCurve3(_n);
        if(!_cc)
        {
            throw Exception("Could not create the cyclic curve");
        }
        //mivel a kontrolpontok DCoordinate3 tipusuak, az origoba vannak "inicializalva", ezert meg kell valtoztatni a helyzetuket
        GLdouble step = TWO_PI/(2* _n + 1);
        for(GLuint i = 0; i <= 2 * _n; i++)
        {
            GLdouble u = i * step;
            DCoordinate3 &cp = (*_cc)[i]; //visszateriti az i-edik kontrolpontra valo hivatkozast - p(i) vektor
            cp[0] = cos(u);
            cp[1] = sin(u);
            cp[2] = 0.0; //ha lecsereljuk, akkor tergorbe lesz pl. -2.0 + 4.0 * (GLdouble) rand()/RAND_MAX;
        }
        if(!_cc -> UpdateVertexBufferObjectsOfData())
        {
            throw Exception("Could not update the VBOs objects of the cyclic curves control polygon");
        }
        _div_point_count = 100;
        _max_order_of_derivatives = 3;
        _img_cc = _cc ->GenerateImage(_max_order_of_derivatives, _div_point_count);
        if(!_img_cc)
        {
            throw Exception("Could not generate the image of the cyclic curve!");
        }
        if(!_img_cc -> UpdateVertexBufferObjects())
        {
            throw Exception("Could not update the VBOs of the cyclic curves's image!");
        }

        //interpolating cyclic curve
        _icc = 0;
        _n_i = 3;
        GLdouble div_point_count_i = 100;

        _icc = new CyclicCurve3(_n_i);
        GLdouble istep = TWO_PI/(2 * _n_i + 1);
        GLdouble t = 0;

        u.ResizeRows(2 * _n_i + 1);
        d.ResizeRows(2 * _n_i + 1);

        for (GLuint i = 0; i < 2 * _n_i + 1; i++, t += istep)
        {
            u[i] = t;

            DCoordinate3 &icp = (*_icc)[i];
            icp.x() = cos(t);
            icp.y() = sin(t);
            icp.z() = 0;
            d[i] = icp;
        }
        d[0][2] = 3.0;
        _icc->UpdateDataForInterpolation(u, d);

        _icc->UpdateVertexBufferObjectsOfData();
        _mod = 2;
        _img_icc = _icc->GenerateImage(_mod, div_point_count_i);
        _img_icc->UpdateVertexBufferObjects();
    }
    catch (Exception &e)
    {
        cout << e << endl;
    }

}

//-----------------------
// the rendering function
//-----------------------
void GLWidget::paintGL()
{
    // clears the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // stores/duplicates the original model view matrix
    glPushMatrix();

    // applying transformations
    glRotatef(_angle_x, 1.0, 0.0, 0.0);
    glRotatef(_angle_y, 0.0, 1.0, 0.0);
    glRotatef(_angle_z, 0.0, 0.0, 1.0);
    glTranslated(_trans_x, _trans_y, _trans_z);
    glScaled(_zoom, _zoom, _zoom);

    // render your geometry (this is oldest OpenGL rendering technique, later we will use some advanced methods)

    /*------------------------------------------
                TRIANGLE
--------------------------------------------*/

    /*
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(1.1f, 0.0f, 0.0f);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.1f, 0.0f);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, 1.1f);
            glEnd();

            glBegin(GL_TRIANGLES);
                // attributes
                glColor3f(1.0f, 0.0f, 0.0f);
                // associated with position
                glVertex3f(1.0f, 0.0f, 0.0f);

                // attributes
                glColor3f(0.0, 1.0, 0.0);
                // associated with position
                glVertex3f(0.0, 1.0, 0.0);

                // attributes
                glColor3f(0.0f, 0.0f, 1.0f);
                // associated with position
                glVertex3f(0.0f, 0.0f, 1.0f);
            glEnd();
*/

    /*------------------------------------------
             Parametric curves
--------------------------------------------*/

    if (_pc_index < 6)
    {
        if(_image_of_pc[_pc_index])
        {
            glColor3f(1.0,0.0,0.0);
            _image_of_pc[_pc_index]->RenderDerivatives(0,GL_LINE_STRIP); //_0 helyett _pc_index

            glPointSize(5.0);

            glColor3f(0.0,0.5,0.0);
            _image_of_pc[_pc_index]->RenderDerivatives(1,GL_LINES);
            _image_of_pc[_pc_index]->RenderDerivatives(1,GL_POINTS);

            glColor3f(1.0,0.5,0.0);
            _image_of_pc[_pc_index]->RenderDerivatives(2,GL_LINES);
            _image_of_pc[_pc_index]->RenderDerivatives(2,GL_POINTS);
        }
    }
    else if (_pc_index == 6)
    {
        if(_cc)
        {
            _cc->RenderData(GL_LINE_LOOP);
        }

        if(_img_cc)
        {
            _img_cc->RenderDerivatives(3, GL_LINES); //ha 0 az elso parameter akkor GL_LINE_LOOP
        }
    }
    else if (_pc_index == 7)
    {
        if (_icc)
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            _icc->RenderData(GL_LINE_LOOP);
        }
        if (_img_icc)
        {
            glColor3f(1.0,0.0,0.0);
            _img_icc->RenderDerivatives(0, GL_LINE_LOOP);

            glColor3f(0.0,0.5,0.0);
            _img_icc->RenderDerivatives(1, GL_LINES);

            glColor3f(1.0,0.5,0.0);
            _img_icc->RenderDerivatives(2, GL_LINES);

        }
    }
    // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
    // i.e., the original model view matrix is restored
    glPointSize(1.0);
    glPopMatrix();

}

//----------------------------------------------------------------------------
// when the main window is resized one needs to redefine the projection matrix
//----------------------------------------------------------------------------
void GLWidget::resizeGL(int w, int h)
{
    // setting the new size of the rendering context
    glViewport(0, 0, w, h);

    // redefining the projection matrix
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    _aspect = (float)w / (float)h;

    gluPerspective(_fovy, _aspect, _z_near, _z_far);

    // switching back to the model view matrix
    glMatrixMode(GL_MODELVIEW);

    updateGL();
}

//-----------------------------------
// implementation of the public slots
//-----------------------------------

void GLWidget::set_angle_x(int value)
{
    if (_angle_x != value)
    {
        _angle_x = value;
        updateGL();
    }
}

void GLWidget::set_angle_y(int value)
{
    if (_angle_y != value)
    {
        _angle_y = value;
        updateGL();
    }
}

void GLWidget::set_angle_z(int value)
{
    if (_angle_z != value)
    {
        _angle_z = value;
        updateGL();
    }
}

void GLWidget::set_zoom_factor(double value)
{
    if (_zoom != value)
    {
        _zoom = value;
        updateGL();
    }
}

void GLWidget::set_trans_x(double value)
{
    if (_trans_x != value)
    {
        _trans_x = value;
        updateGL();
    }
}

void GLWidget::set_trans_y(double value)
{
    if (_trans_y != value)
    {
        _trans_y = value;
        updateGL();
    }
}

void GLWidget::set_trans_z(double value)
{
    if (_trans_z != value)
    {
        _trans_z = value;
        updateGL();
    }
}

void GLWidget::set_pc_index(int value)
{
    //cout<<"Szam: " << value <<endl;
    if(_pc_index != value){
        _pc_index = value;
        updateGL();
    }
}


}

