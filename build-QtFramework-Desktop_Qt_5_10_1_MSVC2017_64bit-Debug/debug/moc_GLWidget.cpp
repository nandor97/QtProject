/****************************************************************************
** Meta object code from reading C++ file 'GLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtFramework/GUI/GLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cagd__GLWidget_t {
    QByteArrayData data[14];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cagd__GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cagd__GLWidget_t qt_meta_stringdata_cagd__GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "cagd::GLWidget"
QT_MOC_LITERAL(1, 15, 11), // "set_angle_x"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "value"
QT_MOC_LITERAL(4, 34, 11), // "set_angle_y"
QT_MOC_LITERAL(5, 46, 11), // "set_angle_z"
QT_MOC_LITERAL(6, 58, 15), // "set_zoom_factor"
QT_MOC_LITERAL(7, 74, 11), // "set_trans_x"
QT_MOC_LITERAL(8, 86, 11), // "set_trans_y"
QT_MOC_LITERAL(9, 98, 11), // "set_trans_z"
QT_MOC_LITERAL(10, 110, 12), // "set_pc_index"
QT_MOC_LITERAL(11, 123, 8), // "_animate"
QT_MOC_LITERAL(12, 132, 16), // "set_shader_index"
QT_MOC_LITERAL(13, 149, 1) // "i"

    },
    "cagd::GLWidget\0set_angle_x\0\0value\0"
    "set_angle_y\0set_angle_z\0set_zoom_factor\0"
    "set_trans_x\0set_trans_y\0set_trans_z\0"
    "set_pc_index\0_animate\0set_shader_index\0"
    "i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cagd__GLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       5,    1,   70,    2, 0x0a /* Public */,
       6,    1,   73,    2, 0x0a /* Public */,
       7,    1,   76,    2, 0x0a /* Public */,
       8,    1,   79,    2, 0x0a /* Public */,
       9,    1,   82,    2, 0x0a /* Public */,
      10,    1,   85,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    1,   89,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void cagd::GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLWidget *_t = static_cast<GLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_angle_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->set_angle_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->set_angle_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->set_zoom_factor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->set_trans_x((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->set_trans_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->set_trans_z((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->set_pc_index((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->_animate(); break;
        case 9: _t->set_shader_index((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject cagd::GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_cagd__GLWidget.data,
      qt_meta_data_cagd__GLWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *cagd::GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cagd::GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cagd__GLWidget.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int cagd::GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
