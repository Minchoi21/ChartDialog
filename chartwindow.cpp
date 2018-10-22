#include "chartwindow.h"
#include "ui_chartwindow.h"

ChartWindow::ChartWindow(QList<DataCharts> *list_chart, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartWindow)
{
    qDebug() << "fcn ChartWindow konstruktor";
    ui->setupUi(this);
    setWindowTitle("SPEED CHART WINDOW");

    connect(ui->btnCloseChart, SIGNAL(clicked()), this, SLOT(closeChartWindow()));

    if(list_chart) { //TODO: sprawdzić czy jest coś pod list_chart!!!

        this->p_curr_chart = list_chart;

        title = new QCPTextElement(ui->custom_plot, "Wlkm speed rotation", QFont("sans", 12, QFont::Bold));

        // connect slot that ties some axis selections together (especially opposite axes):
        connect(ui->custom_plot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
        // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
        connect(ui->custom_plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
        connect(ui->custom_plot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

        // make bottom and left axes transfer their ranges to top and right axes:
        connect(ui->custom_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->custom_plot->xAxis2, SLOT(setRange(QCPRange)));
        connect(ui->custom_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->custom_plot->yAxis2, SLOT(setRange(QCPRange)));

        // connect some interaction slots:
        connect(ui->custom_plot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
        connect(ui->custom_plot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
        connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

        // connect slot that shows a message in the status bar when a graph is clicked:
        connect(ui->custom_plot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

        // setup policy and connect slot for context menu popup:
        ui->custom_plot->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(ui->custom_plot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

        setupChart();
    } else {
        qDebug() << "In class ChartWindow: DataCharts chart is NULL";
    }
}

ChartWindow::~ChartWindow()
{
    qDebug() << "fcn ChartWindow destruktor";
    delete ui;
}

void ChartWindow::setupChart()
{
    qDebug() << "fcn setupChart";
//    showParameters();
    drawSpeedRotationChart(ui->custom_plot);
    ui->custom_plot->replot();
}

void ChartWindow::showParameters(int i)
{
    qDebug() << "fcn showParameters";
    ui->labelAvgSpeed       ->setText(this->p_curr_chart->at(i).getAvgSpeed());
    ui->labelRounds         ->setText(this->p_curr_chart->at(i).getRounds());
    ui->labelKp             ->setText(this->p_curr_chart->at(i).getKp());
    ui->labelKi             ->setText(this->p_curr_chart->at(i).getKi());
    ui->labelKpr            ->setText(this->p_curr_chart->at(i).getKpr());
    ui->labelI              ->setText(this->p_curr_chart->at(i).getI());
    ui->labelRPM            ->setText(this->p_curr_chart->at(i).getRpm());
    ui->labelPeriod         ->setText(this->p_curr_chart->at(i).getPeriod());
    ui->labelDuty           ->setText(this->p_curr_chart->at(i).getDuty());
    ui->labelSpeedMin       ->setText(this->p_curr_chart->at(i).getSpeedMin());
    ui->labelStallOnStart   ->setText(this->p_curr_chart->at(i).getStallOnStart());
    ui->labelStallWhenRun   ->setText(this->p_curr_chart->at(i).getStallWhenRun());
}

void ChartWindow::drawSpeedRotationChart(QCustomPlot *custom_plot)
{
    qDebug() << "fcn drawSpeedRotationChart";

    custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                          QCP::iSelectLegend | QCP::iSelectPlottables);
    custom_plot->xAxis->setRange(-8, 8);
    custom_plot->yAxis->setRange(-5, 5);
    custom_plot->axisRect()->setupFullAxesBox();

    custom_plot->plotLayout()->insertRow(0);
    custom_plot->plotLayout()->addElement(0, 0, title);

    custom_plot->xAxis->setLabel("Time (ms)");
    custom_plot->yAxis->setLabel("RPM");
    custom_plot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    custom_plot->legend->setFont(legendFont);
    custom_plot->legend->setSelectedFont(legendFont);
    custom_plot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    addRandomGraph();

    custom_plot->rescaleAxes();
}

void ChartWindow::titleDoubleClick(QMouseEvent* event)
{
  Q_UNUSED(event)
  if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender()))
  {
    // Set the plot title by double clicking on it
    bool ok;
    QString newTitle = QInputDialog::getText(this, "Qcustom_plot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
    if (ok)
    {
      title->setText(newTitle);
      ui->custom_plot->replot();
    }
  }
}

void ChartWindow::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "Qcustom_plot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      ui->custom_plot->replot();
    }
  }
}

void ChartWindow::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "Qcustom_plot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      ui->custom_plot->replot();
    }
  }
}

void ChartWindow::selectionChanged()
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->custom_plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->custom_plot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->custom_plot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->custom_plot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->custom_plot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->custom_plot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->custom_plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->custom_plot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->custom_plot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->custom_plot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->custom_plot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->custom_plot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<ui->custom_plot->graphCount(); ++i)
  {
    QCPGraph *graph = ui->custom_plot->graph(i);
    QCPPlottableLegendItem *item = ui->custom_plot->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
      showParameters(i);
      qDebug() << "Numer wykresu:" << i;
    }
  }
}

void ChartWindow::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (ui->custom_plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->custom_plot->axisRect()->setRangeDrag(ui->custom_plot->xAxis->orientation());
  else if (ui->custom_plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->custom_plot->axisRect()->setRangeDrag(ui->custom_plot->yAxis->orientation());
  else
    ui->custom_plot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void ChartWindow::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->custom_plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->custom_plot->axisRect()->setRangeZoom(ui->custom_plot->xAxis->orientation());
  else if (ui->custom_plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->custom_plot->axisRect()->setRangeZoom(ui->custom_plot->yAxis->orientation());
  else
    ui->custom_plot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void ChartWindow::addRandomGraph()
{
    for (int i=0; i < p_curr_chart->size(); i++)
    {
        ui->custom_plot->addGraph();
        ui->custom_plot->graph()->setName(QString("Series %1").arg(ui->custom_plot->graphCount()-1));
        // pass data points to graph:
        ui->custom_plot->graph()->setData(p_curr_chart->at(i).getVecPointsX(), p_curr_chart->at(i).getVecPointsY());
        ui->custom_plot->graph()->setLineStyle((QCPGraph::LineStyle)(QCPGraph::lsLine));
//        if (rand()%100 > 50)
//          ui->custom_plot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
        QPen graphPen;
        graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
        graphPen.setWidthF(2);
        ui->custom_plot->graph()->setPen(graphPen);
        showParameters(i);
        ui->custom_plot->replot();
    }

}

void ChartWindow::removeSelectedGraph()
{
  if (ui->custom_plot->selectedGraphs().size() > 0)
  {
    ui->custom_plot->removeGraph(ui->custom_plot->selectedGraphs().first());
    ui->custom_plot->replot();
  }
}

void ChartWindow::removeAllGraphs()
{
  ui->custom_plot->clearGraphs();
  ui->custom_plot->replot();
}

void ChartWindow::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  if (ui->custom_plot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
    menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
    menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
    menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
    menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
    menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  } else  // general context menu on graphs requested
  {
    menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
    if (ui->custom_plot->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    if (ui->custom_plot->graphCount() > 0)
      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
  }

  menu->popup(ui->custom_plot->mapToGlobal(pos));
}

void ChartWindow::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      ui->custom_plot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      ui->custom_plot->replot();
    }
  }
}

void ChartWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
}

void ChartWindow::closeChartWindow()
{
    qDebug() << "closeChartWindow()";
    this->close();
    delete(this);
}
