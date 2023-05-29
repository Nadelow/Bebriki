#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    resize(700, 600);

    QGridLayout* layout = new QGridLayout(this);
    text_pole_in = new QTextEdit(this);
    layout->addWidget(text_pole_in, 0, 0, 3, 2);

    QTextDocument* text = new QTextDocument();
    text_pole_in->setDocument(text);

    text_pole_out = new QTextBrowser(this);
    layout->addWidget(text_pole_out, 0, 3, 3, 2);

    go_b = new QPushButton("Перевод на\nassembler",this);
    go_b->setObjectName("Go_b");
    layout->addWidget(go_b, 4, 4, 1, 1);

    load_b = new QPushButton("Загрузить\nфайл",this);
    load_b->setObjectName("Load_b");
    layout->addWidget(load_b, 4, 0, 1, 1);

    save_b = new QPushButton("Сохранить\nфайл",this);
    save_b->setObjectName("Save_b");
    layout->addWidget(save_b, 4, 3, 1, 1);

    text_on_screen = new QLabel("", this);
    layout->addWidget(text_on_screen, 4, 1, 1, 1);

    setWindowTitle("Транслятор mini-basic -> assebmler");
    setWindowModality(Qt::ApplicationModal);
    //setAttribute(Qt::WA_DeleteOnClose, true);
    QMetaObject::connectSlotsByName(this);
}

void MainWindow::load_text(QString filename){
    text_pole_in->clear();
    m_filename = filename;
    file.setFileName(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream text_stream(&file);

        while (!text_stream.atEnd()){
            QString in_line = text_stream.readLine();
            //qDebug() << in_line;
            text_pole_in->append(in_line);
        }

        text_on_screen->setText("Открыт " + m_filename);

        file.close();
    }else{
        QErrorMessage* dialog = new QErrorMessage(this);
        dialog->setWindowModality(Qt::ApplicationModal);
        dialog->setWindowTitle("Ошибка!");
        dialog->showMessage("Неудалось найти указанный файл."
                            "Проверьте имя файла и попробуйте еще раз");
        //dialog->setWindowIcon(QMessageBox::Warning);
        dialog->show();
    }
}

void MainWindow::saving_file(QString file_name)
{
    QTextDocumentWriter writer;
    writer.setFormat("plaintext");
    writer.setFileName(file_name);
    writer.write(text_pole_in->document());
}

void MainWindow::on_Go_b_clicked(){ //файл будет в папке дебаггера
    //out_file.setFileName("input_in_tr.txt");

    QTextDocumentWriter writer;
    writer.setFormat("plaintext");
    writer.setFileName("input_in_tr.txt");
    writer.write(text_pole_in->document());

    Translator trans;
    trans.Translate("input_in_tr.txt");

    out_file.setFileName("out.txt");
    out_file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream text_stream(&out_file);
    text_pole_out->clear();

    while (!text_stream.atEnd()){
        QString in_line = text_stream.readLine();
        //qDebug() << in_line;
        text_pole_out->append(in_line);
    }

    out_file.close();
}

void MainWindow::on_Load_b_clicked()
{
    help_window = new Help_window();
    help_window->setWindowModality(Qt::ApplicationModal);
    connect(help_window, &Help_window::s_file_name_catched, this, &MainWindow::load_text);
    help_window->show();
}

void MainWindow::on_Save_b_clicked()
{
    QTextDocumentWriter writer;
    writer.setFormat("plaintext");
    if (m_filename!=""){
        writer.setFileName(m_filename);
        writer.write(text_pole_in->document());
    }else{
//        QInputDialog* dialog = new QInputDialog(this);
//        dialog->setWindowModality(Qt::ApplicationModal);
//        dialog->setWindowTitle("File name?");
//        dialog->setLabelText("Файл не был открыт. "
//                             "Введите имя для нового файла.");
//        dialog->show();

//        m_filename = dialog->textValue();
//        file.setFileName(m_filename);
//        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
//            writer.setFileName(m_filename);
//            writer.write(text_pole_in->document());
//            return;
//        }
//        dialog->setWindowTitle("");
//        dialog->setLabelText("Такой файл существует. "
//                                 "Перезаписать его?");
//        dialog->show();
//        if (dialog->result()){
//            writer.setFileName(m_filename);
//            writer.write(text_pole_in->document());
//        }else
//            m_filename = "";
//        return;
        Save_window* save_window = new Save_window ();
        save_window->setWindowModality(Qt::ApplicationModal);
        connect(save_window, &Save_window::s_file_name, this, &MainWindow::saving_file);
        save_window->show();
    }
}

MainWindow::~MainWindow()
{

}

