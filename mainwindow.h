#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include "Translator.h"
#include "help_window.h"
#include "save_window.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Go_b_clicked();
    void on_Load_b_clicked();
    void on_Save_b_clicked();
    void load_text(QString filename);
    void saving_file(QString);

signals:
    void s_file_name_catched(QString);

private:
    QTextEdit* text_pole_in;
    QTextBrowser* text_pole_out;
    QPushButton* go_b;
    QPushButton* load_b;
    QPushButton* save_b;
    QLabel* text_on_screen;
    Help_window* help_window;
    QFile file;
    QFile out_file;
    QFile ready_code_file;
    QString m_filename;
};
#endif // MAINWINDOW_H
