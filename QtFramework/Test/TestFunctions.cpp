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

//paramtric surafaces
//spheroid
GLdouble spheroid::u_min = 0.0 + EPS;
GLdouble spheroid::u_max = +PI - EPS;
GLdouble spheroid::v_min = 0.0;
GLdouble spheroid::v_max = +TWO_PI;
GLdouble spheroid::a = 0.5;
GLdouble spheroid::b = 1.5;

DCoordinate3 spheroid::d00(GLdouble u, GLdouble v)
{
    GLdouble x = a * sin(u) * sin(v);
    GLdouble y = a * sin(u) * cos(v);
    GLdouble z = b * cos(u);
    return DCoordinate3(x, y, z);
}

DCoordinate3 spheroid::d10(GLdouble u, GLdouble v)
{
    GLdouble x = a * cos(u) * sin(v);
    GLdouble y = a * cos(u) * cos(v);
    GLdouble z = -b * sin(u);
    return DCoordinate3(x, y, z);
}

DCoordinate3 spheroid::d01(GLdouble u, GLdouble v)
{
    GLdouble x = a * sin(u) * cos(v);
    GLdouble y =  -a * sin(u) * sin(v);
    GLdouble z = 0.0;
    return DCoordinate3(x, y, z);
}

//conchoid
GLdouble conchoid::u_min = -TWO_PI;
GLdouble conchoid::u_max = +TWO_PI;
GLdouble conchoid::v_min = -TWO_PI;
GLdouble conchoid::v_max = +TWO_PI;
DCoordinate3 conchoid::d00(GLdouble u, GLdouble v)
{
    GLdouble x = pow(1.2, u) * (1 + cos(v)) * sin(u);
    GLdouble y = pow(1.2, u) * (1 + cos(v)) * cos(u);
    GLdouble z = pow(1.2, u) * sin(v) - 1.5 * pow(1.2, u);
    return DCoordinate3(x, y, z);
}

DCoordinate3 conchoid::d10(GLdouble u, GLdouble v)
{
    GLdouble x = pow(1.2, u) * (cos(v) + 1) * (0.182322 * sin(u) + cos(u));
    GLdouble y = pow(1.2, u) * (cos(v) + 1) * (0.182322 * cos(u) - sin(u));
    GLdouble z = pow(1.2, u) * (0.182322 * sin(v) - 0.273482);
    return DCoordinate3(x, y, z);
}

DCoordinate3 conchoid::d01(GLdouble u, GLdouble v)
{
    GLdouble x = -pow(1.2, u) * sin(u) * sin(v);
    GLdouble y = -pow(1.2, u) * cos(u) * sin(v);
    GLdouble z = pow(1.2, u) * cos(v);
    return DCoordinate3(x, y, z);
}
//elliptic_torus
GLdouble elliptic_torus::u_min = 0.0;
GLdouble elliptic_torus::u_max = +TWO_PI;
GLdouble elliptic_torus::v_min = 0.0;
GLdouble elliptic_torus::v_max = +TWO_PI;
GLdouble elliptic_torus::a = 1.5;
GLdouble elliptic_torus::b = 0.5;
GLdouble elliptic_torus::c = 1.0;

DCoordinate3 elliptic_torus::d00(GLdouble u, GLdouble v)
{
    GLdouble x = (c + a * cos(v)) * cos(u);
    GLdouble y = (c + a * cos(v)) * sin(u);
    GLdouble z = b * sin(v);
    return DCoordinate3(x, y, z);
}

DCoordinate3 elliptic_torus::d10(GLdouble u, GLdouble v)
{
    GLdouble x = -(c + a * cos(v)) * sin(u);
    GLdouble y = (c + a * cos(v)) * cos(u);
    GLdouble z = b * cos(u);
    return DCoordinate3(x, y, z);
}

DCoordinate3 elliptic_torus::d01(GLdouble u, GLdouble v)
{
    GLdouble x = -a * sin(v) * cos(u);
    GLdouble y = -a * sin(v) * sin(u);
    GLdouble z = 0.0;
    return DCoordinate3(x, y, z);
}

//astroidal surface
GLdouble astroidal::u_min = -PI/2;
GLdouble astroidal::u_max = +PI/2;
GLdouble astroidal::v_min = -PI;
GLdouble astroidal::v_max = +PI;
DCoordinate3 astroidal::d00(GLdouble u, GLdouble v)
{
    GLdouble x = cos(u) * cos(u) * cos(u) * cos(v) * cos(v) * cos(v);
    GLdouble y = sin(u) * sin(u) * sin(u) * cos(v) * cos(v) * cos(v);
    GLdouble z = sin(v) * sin(v) * sin(v);
    return DCoordinate3(x, y, z);
}

DCoordinate3 astroidal::d10(GLdouble u, GLdouble v)
{
    GLdouble x = -3 * cos(u) * cos(u) * sin(u) * cos(v) * cos(v) * cos(v);
    GLdouble y = 3 * sin(u) * sin(u) * cos(u) * cos(v) * cos(v) * cos(v);
    GLdouble z = 0.0;
    return DCoordinate3(x, y, z);
}

DCoordinate3 astroidal::d01(GLdouble u, GLdouble v)
{
    GLdouble x = -3 * cos(u) * cos(u) * cos(u) * cos(v) * cos(v) * sin(v);
    GLdouble y = sin(u) * sin(u) * sin(u) * 3 * cos(v) * cos(v) * sin(v);
    GLdouble z = 3 * cos(v) * sin(v) * sin(v);
    return DCoordinate3(x, y, z);
}

//sine surface
GLdouble sine_surface::u_min = -TWO_PI;
GLdouble sine_surface::u_max = +TWO_PI;
GLdouble sine_surface::v_min = -TWO_PI;
GLdouble sine_surface::v_max = +TWO_PI;
GLdouble sine_surface::a = 0.5;
DCoordinate3 sine_surface::d00(GLdouble u, GLdouble v)
{
    GLdouble x = a * sin(u);
    GLdouble y = a * sin(v);
    GLdouble z = a * sin(u+v);
    return DCoordinate3(x, y, z);
}

DCoordinate3 sine_surface::d10(GLdouble u, GLdouble v)
{
    GLdouble x = a * cos(u);
    GLdouble y = 0;
    GLdouble z = a * cos(u + v);
    return DCoordinate3(x, y, z);
}

DCoordinate3 sine_surface::d01(GLdouble u, GLdouble v)
{
    GLdouble x = 0;
    GLdouble y = a * cos(v);
    GLdouble z = a * cos(u + v);
    return DCoordinate3(x, y, z);
}
