#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CompilationProcessGraphicItem.h"

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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                                    tr("Text file (*.txt)"));
    if (!fileName.isEmpty()) {
        DataParser parser(fileName);
        const auto & processes = parser.getAllProcesses();

        QGraphicsScene * scene = new QGraphicsScene;
        qint64 xStart = processes[0].start;
        qint64 y = 0;

        for (const auto & p : processes) {
            auto * item = new CompilationProcessGraphicItem(p.fileName(), p.start - xStart, y,
                                                            p.duration(), 20);
            scene->addItem(item);
            y += 22;
        }

        ui->graphicsView->setScene(scene);
    }
}
