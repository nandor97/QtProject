#pragma once

#include <cmath>
#include <GL/glew.h>
#include <iostream>

namespace cagd
{
    //-------------------
    // class DCoordinate3
    //-------------------
    class DCoordinate3
    {
    private:
        GLdouble _data[3];

    public:

        // default constructor
        DCoordinate3();

        // special constructor
        DCoordinate3(GLdouble x, GLdouble y, GLdouble z = 0.0);

        // get components by value
        GLdouble operator [](GLuint index) const;
        GLdouble x() const;
        GLdouble y() const;
        GLdouble z() const;


        // get components by reference
        GLdouble& operator [](GLuint index);
        GLdouble& x();
        GLdouble& y();
        GLdouble& z();

        // change sign
        const DCoordinate3 operator +() const;
        const DCoordinate3 operator -() const;

        // add
        const DCoordinate3 operator +(const DCoordinate3& rhs) const;

        // add to *this
        DCoordinate3& operator +=(const DCoordinate3& rhs);

        // subtract
        const DCoordinate3 operator -(const DCoordinate3& rhs) const;

        // subtract from *this
        DCoordinate3& operator -=(const DCoordinate3& rhs);

        // cross product
        const DCoordinate3 operator ^(const DCoordinate3& rhs) const;

        // cross product, result is stored by *this
        DCoordinate3& operator ^=(const DCoordinate3& rhs);

        // dot product
        GLdouble operator *(const DCoordinate3& rhs) const;

        // scale
        const DCoordinate3 operator *(const GLdouble& rhs) const;
        const DCoordinate3 operator /(const GLdouble& rhs) const;

        // scale *this
        DCoordinate3& operator *=(const GLdouble& rhs);
        DCoordinate3& operator /=(const GLdouble& rhs);

        // length
        GLdouble length() const;

        // normalize
        DCoordinate3& normalize();

        // logical operators
        GLboolean operator !=(const GLdouble& rhs) const;
    };

    //-------------------------------------
    // implementation of class DCoordinate3
    //-------------------------------------

    // default constructor
    inline DCoordinate3::DCoordinate3()
    {
        _data[0] = _data[1] = _data[2] = 0.0;
    }

