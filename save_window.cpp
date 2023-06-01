#include "save_window.h"
#include <QGridLayout>
#include <QMessageBox>

Save_window::Save_window(QWidget *parent) : QWidget(parent)
{
    resize(250, 100);
    setWindowTitle("Сохранение");

    QGridLayout* layout = new QGridLayout(this);

    QLabel *text = new QLabel ("Введите имя файла", this);
    layout->addWidget(text, 0, 0, 1, 2);

    input_line = new QLineEdit(this);
    layout->addWidget(input_line, 1, 0, 1, 2);

    QLabel *d_text = new QLabel (".txt", this);
    layout->addWidget(d_text, 1, 3, 1, 1);

    accept_b = new QPushButton("Ok", this);
    connect(accept_b, &QPushButton::clicked, this, &Save_window::on_Accept_b_clicked);
    layout->addWidget(accept_b, 2, 2, 1, 1);
}

Save_window::~Save_window()
{

}

void Save_window::on_Accept_b_clicked()
{
    if (input_line->text() == ""){
        return;
    }
    QFile file;
    file.setFileName(input_line->text() + ".txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        file.close();
        QMessageBox* m_box = new QMessageBox (this);
        m_box->setWindowTitle("Warning!");
        m_box->setText("This name is already using"
                       "\nFile'll be rerecorded");
        m_box->setWindowModality(Qt::ApplicationModal);
        m_box->show();
        emit s_file_name(input_line->text() + ".txt");
    }else
        emit s_file_name(input_line->text() + ".txt");
    close();
}
