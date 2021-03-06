#include "SideWidget.h"

namespace cagd
{
    SideWidget::SideWidget(QWidget *parent): QWidget(parent)
    {
        setupUi(this);

        QPalette p = rotate_x_slider->palette();

        p.setColor(QPalette::Highlight, QColor(255,50,10).lighter());

        rotate_x_slider->setPalette(p);

        p = rotate_y_slider->palette();

        p.setColor(QPalette::Highlight, QColor(50,255,10).lighter());

        rotate_y_slider->setPalette(p);

        comboBox->addItem("spiral on cone");
        comboBox->addItem("cochleoid");
        comboBox->addItem("torus know");
        comboBox->addItem("ellipse");
        comboBox->addItem("epicycloid");
        comboBox->addItem("hypocycloid");
        comboBox->addItem("cyclic curve");
        comboBox->addItem("interpolating cyclic curve");
        comboBox->addItem("Eger");
        comboBox->addItem("Elefant");
        comboBox->addItem("Spheroid");
        comboBox->addItem("Conchoid");
        comboBox->addItem("Elliptic torus");
        comboBox->addItem("Astroidal");
        comboBox->addItem("Sine surface");
        comboBox->addItem("Patch");

        cb_shaders->addItem("Nothing");
        cb_shaders->addItem("Reflection lines");
        cb_shaders->addItem("Directional light");
        cb_shaders->addItem("Toon");
        cb_shaders->addItem("Two sided lighting");
    }
}
