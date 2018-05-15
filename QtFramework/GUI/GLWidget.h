#pragma once

#include <GL/glew.h>
#include <QGLWidget>
#include <QGLFormat>
#include <QTimer>
#include "../Core/GenericCurves3.h"
#include "../Parametric/ParametricCurves3.h"
#include "../Cyclic/CyclicCurves3.h"
#include "../Core/Constants.h"
#include"Core/ShaderPrograms.h"
#include"Core/TriangulatedMeshes3.h"
#include"Core/TriangularFaces.h"
#include"Core/Materials.h"
#include"Core/Lights.h"
#include"Parametric/ParametricSurfaces3.h"
#include"Trigonometric/QuarticAlgebraicTrigonometricPatches.h"

namespace cagd
{
    class GLWidget: public QGLWidget
    {
        Q_OBJECT

    private:

        // variables defining the projection matrix
        float       _aspect;            // aspect ratio of the rendering window
        float       _fovy;              // field of view in direction y
        float       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        float       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // your other declarations
        //parametric curves
        RowMatrix<ParametricCurve3*> _pc;
        RowMatrix<GenericCurve3*> _image_of_pc;
        GLint _pc_index;

        //cyclic curve
        CyclicCurve3 *_cc;
        GLuint _n; //order of the cyclic curve
        GLuint _max_order_of_derivatives;
        GLuint _div_point_count; //number of subdivision points
        GenericCurve3* _img_cc;

        //interpolating cyclic curve
        CyclicCurve3 *_icc;
        GenericCurve3 *_img_icc;
        GLuint _n_i;
        GLuint _mod;
        GLuint _div_point_count_i;
        ColumnMatrix<GLdouble> u;
        ColumnMatrix<DCoordinate3> d;

        TriangulatedMesh3* _mouse;
        TriangulatedMesh3* _elephant;
        Material* _material_mouse;
        Material* _material_elephant;
        QTimer *_timer;
        GLdouble _angle;

        RowMatrix<ParametricSurface3*> _surf;
        RowMatrix<TriangulatedMesh3*> _surf_img;
        Material* _material_surface;

        GLdouble _alpha;
        QuarticAlgebraicTrigonometricPatch* _patch;
        TriangulatedMesh3 *_before_interpolation, *_after_interpolation;
        RowMatrix<GenericCurve3*>* _u_dir;
        RowMatrix<GenericCurve3*>* _v_dir;

        GLint _shader_index;
        ShaderProgram _shader_reflection_lines;
        ShaderProgram _shader_directional_light;
        ShaderProgram _shader_toon;
        ShaderProgram _shader_two_sided_lighting;

        GLdouble _scale;
        GLdouble _smoothing;
        GLdouble _shading;
        GLdouble _red, _green, _blue, _alpha_color;

    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);

        //your other declarations
        virtual ~GLWidget();

    public slots:
        // public event handling methods/slots
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);
        void set_pc_index(int value);
        void _animate();

        void set_shader_index(int i);
        void set_scale(double value);
        void set_smoothing(double value);
        void set_shading(double value);
        void set_red(double value);
        void set_green(double value);
        void set_blue(double value);
        void set_alpha_color(double value);
    };
}
