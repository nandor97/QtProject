#pragma once

#include "../Core/DCoordinates3.h"

namespace cagd
{
    namespace spiral_on_cone
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace cochleoid
    {
        extern GLdouble u_min, u_max, a;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace torus_knot
    {
        extern GLdouble u_min, u_max, r, p, q;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace ellipse
    {
        extern GLdouble u_min, u_max, a, b;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace epicycloid
    {
        extern GLdouble u_min, u_max, k;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }
    namespace hypocycloid
    {
        extern GLdouble u_min, u_max, k;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }
    namespace spheroid
    {
        extern GLdouble a,b;
        extern GLdouble u_min, u_max, v_min, v_max;

        DCoordinate3 d00(GLdouble u, GLdouble v); // zeroth order partial derivative, i.e. surface point
        DCoordinate3 d10(GLdouble u, GLdouble v); // first order partial derivative in direction u
        DCoordinate3 d01(GLdouble u, GLdouble v); // first order partial derivative in direction v

    }
    namespace conchoid
    {
        extern GLdouble u_min, u_max, v_min, v_max;

        DCoordinate3 d00(GLdouble u, GLdouble v); // zeroth order partial derivative, i.e. surface point
        DCoordinate3 d10(GLdouble u, GLdouble v); // first order partial derivative in direction u
        DCoordinate3 d01(GLdouble u, GLdouble v); // first order partial derivative in direction v

    }
    namespace elliptic_torus
    {
        extern GLdouble a,b,c;
        extern GLdouble u_min, u_max, v_min, v_max;

        DCoordinate3 d00(GLdouble u, GLdouble v); // zeroth order partial derivative, i.e. surface point
        DCoordinate3 d10(GLdouble u, GLdouble v); // first order partial derivative in direction u
        DCoordinate3 d01(GLdouble u, GLdouble v); // first order partial derivative in direction v

    }
    namespace astroidal
    {
        extern GLdouble u_min, u_max, v_min, v_max;

        DCoordinate3 d00(GLdouble u, GLdouble v); // zeroth order partial derivative, i.e. surface point
        DCoordinate3 d10(GLdouble u, GLdouble v); // first order partial derivative in direction u
        DCoordinate3 d01(GLdouble u, GLdouble v); // first order partial derivative in direction v

    }
    namespace sine_surface
    {
        extern GLdouble a;
        extern GLdouble u_min, u_max, v_min, v_max;

        DCoordinate3 d00(GLdouble u, GLdouble v); // zeroth order partial derivative, i.e. surface point
        DCoordinate3 d10(GLdouble u, GLdouble v); // first order partial derivative in direction u
        DCoordinate3 d01(GLdouble u, GLdouble v); // first order partial derivative in direction v

    }
}
