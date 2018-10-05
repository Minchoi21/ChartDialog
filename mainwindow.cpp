#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
