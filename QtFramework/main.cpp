#include <QApplication>
#include "GUI/MainWindow.h"
#include "Core/Matrices.h"
#include "Core/RealSquareMatrices.h"

#include <iostream>
#include <fstream>

using namespace cagd;
using namespace std;

int main(int argc, char **argv)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);

    // creating an application object and setting one of its attributes
    QApplication app(argc, argv);

    // if you have installed a different version of Qt, it may happen that
    // the application attribute Qt::AA_UseDesktopOpenGL is not recognized
    // on Windows its existence is critical for our applications
    // on Linux or Mac you can uncomment this line
    app.setAttribute(Qt::AA_UseDesktopOpenGL, true);

    // creating a main window object
    MainWindow mwnd;
    mwnd.showMaximized();

    //---------------------
    //Kovetkezik a teszteles
    //---------------------


//---------------------------------------------
//                 LAB 1
//---------------------------------------------
/*
    Matrix<int> M(3, 5);
    cout << M << endl;

    for (GLuint i = 0; i < M.GetRowCount(); ++i)
    {
        for (GLuint j = 0; j < M.GetColumnCount(); ++j)
        {
            M(i,j) = i*M.GetColumnCount() + j;
        }
    }
    fstream f("log.txt", ios_base::out);
    f << M << endl;
    f.close();

    Matrix<int> N;
    fstream g("log.txt", ios_base::in);
    g >> N;
    g.close();
    cout << N << endl;

    N.ResizeRows(7);
    N(6, 4) = -1;
    cout << N << endl << endl;

    RealSquareMatrix A(3);
    A(0, 0) =      A(0, 1) =       A(0, 2) = 1.0;
    A(1, 0) = 3.0; A(1, 1) = -2.0; A(1, 2) = 1.0;
    A(2, 0) = 2.0; A(2, 1) = 5.0;  A(2, 2) = 7.0;
    ColumnMatrix<GLdouble> b(3);
    b[0] = -2.0; b[1] = -7.0; b[2] = -11;
    ColumnMatrix<GLdouble> x;
    A.SolveLinearSystem(b, x);
    cout << x << endl;  //3 1
                        //-1
                        //1
                        //-2

    cout << "------------------" << endl << "TRIANGULAR MATRIX" << endl << "------------------" << endl << endl;

    TriangularMatrix<int> TM(3);
    cout << TM << endl;

    for (GLuint i = 0; i < M.GetRowCount(); ++i)
    {
        for (GLuint j = 0; j <= i; ++j)
        {
            TM(i,j) = i*M.GetColumnCount() + j;
        }
    }
    cout << TM << endl;

    TM.ResizeRows(5);
    cout << TM << endl;

    Matrix<int> m(2, 2);
    m(0, 0) = 4;
    m(0, 1) = 3;
    m(1, 0) = 2;
    m(1, 1) = 1;
    cout << m << endl;
    m.ResizeColumns(5);
    cout << m << endl;
*/


//---------------------------------------------------
//                LAB 2
//---------------------------------------------------




    // running the application
    return app.exec();
}
