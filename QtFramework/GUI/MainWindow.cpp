#include "MainWindow.h"

namespace cagd
{
    MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    {
        setupUi(this);

    /*

      the structure of the main window's central widget

     *---------------------------------------------------*
     |                 central widget                    |
     |                                                   |
     |  *---------------------------*-----------------*  |
     |  |     rendering context     |   scroll area   |  |
     |  |       OpenGL widget       | *-------------* |  |
     |  |                           | | side widget | |  |
     |  |                           | |             | |  |
     |  |                           | |             | |  |
     |  |                           | *-------------* |  |
     |  *---------------------------*-----------------*  |
     |                                                   |
     *---------------------------------------------------*

    */
        _side_widget = new SideWidget(this);

        _scroll_area = new QScrollArea(this);
        _scroll_area->setWidget(_side_widget);
        _scroll_area->setSizePolicy(_side_widget->sizePolicy());
        _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        _gl_widget = new GLWidget(this);

        centralWidget()->setLayout(new QHBoxLayout());
        centralWidget()->layout()->addWidget(_gl_widget);
        centralWidget()->layout()->addWidget(_scroll_area);

        // creating a signal slot mechanism between the rendering context and the side widget
        connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
        connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
        connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

        connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

        connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
        connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
        connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));

        connect(_side_widget->comboBox, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_pc_index(int)));
        connect(_side_widget->cb_shaders, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_shader_index(int)));

        connect(_side_widget->scale, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_scale(double)));
        connect(_side_widget->smoothing, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_smoothing(double)));
        connect(_side_widget->shading, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_shading(double)));

        connect(_side_widget->red, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_red(double)));
        connect(_side_widget->blue, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_blue(double)));
        connect(_side_widget->green, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_green(double)));
        connect(_side_widget->alpha, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_alpha_color(double)));

    }

    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}
