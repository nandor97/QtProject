/********************************************************************************
** Form generated from reading UI file 'SideWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEWIDGET_H
#define UI_SIDEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideWidget
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *rotate_x_slider;
    QLabel *label_2;
    QSlider *rotate_y_slider;
    QLabel *label_3;
    QSlider *rotate_z_slider;
    QLabel *label_4;
    QDoubleSpinBox *zoom_factor_spin_box;
    QLabel *label_5;
    QDoubleSpinBox *trans_x_spin_box;
    QLabel *label_6;
    QDoubleSpinBox *trans_y_spin_box;
    QLabel *label_7;
    QDoubleSpinBox *trans_z_spin_box;
    QComboBox *comboBox;
    QLabel *label_8;
    QComboBox *cb_shaders;
    QLabel *lb_shaderek;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBox_2;
    QDoubleSpinBox *doubleSpinBox_3;
    QLabel *lb_scale;
    QLabel *label_9;
    QLabel *label_10;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QStringLiteral("SideWidget"));
        SideWidget->resize(289, 355);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideWidget->sizePolicy().hasHeightForWidth());
        SideWidget->setSizePolicy(sizePolicy);
        SideWidget->setMinimumSize(QSize(269, 0));
        groupBox = new QGroupBox(SideWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 271, 261));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 21, 261, 236));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rotate_x_slider = new QSlider(layoutWidget);
        rotate_x_slider->setObjectName(QStringLiteral("rotate_x_slider"));
        rotate_x_slider->setMinimum(-180);
        rotate_x_slider->setMaximum(180);
        rotate_x_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, rotate_x_slider);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        rotate_y_slider = new QSlider(layoutWidget);
        rotate_y_slider->setObjectName(QStringLiteral("rotate_y_slider"));
        rotate_y_slider->setMinimum(-180);
        rotate_y_slider->setMaximum(180);
        rotate_y_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, rotate_y_slider);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rotate_z_slider = new QSlider(layoutWidget);
        rotate_z_slider->setObjectName(QStringLiteral("rotate_z_slider"));
        rotate_z_slider->setMinimum(-180);
        rotate_z_slider->setMaximum(180);
        rotate_z_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, rotate_z_slider);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        zoom_factor_spin_box = new QDoubleSpinBox(layoutWidget);
        zoom_factor_spin_box->setObjectName(QStringLiteral("zoom_factor_spin_box"));
        zoom_factor_spin_box->setDecimals(5);
        zoom_factor_spin_box->setMinimum(0.0001);
        zoom_factor_spin_box->setMaximum(10000);
        zoom_factor_spin_box->setSingleStep(0.1);
        zoom_factor_spin_box->setValue(1);

        formLayout->setWidget(3, QFormLayout::FieldRole, zoom_factor_spin_box);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        trans_x_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_x_spin_box->setObjectName(QStringLiteral("trans_x_spin_box"));
        trans_x_spin_box->setMinimum(-100);
        trans_x_spin_box->setMaximum(100);
        trans_x_spin_box->setSingleStep(0.1);

        formLayout->setWidget(4, QFormLayout::FieldRole, trans_x_spin_box);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        trans_y_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_y_spin_box->setObjectName(QStringLiteral("trans_y_spin_box"));
        trans_y_spin_box->setMinimum(-100);
        trans_y_spin_box->setMaximum(100);
        trans_y_spin_box->setSingleStep(0.1);

        formLayout->setWidget(5, QFormLayout::FieldRole, trans_y_spin_box);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        trans_z_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_z_spin_box->setObjectName(QStringLiteral("trans_z_spin_box"));
        trans_z_spin_box->setMinimum(-100);
        trans_z_spin_box->setMaximum(100);
        trans_z_spin_box->setSingleStep(0.1);

        formLayout->setWidget(6, QFormLayout::FieldRole, trans_z_spin_box);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        formLayout->setWidget(7, QFormLayout::FieldRole, comboBox);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_8);

        cb_shaders = new QComboBox(layoutWidget);
        cb_shaders->setObjectName(QStringLiteral("cb_shaders"));

        formLayout->setWidget(8, QFormLayout::FieldRole, cb_shaders);

        lb_shaderek = new QLabel(layoutWidget);
        lb_shaderek->setObjectName(QStringLiteral("lb_shaderek"));

        formLayout->setWidget(8, QFormLayout::LabelRole, lb_shaderek);

        doubleSpinBox = new QDoubleSpinBox(SideWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(100, 260, 171, 22));
        doubleSpinBox_2 = new QDoubleSpinBox(SideWidget);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(100, 290, 171, 22));
        doubleSpinBox_3 = new QDoubleSpinBox(SideWidget);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));
        doubleSpinBox_3->setGeometry(QRect(100, 320, 171, 22));
        lb_scale = new QLabel(SideWidget);
        lb_scale->setObjectName(QStringLiteral("lb_scale"));
        lb_scale->setGeometry(QRect(20, 260, 71, 16));
        label_9 = new QLabel(SideWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 290, 61, 16));
        label_10 = new QLabel(SideWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 320, 61, 16));
#ifndef QT_NO_SHORTCUT
        label->setBuddy(rotate_x_slider);
        label_2->setBuddy(rotate_y_slider);
        label_3->setBuddy(rotate_z_slider);
        label_4->setBuddy(zoom_factor_spin_box);
        label_5->setBuddy(trans_x_spin_box);
        label_6->setBuddy(trans_y_spin_box);
        label_7->setBuddy(trans_z_spin_box);
#endif // QT_NO_SHORTCUT

        retranslateUi(SideWidget);

        QMetaObject::connectSlotsByName(SideWidget);
    } // setupUi

    void retranslateUi(QWidget *SideWidget)
    {
        SideWidget->setWindowTitle(QApplication::translate("SideWidget", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("SideWidget", "Transformations", nullptr));
        label->setText(QApplication::translate("SideWidget", "Rotate around x", nullptr));
        label_2->setText(QApplication::translate("SideWidget", "Rotate around y", nullptr));
        label_3->setText(QApplication::translate("SideWidget", "Rotate around z", nullptr));
        label_4->setText(QApplication::translate("SideWidget", "Zoom factor", nullptr));
#ifndef QT_NO_TOOLTIP
        zoom_factor_spin_box->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("SideWidget", "Translate along x", nullptr));
        label_6->setText(QApplication::translate("SideWidget", "Translate along y", nullptr));
        label_7->setText(QApplication::translate("SideWidget", "Translate along z", nullptr));
        label_8->setText(QApplication::translate("SideWidget", "gorbek", nullptr));
        lb_shaderek->setText(QApplication::translate("SideWidget", "shaderek", nullptr));
        lb_scale->setText(QApplication::translate("SideWidget", "Scale factor:", nullptr));
        label_9->setText(QApplication::translate("SideWidget", "Smoothing:", nullptr));
        label_10->setText(QApplication::translate("SideWidget", "Shading:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H
