#include "QuarticAlgebraicTrigonometricPatches.h"

using namespace cagd;

QuarticAlgebraicTrigonometricPatch::QuarticAlgebraicTrigonometricPatch(GLdouble alpha):TensorProductSurface3(0.0, alpha,0.0, alpha, 4.4)
{
	this->alpha = alpha;
}

GLboolean QuarticAlgebraicTrigonometricPatch::UBlendingFunctionValues(GLdouble u_knot, RowMatrix<GLdouble>&blending_values) const
{
    if(u_knot < 0.0 || u_knot > alpha)
        return GL_FALSE;

    blending_values.ResizeColumns(4);

    blending_values(0) = F3(alpha - u_knot);
    blending_values(1) = F2(alpha - u_knot);
    blending_values(2) = F2(u_knot);
    blending_values(3) = F3(u_knot);
    return GL_TRUE;
}
GLboolean QuarticAlgebraicTrigonometricPatch::VBlendingFunctionValues(GLdouble v_knot, RowMatrix<GLdouble>&blending_values) const
{
    if(v_knot < 0.0 || v_knot > alpha)
        return GL_FALSE;

    blending_values.ResizeColumns(4);

    //beallitani a blending_values-kat
    blending_values(0) = F3(alpha - v_knot);
    blending_values(1) = F2(alpha - v_knot);
    blending_values(2) = F2(v_knot);
    blending_values(3) = F3(v_knot);
    return GL_TRUE;
}
GLboolean QuarticAlgebraicTrigonometricPatch::CalculatePartialDerivatives(GLuint maximum_order_of_partial_derivatives, GLdouble u, GLdouble v, PartialDerivatives &pd) const
{
    if(u < 0.0 || u > alpha || v < 0.0 || v > alpha || maximum_order_of_partial_derivatives > 1)
        return GL_FALSE;
    //blending functions values and their derivatives in u_direction
    RowMatrix<GLdouble> u_blending_values(4), d1_u_blending_values(4);

    u_blending_values(0) = F3(alpha - u);
    u_blending_values(1) = F2(alpha - u);
    u_blending_values(2) = F2(u);
    u_blending_values(3) = F3(u);

    d1_u_blending_values(0) = dF3(alpha - u) * (-1);
    d1_u_blending_values(1) = dF2(alpha - u) * (-1);
    d1_u_blending_values(2) = dF2(u);
    d1_u_blending_values(3) = dF3(u);

    //blending function values and their derivatives in v-direction
    RowMatrix<GLdouble> v_blending_values(4), d1_v_blending_values(4);

    v_blending_values(0) = F3(alpha - v);
    v_blending_values(1) = F2(alpha - v);
    v_blending_values(2) = F2(v);
    v_blending_values(3) = F3(v);

    d1_v_blending_values(0) = dF3(alpha - v) * (-1);
    d1_v_blending_values(1) = dF2(alpha - v) * (-1);
    d1_v_blending_values(2) = dF2(v);
    d1_v_blending_values(3) = dF3(v);

    pd.ResizeRows(2);
    pd.LoadNullVectors();

    for(GLuint row = 0; row < 4; ++row)
    {
        DCoordinate3 aux_d0_v, aux_d1_v;
        for(GLuint column = 0; column < 4; ++column)
        {
            aux_d0_v += _data(row,column) * v_blending_values(column);
            aux_d1_v += _data(row,column) * d1_v_blending_values(column);
        }
        pd(0,0) += aux_d0_v * u_blending_values(row); //surface point
        pd(1,0) += aux_d0_v * d1_u_blending_values(row); //first order u-directional partial derivative
        pd(1,1) += aux_d1_v * u_blending_values(row); //first order v-directional partial derivative
    }

    return GL_TRUE;
}
