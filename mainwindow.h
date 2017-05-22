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

    void on_spinBoxNumNeur_valueChanged(int arg1);//изменить размеры таблиц по кол-ву нейронов

    void on_pushButtonStart_clicked();//запустить всё (мб в дальнейшем разделить вычисления и построения)

private:
    void setDefaults();//установить параметры по умолчанию
    void set();//установить параметры
    void get();//получить параметры
    void write(QJsonObject &json) const;//записать параметры в объект json
    void read(const QJsonObject &json);//считать параметры из объекта json

    void calcX();
    void calcU();
    void calcI();
    void calcK();
    void calcP();
    void calcG();

    void calc();//вычислить всё
    void print();//вывести таблицы
    void plot();//построить графики (мб потом отдельно каждый)

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

    QVector<double> W_;//константные значения
    QVector<double> A_;//константные (конечные) значения
    QVector<double> K_;//задается 0-е значение
    QVector<double> U_;//задается 0-е значение
    QVector<QVector<double>> X_;//задается 0-й слой
};
//QSettings
//QCustomPlot::rescaleAxes - вместо setRange

#endif // MAINWINDOW_H
