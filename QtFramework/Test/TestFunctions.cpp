#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}

//ellipse

GLdouble ellipse::u_min = -TWO_PI;
GLdouble ellipse::u_max = +TWO_PI;
GLdouble ellipse::a = 2.0;
GLdouble ellipse::b = 4.0;

DCoordinate3 ellipse::d0(GLdouble u)
{
    return DCoordinate3(a*cos(u), b*sin(u), 0.0);
}

DCoordinate3 ellipse::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-a * s, b * c, 0.0);
}
DCoordinate3 ellipse::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-a * c, -b * s, 0.0);
}

//cochleoid

GLdouble cochleoid::u_min = -TWO_PI;
GLdouble cochleoid::u_max = +TWO_PI;
GLdouble cochleoid::a = 1;

DCoordinate3 cochleoid::d0(GLdouble u)
{
    return DCoordinate3((a * sin(u) * cos(u)) / u,
                        (a * sin(u) * sin(u))/u, 0);
}

DCoordinate3 cochleoid::d1(GLdouble u)
{
    return DCoordinate3(a * (2.0 * u * cos(2*u) - cos(2*u))/ (2.0 * u * u),
                        a * (u * sin(2*u) - sin(u) * sin(u)) / u * u, 0);
}

DCoordinate3 cochleoid::d2(GLdouble u)
{
    return DCoordinate3(-1.0 * (a * (2.0 * u * u * sin(2*u) + 2.0 * u * cos(2*u) - sin(2*u))) / u * u * u,
                        (2.0 * a * (u * u * cos(2*u) - u * sin(2*u) + sin(u) * sin(u) )) / u * u * u, 0);
}

//torus knot
GLdouble torus_knot::u_min = -TWO_PI;
GLdouble torus_knot::u_max = +TWO_PI;
GLdouble torus_knot::r = 1.0;
GLdouble torus_knot::p = 4.0;
GLdouble torus_knot::q = 3.0;

DCoordinate3 torus_knot::d0(GLdouble u)
{
    GLdouble cp = cos(p * u), sp = sin(p * u), sq = sin(q * u);
    return DCoordinate3(r * cp, r * sp, -1.0 * sq);
}

DCoordinate3 torus_knot::d1(GLdouble u)
{
    GLdouble cp = cos(p * u), sp = sin(p * u), cq = cos(q * u);
    return DCoordinate3(-1.0 * r * p * sp,
                        r * p * cp,
                        -1.0 * cq * q);
}

DCoordinate3 torus_knot::d2(GLdouble u)
{
    GLdouble cp = cos(p * u), sp = sin(p * u), sq = sin(q * u);
    return DCoordinate3(-1.0 * r * (p * p) * cp,
                        -1.0 * r * (p * p) * sp,
                        (q * q) * sq);
}

//epicycloid

GLdouble epicycloid::u_min = -TWO_PI;
GLdouble epicycloid::u_max = +TWO_PI;
GLdouble epicycloid::k = 4.0;

DCoordinate3 epicycloid::d0(GLdouble u)
{
    return DCoordinate3((k+1) * cos(u) - cos((k + 1) * u), (k+1) * sin(u) - sin((k + 1) * u), 0.0);
}

DCoordinate3 epicycloid::d1(GLdouble u)
{
    return DCoordinate3(-(k+1) * sin(u) + (k + 1) * sin((k + 1) * u),  (k+1) * cos(u) - (k+1) * cos((k + 1) * u), 0.0);
}

DCoordinate3 epicycloid::d2(GLdouble u)
{
    return DCoordinate3(-(k+1) * cos(u) + (k + 1) * (k + 1) * cos((k + 1) * u), -(k+1) * sin(u) + (k+1)*(k+1)*sin((k + 1) * u), 0);
}

//hypocycloid

GLdouble hypocycloid::u_min = 0.0; //-TWO_PI;
GLdouble hypocycloid::u_max = +TWO_PI;
GLdouble hypocycloid::k = 6.0;
DCoordinate3 hypocycloid::d0(GLdouble u)
{
    return DCoordinate3((k-1) * cos(u) + cos((k - 1) * u), (k-1) * sin(u) - sin((k - 1) * u), 0.0);
}

DCoordinate3 hypocycloid::d1(GLdouble u)
{
    return DCoordinate3(-(k-1) * sin(u) - (k - 1) * sin((k - 1) * u),  (k-1) * cos(u) - (k-1) * cos((k - 1) * u), 0.0);
}

DCoordinate3 hypocycloid::d2(GLdouble u)
{
    return DCoordinate3(-(k-1) * cos(u) - (k - 1) * (k - 1) * cos((k - 1) * u), -(k-1) * sin(u) + (k-1)*(k-1)*sin((k - 1) * u), 0);
}

