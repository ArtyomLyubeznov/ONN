#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSave_triggered();//сохранить параметры в json-файл
    void on_actionLoad_triggered();//загрузить параметры из json-файла

private:
    void setDefaults();//установить параметры по умолчанию
    void set();//установить параметры
    void get();//получить параметры
    void write(QJsonObject &json) const;//записать параметры в объект json
    void read(const QJsonObject &json);//считать параметры из объекта json

private:
    Ui::MainWindow *ui;

    int numNeur_; // число нейронов
    int numLay_;  // число слоев
    double time_; // время процесса
    double limit_;// ограничения на управления
    double M1_;   // штрафные коэффициенты
    double M2_;   // штрафные коэффициенты
    double step_; // шаг градиен. спуска
    double accur_;// точность

    double dt_;// dt = T/q
    int iter_; // итерация
};

#endif // MAINWINDOW_H
