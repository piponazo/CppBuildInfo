#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "DataParser.h"

#include <QDir>
#include <QFileDialog>
#include <QDebug>

#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalBarSeries>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text file (*.txt)"));
    if (!fileName.isEmpty()) {
        DataParser parser(fileName);
        auto fileNames = parser.getFileNames();
        auto times = parser.getTimes();

        QBarSet *set0 = new QBarSet("Time (msecs)");
        QHorizontalBarSeries *series = new QHorizontalBarSeries();

        QStringList sourceFiles;

        for (int i = 0; i < fileNames.size(); ++i) {
            sourceFiles << fileNames[i];
            *set0 << times[i];
        }

        series->append(set0);
        QBarCategoryAxis *axisY = new QBarCategoryAxis();
        axisY->append(sourceFiles);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Simple horizontal barchart example");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        chart->setAxisY(axisY, series);

        QValueAxis *axisX = new QValueAxis();
        chart->setAxisX(axisX, series);
        axisX->applyNiceNumbers();

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        setCentralWidget(chartView);
    }
}
