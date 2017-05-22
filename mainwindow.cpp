#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Oscillatory Neural Network");
    setDefaults();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{
    QMessageBox::information(this, "test", "triggering save button", QMessageBox::Ok);
    QFile fsave(QStringLiteral("def.json"));
    if(!fsave.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open file.");
        return;
    }
    QJsonObject json;
    get();
    write(json);
    QJsonDocument doc(json);
    fsave.write(doc.toJson());
    fsave.close();
}

void MainWindow::on_actionLoad_triggered()
{
    QMessageBox::information(this, "test", "triggering load button", QMessageBox::Ok);
}

void MainWindow::setDefaults()
{

}

void MainWindow::set()
{

}

void MainWindow::get()
{
    numNeur_ = ui->spinBoxNumNeur->value();//auto update when changing?
    numLay_ = ui->spinBoxNumLay->value();
    time_ = ui->lineEditTime->text().toDouble();
    limit_ = ui->lineEditLimit->text().toDouble();
    M1_ = ui->lineEditM1->text().toDouble();
    M2_ = ui->labelM2->text().toDouble();
    step_ = ui->lineEditStep->text().toDouble();
    accur_ = ui->lineEditAccur->text().toDouble();
}

void MainWindow::write(QJsonObject &json) const
{
    json["num_neur"] = numNeur_;
    json["num_lay"] = numLay_;
    json["time"] = time_;
    json["limit"] = limit_;
    json["m1"] = M1_;
    json["m2"] = M2_;
    json["step"] = step_;
    json["accur"] = accur_;
}

void MainWindow::read(const QJsonObject &json)
{
    numNeur_ = json["num_neur"].toInt();
    numLay_ = json["num_lay"].toInt();
    time_ = json["time"].toDouble();
    limit_ = json["limit"].toDouble();
    M1_ = json["m1"].toDouble();
    M2_ = json["m2"].toDouble();
    step_ = json["step"].toDouble();
    accur_ = json["accur"].toDouble();
}
