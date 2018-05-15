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
    _timer = new QTimer(this);
    _timer->setInterval(0);

    connect(_timer, SIGNAL(timeout()), this, SLOT(_animate()));
}

//--------------------------------------------------------------------------------------
// this virtual function is called once before the first call to paintGL() or resizeGL()
//--------------------------------------------------------------------------------------

GLWidget::~GLWidget()
{
    for(GLuint i = 0; i < 6; i++)
    {
        if(_pc[i]){
            delete _pc[i];

        }

        if(_image_of_pc[i]){
            delete _image_of_pc[i];
        }
    }
    for(GLuint i = 0; i < 6; i++)
    {
        if(_surf[i]){
            delete _surf[i];

        }

        if(_surf_img[i]){
            delete _surf_img[i];
        }
    }
    if(_cc)
        delete _cc;

    if(_img_cc)
        delete _img_cc;
    if(_icc)
        delete _icc;
    if(_img_icc)
        delete _img_icc;
    if(_before_interpolation)
        delete _before_interpolation, _before_interpolation = 0;
    if(_after_interpolation)
        delete _after_interpolation, _after_interpolation = 0;
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
        d[0][2] = 2.0;
        _icc->UpdateDataForInterpolation(u, d);

        _icc->UpdateVertexBufferObjectsOfData();
        _mod = 2;
        _img_icc = _icc->GenerateImage(_mod, div_point_count_i);
        _img_icc->UpdateVertexBufferObjects();
        //----------------Eger-------------------------------------------------
        _mouse = new (nothrow) TriangulatedMesh3();

        if(!_mouse)
            throw Exception("Could not create the triangulated mesh of the mouse model!");

        if(!_mouse->LoadFromOFF("Models/mouse.off", GL_TRUE))
            throw Exception("Could not load the mouse.off file!");

        _angle = 0.0;
        _timer->start();

        if(!_mouse->UpdateVertexBufferObjects(usage_flag))
            throw Exception("Could not update the vbo of the model!");

        _material_mouse = new (nothrow) Material(MatFBRuby);

        if(!_material_mouse)
            throw Exception("Could not create the material of the model!");
        //-----------------Elefant-----------------------------------------------

        _elephant = new (nothrow) TriangulatedMesh3();

        if(!_elephant)
            throw Exception("Could not create the triangulated mesh of the elephant model!");

        if(!_elephant->LoadFromOFF("Models/elephant.off", GL_TRUE))
            throw Exception("Could not load the elephant.off file!");

        _angle = 0.0;
        _timer->start();

        if(!_elephant->UpdateVertexBufferObjects(usage_flag))
            throw Exception("Could not update the vbo of the model!");

        _material_elephant = new (nothrow) Material(MatFBEmerald);

        if(!_material_elephant)
            throw Exception("Could not create the material of the model!");



        _surf.ResizeColumns(5);
        _surf_img.ResizeColumns(5);
        _material_surface = new (nothrow) Material(MatFBEmerald);
        //_dl = new DirectionalLight(GL_LIGHT0, HCoordinate3(-30, -30, 100, 1), Color4(1.0,1.0,1.0), Color4(1.0,1.0,1.0), Color4(1.0,1.0,1.0));

        // ----------------------spheroid------------------------------------------------
        TriangularMatrix<ParametricSurface3::PartialDerivative> derivatives_spheroid(3);
        derivatives_spheroid(0,0) = spheroid::d00;
        derivatives_spheroid(1,0) = spheroid::d01;
        derivatives_spheroid(1,1) = spheroid::d10;
        _surf[0] = 0;
        _surf[0] = new ParametricSurface3(derivatives_spheroid, spheroid::u_min, spheroid::u_max, spheroid::v_min, spheroid::v_max);
        if(!_surf[0])
        {
            throw("surface is null!");
        }
        _surf_img[0] = _surf[0]->GenerateImage(100,100);
        if(!_surf_img[0]){
             throw("Surface_image is null!");
        }

        if(!_surf_img[0]-> UpdateVertexBufferObjects(usage_flag)){
              cout<<"Could not create the vertex buffer object of the parametric surface!"<<endl;
        }

        //---------------------------conchoid--------------------------------------------------
        TriangularMatrix<ParametricSurface3::PartialDerivative> derivatives_conchoid(3);
        derivatives_conchoid(0,0) = conchoid::d00;
        derivatives_conchoid(1,0) = conchoid::d01;
        derivatives_conchoid(1,1) = conchoid::d10;
        _surf[1] = 0;
        _surf[1] = new ParametricSurface3(derivatives_conchoid, conchoid::u_min, conchoid::u_max, conchoid::v_min, conchoid::v_max);
        if(!_surf[1])
        {
            throw("surface is null!");
        }
        _surf_img[1] = _surf[1]->GenerateImage(100,100);
        if(!_surf_img[1]){
             throw("Surface_image is null!");
        }

        if(!_surf_img[1]-> UpdateVertexBufferObjects(usage_flag)){
              cout<<"Could not create the vertex buffer object of the parametric surface!"<<endl;
        }

        //-------------------------------elliptic_torus----------------------------------------------
        TriangularMatrix<ParametricSurface3::PartialDerivative> derivatives_elliptic_torus(3);
        derivatives_elliptic_torus(0,0) = elliptic_torus::d00;
        derivatives_elliptic_torus(1,0) = elliptic_torus::d01;
        derivatives_elliptic_torus(1,1) = elliptic_torus::d10;
        _surf[2] = 0;
        _surf[2] = new ParametricSurface3(derivatives_elliptic_torus, elliptic_torus::u_min, elliptic_torus::u_max, elliptic_torus::v_min, elliptic_torus::v_max);
        if(!_surf[2])
        {
            throw("surface is null!");
        }
        _surf_img[2] = _surf[2]->GenerateImage(100,100);
        if(!_surf_img[2]){
             throw("Surface_image is null!");
        }

        if(!_surf_img[2]-> UpdateVertexBufferObjects(usage_flag)){
              cout<<"Could not create the vertex buffer object of the parametric surface!"<<endl;
        }

        //-----------------------------------astroidal------------------------------------------------
        TriangularMatrix<ParametricSurface3::PartialDerivative> derivatives_astroidal(3);
        derivatives_astroidal(0,0) = astroidal::d00;
        derivatives_astroidal(1,0) = astroidal::d01;
        derivatives_astroidal(1,1) = astroidal::d10;
        _surf[3] = 0;
        _surf[3] = new ParametricSurface3(derivatives_astroidal, astroidal::u_min, astroidal::u_max, astroidal::v_min, astroidal::v_max);
        if(!_surf[3])
        {
            throw("surface is null!");
        }
        _surf_img[3] = _surf[3]->GenerateImage(100,100);
        if(!_surf_img[3]){
             throw("Surface_image is null!");
        }

        if(!_surf_img[3]-> UpdateVertexBufferObjects(usage_flag)){
              cout<<"Could not create the vertex buffer object of the parametric surface!"<<endl;
        }

        //-----------------------------------sine_surface----------------------------------------
        TriangularMatrix<ParametricSurface3::PartialDerivative> derivatives_sine_surface(3);
        derivatives_sine_surface(0,0) = sine_surface::d00;
        derivatives_sine_surface(1,0) = sine_surface::d01;
        derivatives_sine_surface(1,1) = sine_surface::d10;
        _surf[4] = 0;
        _surf[4] = new ParametricSurface3(derivatives_sine_surface, sine_surface::u_min, sine_surface::u_max, sine_surface::v_min, sine_surface::v_max);
        if(!_surf[4])
        {
            throw("surface is null!");
        }
        _surf_img[4] = _surf[4]->GenerateImage(100,100);
        if(!_surf_img[4]){
             throw("Surface_image is null!");
        }

        if(!_surf_img[4]-> UpdateVertexBufferObjects(usage_flag)){
              cout<<"Could not create the vertex buffer object of the parametric surface!"<<endl;
        }

        _shader_index = 0;
        _scale = 5.0f;
        _smoothing = 2.0f;
        _shading = 1.0f;

        _red = 1.0;
        _green = 0.2;
        _blue = 0.4;
        _alpha = 1.0;
        //-----------------------reflection line shader----------------------------------------------
        if(!_shader_reflection_lines.InstallShaders("Shaders/reflection_lines.vert", "Shaders/reflection_lines.frag", GL_TRUE))
        {
            throw("Could not install the shader files");
        }
        _shader_reflection_lines.Enable();
        _shader_reflection_lines.SetUniformVariable1f("scale_factor", _scale);
        _shader_reflection_lines.SetUniformVariable1f("smoothing", _smoothing);
        _shader_reflection_lines.SetUniformVariable1f("shading", _shading);
        _shader_reflection_lines.Disable();

        //-------------------------directional light---------------------------------------
        if(!_shader_directional_light.InstallShaders("Shaders/directional_light.vert", "Shaders/directional_light.frag", GL_TRUE))
        {
            throw("Could not install the shader files");
        }
        _shader_directional_light.Enable();
        _shader_directional_light.Disable();

        //-------------------------------------toon-----------------------------------------------
        if(!_shader_toon.InstallShaders("Shaders/toon.vert", "Shaders/toon.frag", GL_TRUE))
        {
            throw("Could not install the shader files");
        }
        _shader_toon.Enable();

        _shader_toon.SetUniformVariable4f("default_outline_color", (GLfloat)_red, (GLfloat)_green, (GLfloat)_blue, (GLfloat)_alpha);
        _shader_toon.Disable();

        //------------------------------two sided lighting---------------------------------
        if(!_shader_two_sided_lighting.InstallShaders("Shaders/two_sided_lighting.vert", "Shaders/two_sided_lighting.frag", GL_TRUE))
        {
            throw("Could not install the shader files");
        }
        _shader_two_sided_lighting.Enable();
        _shader_two_sided_lighting.Disable();

        //--------------------------Quartic Algebraic Trigonometric Patch-------------------------------------
        _alpha = 3.0;
        _patch = 0;
        _patch = new QuarticAlgebraicTrigonometricPatch(_alpha);
        _patch->SetData(0, 0, -2.0, -2.0, 0.0);
        _patch->SetData(0, 1, -2.0, -1.0, 0.0);
        _patch->SetData(0, 2, -2.0, 1.0, 0.0);
        _patch->SetData(0, 3, -2.0, 2.0, 0.0);

        _patch->SetData(1, 0, -1.0, -2.0, 0.0);
        _patch->SetData(1, 1, -1.0, -1.0, 2.0);
        _patch->SetData(1, 2, -1.0, 1.0, 2.0);
        _patch->SetData(1, 3, -1.0, 2.0, 0.0);

        _patch->SetData(2, 0, 1.0, -2.0, 0.0);
        _patch->SetData(2, 1, 1.0, -1.0, 2.0);
        _patch->SetData(2, 2, 1.0, 1.0, 2.0);
        _patch->SetData(2, 3, 1.0, 2.0, 0.0);

        _patch->SetData(3, 0, 2.0, -2.0, 0.0);
        _patch->SetData(3, 1, 2.0, -1.0, 0.0);
        _patch->SetData(3, 2, 2.0, 1.0, 0.0);
        _patch->SetData(3, 3, 2.0, 2.0, 0.0);

        _patch->UpdateVertexBufferObjectsOfData();
        // generate the mesh of the surface patch
        _before_interpolation = _patch->GenerateImage(30, 30, GL_STATIC_DRAW);

        if (_before_interpolation)
            _before_interpolation->UpdateVertexBufferObjects();

        // define an interpolation problem:
        // 1: create a knot vector in u-direction
        RowMatrix<GLdouble> u_knot_vector(4);
        u_knot_vector(0) = 0.0;
        u_knot_vector(1) = _alpha / 3.0;
        u_knot_vector(2) = 2.0 * _alpha / 3.0;
        u_knot_vector(3) = _alpha;

        // 2: create a knot vector in v-direction
        ColumnMatrix<GLdouble> v_knot_vector(4);
        v_knot_vector(0) = 0.0;
        v_knot_vector(1) = _alpha / 3.0;
        v_knot_vector(2) = 2.0 * _alpha / 3.0;
        v_knot_vector(3) = _alpha;

        // 3: define a matrix of data points, e.g. set them to the original control points
        Matrix<DCoordinate3> data_points_to_interpolate(4, 4);
        for (GLuint row = 0; row < 4; ++row)
            for (GLuint column = 0; column < 4; ++column)
                _patch->GetData(row, column, data_points_to_interpolate(row, column));

        // 4: solve the interpolation problem and generate the mesh of the interpolating patch
        if (_patch->UpdateDataForInterpolation(u_knot_vector, v_knot_vector, data_points_to_interpolate))
        {
            _after_interpolation = _patch->GenerateImage(30, 30, GL_STATIC_DRAW);

            if (_after_interpolation)
                _after_interpolation->UpdateVertexBufferObjects();
        }
        _u_dir = _patch->GenerateUIsoparametricLines(10, 1, 10);
        _v_dir = _patch->GenerateVIsoparametricLines(10, 1, 10);
        for (GLuint j = 0; j < _u_dir->GetColumnCount(); ++j)
        {
            // (*_u_dir)[j]->RenderDerivatives(0, GL_LINE_STRIP);
            (*_u_dir)[j]->UpdateVertexBufferObjects();
        }

        for (GLuint j = 0; j < _v_dir->GetColumnCount(); ++j)
        {
            //(*_v_dir)[j]->RenderDerivatives(0, GL_LINE_STRIP);
            (*_v_dir)[j]->UpdateVertexBufferObjects();
        }
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
    /*-------------------------------------
     *                 SHADERS
     * -----------------------------------*/

    if(_shader_index == 0)
    {
        _shader_reflection_lines.Disable();
        _shader_directional_light.Disable();
        _shader_toon.Disable();
        _shader_two_sided_lighting.Disable();
    }
    else if(_shader_index == 1)
    {
        _shader_reflection_lines.Enable();
        _shader_reflection_lines.SetUniformVariable1f("scale_factor", (GLfloat) _scale);
        _shader_reflection_lines.SetUniformVariable1f("smoothing", (GLfloat) _smoothing);
        _shader_reflection_lines.SetUniformVariable1f("shading", (GLfloat) _shading);
    }
    else if(_shader_index == 2)
    {
        _shader_directional_light.Enable();
    }
    else if(_shader_index == 3)
    {
        _shader_toon.Enable();
        _shader_toon.SetUniformVariable4f("default_outline_color", (GLfloat)_red, (GLfloat)_green, (GLfloat)_blue, (GLfloat)_alpha_color);
    }
    else if(_shader_index == 4)
    {
        _shader_two_sided_lighting.Enable();
    }
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
            glPointSize(15.0);
            glBegin(GL_POINTS);
            {
                for(GLuint i = 0; i < 2 * _n_i + 1; ++i)
                {
                    glVertex3d(d[i][0], d[i][1], d[i][2]);
                }
            }
            glEnd();

            glColor3f(1.0,0.0,0.0);
            _img_icc->RenderDerivatives(0, GL_LINE_LOOP);

            glColor3f(0.0,0.5,0.0);
            _img_icc->RenderDerivatives(1, GL_LINES);

            glColor3f(1.0,0.5,0.0);
            _img_icc->RenderDerivatives(2, GL_LINES);

        }
    }
    else if(_pc_index == 8)
    {
        //eger

        if(_mouse)
        {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);

            _material_mouse->Apply();

            _mouse->Render(GL_TRIANGLES);
            glDisable(GL_LIGHT0);
            glDisable(GL_NORMALIZE);
            glDisable(GL_LIGHTING);
        }

    }
    else if(_pc_index == 9)
    {
        //elefant

        if(_elephant)
        {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);

            _material_elephant->Apply();

            _elephant->Render(GL_TRIANGLES);

            glDisable(GL_LIGHT0);
            glDisable(GL_NORMALIZE);
            glDisable(GL_LIGHTING);
        }


    }
    else if(_pc_index > 9 && _pc_index < 15)
    {

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

        _material_surface->Apply();
        if(_surf_img[_pc_index - 10])
        {//ki kell vonn a 10-et, ert az _pc_index-ek kozul a 10-edik lesz az elso surface, de 0-tol vannak indexelve a rowmatrix-ba
            _surf_img[_pc_index - 10]->Render(GL_TRIANGLES);
        }
        glDisable(GL_LIGHT0);
        glDisable(GL_NORMALIZE);
        glDisable(GL_LIGHTING);

    }
    else if(_pc_index == 15)
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        for (GLuint j = 0; j < _u_dir->GetColumnCount(); ++j)
        {
            (*_u_dir)[j]->RenderDerivatives(0, GL_LINE_STRIP);
        }

        for (GLuint j = 0; j < _v_dir->GetColumnCount(); ++j)
        {
            (*_v_dir)[j]->RenderDerivatives(0, GL_LINE_STRIP);
        }
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        if (_before_interpolation)
        {
            MatFBRuby.Apply();

            glPointSize(5.0);
            glColor3f(1.0f, 0.0f, 0.4f);
            _patch->RenderData();
            _patch->RenderData(GL_POINTS);

            _before_interpolation->Render();
        }
        if (_after_interpolation)
        {
            glEnable(GL_BLEND);
            glDepthMask(GL_FALSE);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            MatFBTurquoise.Apply();
            _after_interpolation->Render();
            glDepthMask(GL_TRUE);
            glDisable(GL_BLEND);
        }
        glDisable(GL_LIGHT0);
        glDisable(GL_NORMALIZE);
        glDisable(GL_LIGHTING);

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

