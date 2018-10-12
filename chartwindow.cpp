#include "chartwindow.h"
#include "ui_chartwindow.h"

ChartWindow::ChartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);
    setWindowTitle("SPEED CHART WINDOW");

    setupChart();
}

ChartWindow::~ChartWindow()
{
    delete ui;
}

void ChartWindow::setupChart()
{
    drawSpeedRotationChart(ui->custom_plot);
    ui->custom_plot->replot();
}

void ChartWindow::drawSpeedRotationChart(QCustomPlot *customPlot)
{

  // add new graph and set this look:
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::red)); // line color red for second graph
  customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
  // generate some points of data (y0 for first, y1 for second graph):
  QVector<double> x(251), y(251);
  for (int i=0; i<251; ++i)
  {
    x[i] = i;
    y[i] = qExp(-i/150.0);              // exponential envelope
  }
  // configure right and top axis to show ticks but no labels:
  // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
  customPlot->xAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setVisible(true);
  customPlot->yAxis2->setTickLabels(false);
  // make left and bottom axes always transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  // pass data points to graph:
  customPlot->graph(0)->setData(x, y);
  // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  customPlot->graph(0)->rescaleAxes();
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void ChartWindow::on_btnCloseChart_clicked()
{
    this->close();
}
