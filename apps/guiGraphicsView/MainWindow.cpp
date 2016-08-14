#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <CppBuildInfo/DataParser.h>

#include <QDir>
#include <QFileDialog>
#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsRectItem>

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
        auto starting = parser.getStartingTimes();
        auto ending = parser.getEndingTimes();

//        ui->graphicsView->scene()
        QGraphicsScene * scene = new QGraphicsScene;
        int x = 0;
        int y = 0;

        for (int i = 0; i < fileNames.size(); ++i) {
            scene->addRect(x, y, times[i], 10);
            x += times[i];
            y += 15;
        }

        ui->graphicsView->setScene(scene);
    }
}
