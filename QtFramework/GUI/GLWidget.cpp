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
        if(_pc)
            delete _pc, _pc = 0;
        if(_image_of_pc)
            delete _image_of_pc, _image_of_pc = 0;
    }

    void GLWidget::initializeGL()
    {
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

            RowMatrix<ParametricCurve3::Derivative> derivative(3);
            derivative(0) = spiral_on_cone::d0;
            derivative(1) = spiral_on_cone::d1;
            derivative(2) = spiral_on_cone::d2;

            _pc = 0;
            _pc = new ParametricCurve3(derivative, spiral_on_cone::u_min, spiral_on_cone::u_max);

            if (!_pc)
            {
                //error: either close the application , or handle this exception
                throw Exception("Could not create the parametric curve!");
                //application.close();
            }

            GLuint div_point_count = 200;
            GLenum usage_flag = GL_STATIC_DRAW;

            _image_of_pc = 0;

            _image_of_pc = _pc->GenerateImage(div_point_count, usage_flag);

            if (!_image_of_pc)
            {
                //error: either close the application , or handle this exception
                throw Exception("Could not create the image of parametric curve");
                //application.close();
            }

            if (!_image_of_pc->UpdateVertexBufferObjects(usage_flag))
            {
                cout << "Could not create the vertex buffer object of the parametric curve!" << endl;
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

/*------------------------------------------
             SPIRAL ON CONE
--------------------------------------------*/

        if (_image_of_pc)
        {
            glColor3f(1.0, 0.0, 0.0);
            _image_of_pc->RenderDerivatives(0, GL_LINE_STRIP);

            glPointSize(5.0);

                glColor3f(0.0, 0.5, 0.0);
                _image_of_pc->RenderDerivatives(1, GL_LINES);
                _image_of_pc->RenderDerivatives(1, GL_POINTS);

                glColor3f(0.1, 0.5, 0.9);
                _image_of_pc->RenderDerivatives(2, GL_LINES);
                _image_of_pc->RenderDerivatives(2, GL_POINTS);

            glPointSize(1.0);

        }
        // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
        // i.e., the original model view matrix is restored
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
}
