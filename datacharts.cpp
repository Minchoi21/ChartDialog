#include "datacharts.h"

DataCharts::DataCharts()
{
    qDebug() << "fcn DataCharts() konstruktor";
    this->st_param.avg_speed        = 0.0;
    this->st_param.rounds           = 0.0;
    this->st_param.kp               = 0.0;
    this->st_param.ki               = 0.0;
    this->st_param.kpr              = 0.0;
    this->st_param.i                = 0.0;
    this->st_param.rpm              = 0.0;
    this->st_param.period           = 0.0;
    this->st_param.duty             = 0.0;
    this->st_param.speed_min        = 0.0;
    this->st_param.stall_on_start   = 0.0;
    this->st_param.stall_when_run   = 0.0;
}

DataCharts::DataCharts(const QVector<double> &x, const QVector<double> &y)
{
    qDebug() << "fcn DataCharts(const QVector<double> &, const QVector<double> &) konstruktor";
    data_x = x;
    data_y = y;

}

DataCharts::~DataCharts()
{
    qDebug() << "fcn DataCharts destruktor";
    this->data_x.clear();
    this->data_y.clear();

}

void DataCharts::setSeriesNo(int no)
{
    this->series_no = no;
}

void DataCharts::setAllParameters(st_parameters_series_t *param_in)
{
    qDebug() << "fcn setAllParameters";
    this->st_param.avg_speed        = param_in->avg_speed;
    this->st_param.rounds           = param_in->rounds;
    this->st_param.kp               = param_in->kp;
    this->st_param.ki               = param_in->ki;
    this->st_param.kpr              = param_in->kpr;
    this->st_param.i                = param_in->i;
    this->st_param.rpm              = param_in->rpm;
    this->st_param.period           = param_in->period;
    this->st_param.duty             = param_in->duty;
    this->st_param.speed_min        = param_in->speed_min;
    this->st_param.stall_on_start   = param_in->stall_on_start;
    this->st_param.stall_when_run   = param_in->stall_when_run;
}

void DataCharts::setAvgSpeed(double data)
{
    st_param.avg_speed = data;
}

void DataCharts::setRounds(double data)
{
    st_param.rounds = data;
}

void DataCharts::setKp(double data)
{
    st_param.kp = data;
}

void DataCharts::setKi(double data)
{
    st_param.ki = data;
}

void DataCharts::setKpr(double data)
{
    st_param.kpr = data;
}

void DataCharts::setI(double data)
{
    st_param.i = data;
}

void DataCharts::setRpm(double data)
{
    st_param.rpm = data;
}

void DataCharts::setPeriod(double data)
{
    st_param.period = data;
}

void DataCharts::setDuty(double data)
{
    st_param.duty = data;
}

void DataCharts::setSpeedMin(double data)
{
    st_param.speed_min = data;
}

void DataCharts::setStallOnStart(double data)
{
    st_param.stall_on_start = data;
}

void DataCharts::setStallWhenRun(double data)
{
    st_param.stall_when_run = data;
}

void DataCharts::setPoint(double x, double y)
{
    data_x.append(x);
    data_y.append(y);
}

int DataCharts::getSeriesNo()
{
    return series_no;
}

DataCharts::st_parameters_series_t DataCharts::getAllParameters(){

    return st_param;
}

QString DataCharts::getAvgSpeed() const
{
    return QString::number(st_param.avg_speed);
}

QString DataCharts::getRounds() const
{
    return QString::number(st_param.rounds);
}

QString DataCharts::getKp() const
{
    return QString::number(st_param.kp);
}

QString DataCharts::getKi() const
{
    return QString::number(st_param.ki);
}

QString DataCharts::getKpr() const
{
    return QString::number(st_param.kpr);
}

QString DataCharts::getI() const
{
    return QString::number(st_param.i);
}

QString DataCharts::getRpm() const
{
    return QString::number(st_param.rpm);
}

QString DataCharts::getPeriod() const
{
    return QString::number(st_param.period);
}

QString DataCharts::getDuty() const
{
    return QString::number(st_param.duty);
}

QString DataCharts::getSpeedMin() const
{
    return QString::number(st_param.speed_min);
}

QString DataCharts::getStallOnStart() const
{
    return QString::number(st_param.stall_on_start);
}

QString DataCharts::getStallWhenRun() const
{
    return QString::number(st_param.stall_when_run);
}

QVector<double> DataCharts::getVecPointsX() const
{
    return data_x;
}

QVector<double> DataCharts::getVecPointsY() const
{
    return data_y;
}
