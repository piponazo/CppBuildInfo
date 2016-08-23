#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CompilationProcessGraphicItem.h"

#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/CompilationProcess.h>

#include <QDir>
#include <QFileDialog>
#include <QDebug>

#include <QSplitter>
#include <QGraphicsView>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

struct MainWindow::Pimpl
{
    void setupUi(QMainWindow *parent);

    QSplitter * splitter {nullptr};
    QGraphicsView * view {nullptr};
    QFrame * frame {nullptr};
    QLabel * labelTotalTime;
};

void MainWindow::Pimpl::setupUi(QMainWindow *parent)
{
    splitter = new QSplitter(parent);
    view = new QGraphicsView;
    view->setMinimumWidth(500);

    QVBoxLayout *frameLayout = new QVBoxLayout;
    labelTotalTime = new QLabel("Total time: ");
    frameLayout->addWidget(labelTotalTime);
    frame = new QFrame;
    frame->setLayout(frameLayout);

    splitter->addWidget(view);
    splitter->addWidget(frame);

    parent->centralWidget()->layout()->addWidget(splitter);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _ui(new Pimpl)
{
    ui->setupUi(this);
    _ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _ui;
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                                    tr("Text file (*.txt)"));
    QRectF rect;
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

        rect.setX(processes.front().start);
        rect.setY(0);
        rect.setWidth(parser.getTotalTime());
        rect.setHeight(y);

        _ui->view->setScene(scene);
        _ui->labelTotalTime->setText(QString("Total time: %1 msecs").arg(parser.getTotalTime()));
    }

    _ui->view->fitInView(rect);

}
