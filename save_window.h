#ifndef SAVE_WINDOW_H
#define SAVE_WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFile>

class Save_window : public QWidget
{
    Q_OBJECT
public:
    explicit Save_window(QWidget *parent = nullptr);
    ~Save_window();

signals:
    void s_file_name (QString);


private:
    QLineEdit* input_line;
    QPushButton* accept_b;

private slots:
    void on_Accept_b_clicked();

};

#endif // SAVE_WINDOW_H
