#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Oscillatory Neural Network");
    setWindowIcon(QIcon());

    ui->spinBoxNumLay->setMaximum(1000);

    ui->actionLoad->setShortcut(QKeySequence::Open);
    ui->actionLoad->setStatusTip("Load parameters");
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSave->setStatusTip("Save parameters");
    ui->actionAbout->setStatusTip("About the program");

    setDefaults();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{
    QMessageBox::information(this, "test", "triggering save button", QMessageBox::Ok);
    QFile fsave(QDir::currentPath() + "/def.json");//build directory
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
    QFile fload(QDir::currentPath() + "/def.json");//build directory
    if(!fload.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open file.");
        return;
    }
    QByteArray data = fload.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    read(doc.object());
    set();
    fload.close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About the program", "");
}

void MainWindow::on_spinBoxNumNeur_valueChanged(int arg1)
{
    numNeur_ = arg1;

    ui->tableWidgetInitValues->setRowCount(numNeur_);
    ui->tableWidgetInitValues->setColumnCount(3);
    for(int i = 0; i < numNeur_; i++)
        for(int j = 0; j < 3; j++)
        {
            auto item = ui->tableWidgetInitValues->item(i, j);
            if(!item)
            {
                item = new QTableWidgetItem();
                ui->tableWidgetInitValues->setItem(i, j, item);
            }
            item->setText("0.1");
        }
}

void MainWindow::on_pushButtonStart_clicked()
{

}

void MainWindow::setDefaults()
{
    ui->spinBoxNumNeur->setValue(3);
    ui->spinBoxNumLay->setValue(300);
    ui->lineEditTime->setText("10.0");
    ui->lineEditLimit->setText("1.0");
    ui->lineEditStep->setText("0.1");
    ui->lineEditAccur->setText("0.0001");
    ui->lineEditM1->setText("1.0");
    ui->lineEditM2->setText("100.0");
}

void MainWindow::set()
{
    ui->spinBoxNumNeur->setValue(numNeur_);
    ui->spinBoxNumLay->setValue(numLay_);
    ui->lineEditTime->setText(QString::number(time_));
    ui->lineEditLimit->setText(QString::number(limit_));
    ui->lineEditM1->setText(QString::number(M1_));
    ui->lineEditM2->setText(QString::number(M2_));
    ui->lineEditStep->setText(QString::number(step_));
    ui->lineEditAccur->setText(QString::number(accur_));
}

void MainWindow::get()
{
    numNeur_ = ui->spinBoxNumNeur->value();//auto update when changing?
    numLay_ = ui->spinBoxNumLay->value();
    time_ = ui->lineEditTime->text().toDouble();
    limit_ = ui->lineEditLimit->text().toDouble();
    M1_ = ui->lineEditM1->text().toDouble();
    M2_ = ui->lineEditM2->text().toDouble();
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