void GLWidget::_animate()
{
    GLfloat *vertex = _mouse->MapVertexBuffer(GL_READ_WRITE);
    GLfloat *normal = _mouse->MapNormalBuffer(GL_READ_ONLY);
    _angle += DEG_TO_RADIAN;
    if (_angle > TWO_PI) _angle -= TWO_PI;

    GLfloat scale = std::sin(_angle) / 3000.0;
    for (GLuint i=0; i<_mouse->VertexCount(); ++i)
        for (GLuint coordinate=0; coordinate<3; ++coordinate, ++vertex, ++normal)
            *vertex += scale * (*normal);

    _mouse->UnmapVertexBuffer();
    _mouse->UnmapNormalBuffer();
    updateGL();

    GLfloat *vertex2 = _elephant->MapVertexBuffer(GL_READ_WRITE);
    GLfloat *normal2 = _elephant->MapNormalBuffer(GL_READ_ONLY);
    _angle += DEG_TO_RADIAN;
    if (_angle > TWO_PI) _angle -= TWO_PI;

    GLfloat scale2 = std::sin(_angle) / 3000.0;
    for (GLuint i=0; i<_elephant->VertexCount(); ++i)
        for (GLuint coordinate=0; coordinate<3; ++coordinate, ++vertex2, ++normal2)
            *vertex2 += scale2 * (*normal2);

    _elephant->UnmapVertexBuffer();
    _elephant->UnmapNormalBuffer();
    updateGL();
}
void GLWidget::set_shader_index(int i)
{
    if(_shader_index != i)
        _shader_index = i;
    updateGL();
}
void GLWidget::set_scale(double value)
{
    //std::cout << "HERE" << endl;
    if(_scale != value){
        _scale = value;
        updateGL();
    }
}

void GLWidget::set_smoothing(double value)
{
    if(_smoothing != value){
        _smoothing = value;
        updateGL();
    }
}

void GLWidget::set_shading(double value)
{
    if(_shading != value){
        _shading = value;
        updateGL();
    }
}

void GLWidget::set_red(double value)
{
    //std::cout << "HERE" << endl;
    if(_red != value){
        _red = value;
        updateGL();
    }
}

void GLWidget::set_green(double value)
{
    //std::cout << "HERE" << endl;
    if(_green != value){
        _green = value;
        updateGL();
    }
}

void GLWidget::set_blue(double value)
{
    //std::cout << "HERE" << endl;
    if(_blue != value){
        _blue = value;
        updateGL();
    }
}

void GLWidget::set_alpha_color(double value)
{
    //std::cout << "HERE" << endl;
    if(_alpha_color != value){
        _alpha_color = value;
        updateGL();
    }
}

}

