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
    /**
     * @brief Функция нажатия на кнопку перевода
     */
    void on_Go_b_clicked();
    /**
     * @brief Функция нажатия на кнопку загрузки файла
     */
    void on_Load_b_clicked();
    /**
     * @brief Функция нажатия на кнопку сохранения файла
     */
    void on_Save_b_clicked();
    /**
     * @brief Функция-слот загрузки текста из файла
     */
    void load_text(QString filename);
    /**
     * @brief Функция-стол сохранения файла
     */
    void saving_file(QString);

private:
    /**
     * @brief Поле текстового редактора
     */
    QTextEdit* text_pole_in;
    /**
     * @brief Поле вывода результата трансляции
     */
    QTextBrowser* text_pole_out;
    /**
     * @brief Кнопка запуска транслятора
     */
    QPushButton* go_b;
    /**
     * @brief Кнопка загрузки файла
     */
    QPushButton* load_b;
    /**
     * @brief Кнопка сохранения файла
     */
    QPushButton* save_b;
    /**
     * @brief Текст в окне транслятора
     */
    QLabel* text_on_screen;
    /**
     * @brief Вспомогательное окно
     */
    Help_window* help_window;
    /**
     * @brief Переменная исходного файла
     */
    QFile file;
    /**
     * @brief Переменная выходного файла
     */
    QFile out_file;
    /**
     * @brief Переменная памяти для имени файла
     */
    QString m_filename;
};
#endif // MAINWINDOW_H
