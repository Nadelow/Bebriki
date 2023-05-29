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
    /**
     * @brief Сигнал отправки имени
     */
    void s_file_name (QString);


private:
    /**
     * @brief Строка ввода
     */
    QLineEdit* input_line;

    /**
     * @brief Кнопка принятия
     */
    QPushButton* accept_b;

private slots:
    /**
     * @brief Функция нажатия на кнопку принятия
     */
    void on_Accept_b_clicked();

};

#endif // SAVE_WINDOW_H
