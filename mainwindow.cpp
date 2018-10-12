#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("PULPIT WLMK v1.0");
    connectSignalSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignalSlot()
{
    connect(ui->btnDrawChart, SIGNAL(clicked()), this, SLOT(openChartWindow()));
}

void MainWindow::openChartWindow()
{
    p_chart_window = new ChartWindow();
    p_chart_window->setModal(true);
    p_chart_window->show();
}

void MainWindow::on_btnReadChart_clicked()
{
    int data_size = 1000;
    chart_data.resize(data_size);
    for(int i=0; i<chart_data.size();i++){
        chart_data[i] = i+1;
    }

    qDebug() << chart_data;
}