    // special constructor
    inline DCoordinate3::DCoordinate3(GLdouble x, GLdouble y, GLdouble z)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
    }

    // get components by value
    inline GLdouble DCoordinate3::operator [](GLuint index) const
    {
        return _data[index];
    }

    inline GLdouble DCoordinate3::x() const
    {
        return _data[0];
    }

    inline GLdouble DCoordinate3::y() const
    {
        // homework
        return _data[1];
        //done
    }

    inline GLdouble DCoordinate3::z() const
    {
        // homework
        return _data[2];
        //done
    }

    // get components by reference
    inline GLdouble& DCoordinate3::operator [](GLuint index)
    {
        return _data[index];
    }

    inline GLdouble& DCoordinate3::x()
    {
        return _data[0];
    }

    inline GLdouble& DCoordinate3::y()
    {
        // homework
        return _data[1];
        //done
    }

    inline GLdouble& DCoordinate3::z()
    {
        // homework
        return _data[2];
        //done
    }

    // change sign
    inline const DCoordinate3 DCoordinate3::operator +() const
    {
        return DCoordinate3(_data[0], _data[1], _data[2]);
    }

    inline const DCoordinate3 DCoordinate3::operator -() const
    {
        return DCoordinate3(-_data[0], -_data[1], -_data[2]);
    }

    // add
    inline const DCoordinate3 DCoordinate3::operator +(const DCoordinate3& rhs) const
    {
        return DCoordinate3(_data[0] + rhs._data[0], _data[1] + rhs._data[1], _data[2] + rhs._data[2]);
    }

    // add to *this
    inline DCoordinate3& DCoordinate3::operator +=(const DCoordinate3& rhs)
    {
        _data[0] += rhs._data[0];
        _data[1] += rhs._data[1];
        _data[2] += rhs._data[2];
        return *this;
    }

    // subtract
    inline const DCoordinate3 DCoordinate3::operator -(const DCoordinate3& rhs) const
    {
        // homework
        return DCoordinate3(_data[0] - rhs._data[0], _data[1] - rhs._data[1], _data[2] - rhs._data[2]);
        //done
    }

    // subtract from *this
    inline DCoordinate3& DCoordinate3::operator -=(const DCoordinate3& rhs)
    {
        //homework
        _data[0] -= rhs._data[0];
        _data[1] -= rhs._data[1];
        _data[2] -= rhs._data[2];
        return *this;
        //done
    }

    // cross product
    inline const DCoordinate3 DCoordinate3::operator ^(const DCoordinate3& rhs) const
    {
        return DCoordinate3(
                _data[1] * rhs._data[2] - _data[2] * rhs._data[1],
                _data[2] * rhs._data[0] - _data[0] * rhs._data[2],
                _data[0] * rhs._data[1] - _data[1] * rhs._data[0]);
    }

    // cross product, result is stored by *this
    inline DCoordinate3& DCoordinate3::operator ^=(const DCoordinate3& rhs)
    {
        // homework
        GLdouble h0, h1, h2;
        h0 = _data[1] * rhs._data[2] - _data[2] * rhs._data[1];
        h1 = _data[2] * rhs._data[0] - _data[0] * rhs._data[2];
        h2 = _data[0] * rhs._data[1] - _data[1] * rhs._data[0];
        _data[0] = h0;
        _data[1] = h1;
        _data[2] = h2;
        return *this;
        //done
    }

    // dot product
    inline GLdouble DCoordinate3::operator *(const DCoordinate3& rhs) const
    {
        return _data[0] * rhs._data[0] + _data[1] * rhs._data[1] + _data[2] * rhs._data[2];
    }

    // scale
    inline const DCoordinate3 DCoordinate3::operator *(const GLdouble& rhs) const
    {
        return DCoordinate3(_data[0] * rhs, _data[1] * rhs, _data[2] * rhs);
    }

    inline const DCoordinate3 operator *(const GLdouble& lhs, const DCoordinate3& rhs)
    {
        // homework
        return DCoordinate3(lhs * rhs[0], lhs * rhs[1], lhs * rhs[2]);
        //done
    }

    inline const DCoordinate3 DCoordinate3::operator /(const GLdouble& rhs) const
    {
        // homework
        return DCoordinate3(_data[0] / rhs, _data[1] / rhs, _data[2] / rhs);
        //done
    }

    // scale *this
    inline DCoordinate3& DCoordinate3::operator *=(const GLdouble& rhs)
    {
        _data[0] *= rhs;
        _data[1] *= rhs;
        _data[2] *= rhs;

        return *this;
    }

    inline DCoordinate3& DCoordinate3::operator /=(const GLdouble& rhs)
    {
        // homework
        _data[0] /= rhs;
        _data[1] /= rhs;
        _data[2] /= rhs;

        return *this;
        //done
    }

    // length
    inline GLdouble DCoordinate3::length() const
    {
        return std::sqrt((*this) * (*this));
    }

    // normalize
    inline DCoordinate3& DCoordinate3::normalize()
    {
        GLdouble l = length();

        if (l && l != 1.0)
            *this /= l;

        return *this;
    }

    // logical operators
    inline GLboolean DCoordinate3::operator !=(const GLdouble& rhs) const
    {
        return (_data[0] != rhs || _data[1] != rhs || _data[2] != rhs);
    }

    //----------------------------------------------------------------
    // definitions of overloaded input/output from/to stream operators
    //----------------------------------------------------------------

    // output to stream
    inline std::ostream& operator <<(std::ostream& lhs, const DCoordinate3& rhs)
    {
        return lhs << rhs[0] << " " << rhs[1] << " " << rhs[2];
    }

    // input from stream
    inline std::istream& operator >>(std::istream& lhs, DCoordinate3& rhs)
    {
        // homework
        return lhs >> rhs[0] >> rhs[1] >> rhs[2];
        //done
    }
}
