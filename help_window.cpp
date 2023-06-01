#include "help_window.h"

Help_window::Help_window(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Загрузка файла");
    setMinimumSize(300, 75);
    setMaximumSize(300, 75);
    QGridLayout* layout = new QGridLayout(this);
    //------------------------------------------------------
    apply_b = new QPushButton("Загрузить", this);
    layout->addWidget(apply_b, 1, 3, 1, 1);
    apply_b->setObjectName("Apply_b");

    //------------------------------------------------------
    input_line = new QLineEdit(this);
    layout->addWidget(input_line, 1, 0, 1, 3);
    input_line->setObjectName("Input_line");
    input_line->setText("");

    //------------------------------------------------------
    text_on_window = new QLabel(this);
    text_on_window->setText("Введите имя файла в каталоге программы\nили полный путь к файлу");
    layout->addWidget(text_on_window, 0, 0, 1, 4);

    //------------------------------------------------------
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose, true);
    QMetaObject::connectSlotsByName(this);
}

void Help_window::on_Apply_b_clicked(){
    QString name;
    name = input_line->text();
    emit s_file_name_catched(name);
    close();
}

Help_window::~Help_window()
{
    close();
}
