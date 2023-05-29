#ifndef HELP_WINDOW_H
#define HELP_WINDOW_H

#include <QtWidgets>

class Help_window : public QWidget
{
    Q_OBJECT
public:
    Help_window(QWidget *parent = nullptr);
    ~Help_window();

private slots:
    //------------------------------------------------------------------------------
    // Методы кнопок
    //------------------------------------------------------------------------------
    void on_Apply_b_clicked();

signals:
    void s_file_name_catched(QString);

private:
    //------------------------------------------------------------------------------
    //Элементы окна и программы
    //------------------------------------------------------------------------------
    QPushButton* apply_b;
    QLineEdit* input_line;
    QLabel* text_on_window;
};

#endif // HELP_WINDOW_H
