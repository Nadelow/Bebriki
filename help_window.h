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
    /**
     * @brief Функция нажатия на кнопку принятия
     */
    void on_Apply_b_clicked();

signals:
    /**
     * @brief Сигнал отправки имени файла
     */
    void s_file_name_catched(QString);

private:
    /**
     * @brief Кнопка принятия
     */
    QPushButton* apply_b;

    /**
     * @brief Строка для ввода имени
     */
    QLineEdit* input_line;

    /**
     * @brief Текст окна
     */
    QLabel* text_on_window;
};

#endif // HELP_WINDOW_H
