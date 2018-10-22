#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QDialog>
#include <QTimer>
#include <datacharts.h>
#include "qcustomplot.h"
#include <QDebug>
#include <QList>

namespace Ui {
class ChartWindow;
}

class ChartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChartWindow(QList<DataCharts> *list_chart, QWidget *parent = 0);
    ~ChartWindow();

private slots:
    void closeChartWindow();
    void titleDoubleClick(QMouseEvent *event);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void addRandomGraph();
    void removeSelectedGraph();
    void removeAllGraphs();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

private:
    Ui::ChartWindow *ui;
    QList<DataCharts> *p_curr_chart;
    QCPTextElement *title;
    void setupChart();
    void showParameters(int i);
    void drawSpeedRotationChart(QCustomPlot *customPlot);
};

#endif // CHARTWINDOW_H
