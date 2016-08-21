#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/CompilationProcess.h>

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
        const auto & processes = parser.getAllProcesses();

//        ui->graphicsView->scene()
        QGraphicsScene * scene = new QGraphicsScene;
        int x = 0;
        int y = 0;

        for (size_t i = 0; i < processes.size(); ++i) {
            scene->addRect(x, y, processes[i].duration(), 10);
            x += processes[i].duration();
            y += 15;
        }

        ui->graphicsView->setScene(scene);
    }
}
