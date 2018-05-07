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
}
