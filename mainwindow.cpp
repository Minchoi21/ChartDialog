#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("PULPIT WLMK v1.0");
    p_chart = NULL;
    connectSignalSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignalSlot()
{
    connect(ui->btnDrawChart, SIGNAL(clicked()), this, SLOT(openChartWindow()));
    connect(ui->btnReadDataChart, SIGNAL(clicked()), this, SLOT(readDataChart()));
}

void MainWindow::openChartWindow()
{
    qDebug() << "fcn openChartWindow";
    p_chart_window = new ChartWindow(&chart_list);
    p_chart_window->setModal(true);
    p_chart_window->show();

}

void MainWindow::readDataChart()
{
    qDebug() << "fcn on_btnReadChart_clicked";
    p_chart = new DataCharts();
    static int i_test = 0;
    int n = 1000; // number of points in graph
    double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
    double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
    double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
    double yOffset = (rand()/(double)RAND_MAX - 0.5)*10;
    double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
    double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
    double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
    double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
    double x, y;
    for (int i=0; i<n; i++)
    {
      x = (i/(double)n-0.5)*10.0*xScale + xOffset;
      y = (qSin(x*r1*5)*qSin(qCos(x*r2)*r4*3)+r3*qCos(qSin(x)*r4*2))*yScale + yOffset;
      p_chart->setPoint(x, y);
    }
    setCurrParameters(i_test++);
    p_chart->setAllParameters(&curr_param);
    chart_list.append(*p_chart);
    qDebug() << chart_list.last().getVecPointsX();
}

void MainWindow::setCurrParameters(int i)
{
    qDebug() << "fcn setCurrParameters";
    this->curr_param.avg_speed = 1.89 + (double)i;
    this->curr_param.rounds = 25 + (double)i;
    this->curr_param.kp = 0.3;
    this->curr_param.ki = 0.56;
    this->curr_param.kpr = 0.0;
    this->curr_param.i = 0.0;
    this->curr_param.rpm = 3600;
    this->curr_param.period = 24000;
    this->curr_param.duty = 45;
    this->curr_param.speed_min = 390;
    this->curr_param.stall_on_start = 2.0;
    this->curr_param.stall_when_run = 3.0;
}
