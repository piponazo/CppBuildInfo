#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CompilationProcessGraphicItem.h"
#include "mygraphicsview.h"

#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/CompilationProcess.h>

#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>

#include <QMessageBox>
#include <QSplitter>
#include <QCloseEvent>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

// ------------------------------------------------------------------------------------------------
// Private implementation
// ------------------------------------------------------------------------------------------------

namespace
{
    const qint64 HEIGHT = 30;
    void getNextCoordinates(std::vector<CompilationProcess> &concurrentProcs,
                            const CompilationProcess & nextProc,
                            qint64 &nextY)
    {
        for (size_t i = 0; i<concurrentProcs.size(); i++) {
            if (concurrentProcs[i].end < nextProc.start) {
                concurrentProcs[i] = nextProc;
                nextY = i * HEIGHT * 1.2;
                break;
            }
        }
    }
}

struct MainWindow::Pimpl
{
    void setupUi(MainWindow *parent, Ui::MainWindow *ui_);

    void createActionsAndConnections();
    void createMenus();
    void updateRecentActionList();
    void loadFile(const QString &path);
    void saveIntoRecentList(const QString &path);

    // Stuff for recent projects feature
    QList<QAction*> recentFileActionList;
    QString currentFilePath;
    const int maxFileNr {5};
    int maxY {0};

    MainWindow * parent {nullptr};
    Ui::MainWindow *ui {nullptr};
    QSplitter * splitter {nullptr};
    MyGraphicsView * view {nullptr};
    QFrame * frame {nullptr};
    QLabel * labelTotalTime {nullptr};
};

void MainWindow::Pimpl::setupUi(MainWindow *parent_, Ui::MainWindow *ui_)
{
    parent = parent_;
    ui = ui_;
    splitter = new QSplitter(parent);
    view = new MyGraphicsView(parent);
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

void MainWindow::Pimpl::createActionsAndConnections()
{
    QAction* recentFileAction = 0;
    for(int i = 0; i < maxFileNr; ++i){
        recentFileAction = new QAction(parent);
        recentFileAction->setVisible(false);
        QObject::connect(recentFileAction, SIGNAL(triggered()), parent, SLOT(openRecent()));
        recentFileActionList.append(recentFileAction);
    }
}

void MainWindow::Pimpl::createMenus()
{
    for(int i = 0; i < maxFileNr; ++i) {
        ui->menuRecentFiles->addAction(recentFileActionList.at(i));
    }

    updateRecentActionList();
}

void MainWindow::Pimpl::updateRecentActionList()
{
    QSettings settings;
    QStringList recentFilePaths = settings.value("recentFiles").toStringList();

    int itEnd = 0;
    if(recentFilePaths.size() <= maxFileNr)
        itEnd = recentFilePaths.size();
    else
        itEnd = maxFileNr;

    for (int i = 0; i < itEnd; ++i) {
        QString strippedName = QFileInfo(recentFilePaths.at(i)).fileName();
        recentFileActionList.at(i)->setText(strippedName);
        recentFileActionList.at(i)->setData(recentFilePaths.at(i));
        recentFileActionList.at(i)->setVisible(true);
    }

    for (int i = itEnd; i < maxFileNr; ++i) {
        recentFileActionList.at(i)->setVisible(false);
    }
}

void MainWindow::Pimpl::loadFile(const QString &path)
{
    DataParser parser(path);
    const auto & processes = parser.getAllProcesses();
    const size_t nConcurrentProcs = parser.getNConcurrentProcesses();
    if (processes.empty()) {
        QMessageBox::warning(parent, tr("Error parsing the file"),
            tr("Either the data file is empty or the data is incorrect"));
        return;
    }

    QGraphicsScene * scene = new QGraphicsScene;
    qint64 xStart = processes[0].start;
    qint64 y = 0;
    std::vector<CompilationProcess> concurrentProcs (nConcurrentProcs);

    for (const auto & p : processes) {
        getNextCoordinates(concurrentProcs, p, y);
        auto * item = new CompilationProcessGraphicItem(p.fileName(), p.start - xStart, y,
                                                        p.duration(), HEIGHT);
        scene->addItem(item);
    }

    QRectF rect;
    rect.setX(processes.front().start);
    rect.setY(0);
//    rect.setWidth(parser.getTotalTime());
    rect.setWidth(parser.getTotalTime()/2);
    rect.setHeight(nConcurrentProcs * HEIGHT * 2);
    maxY = static_cast<int>(rect.height());

    view->setScene(scene);
    labelTotalTime->setText(QString("Total time: %1 msecs").arg(parser.getTotalTime()));

    view->fitInView(rect);
    saveIntoRecentList(path);

    connect(view, SIGNAL(positionX(int)), parent, SLOT(drawInfoInStatusBar(int)));
}

void MainWindow::Pimpl::saveIntoRecentList(const QString &path)
{
    currentFilePath = path;
    parent->setWindowFilePath(currentFilePath);

    QSettings settings;
    QStringList recentFilePaths = settings.value("recentFiles").toStringList();
    recentFilePaths.removeAll(path);
    recentFilePaths.prepend(path);
    while (recentFilePaths.size() > maxFileNr) {
        recentFilePaths.removeLast();
    }
    settings.setValue("recentFiles", recentFilePaths);

    // see note
    updateRecentActionList();
}

// ------------------------------------------------------------------------------------------------
// MainWindow public implementation
// ------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _impl(new Pimpl)
{
    ui->setupUi(this);
    _impl->setupUi(this, ui);

    _impl->createActionsAndConnections();
    _impl->createMenus();

    readWindowSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _impl;
}


void MainWindow::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                                    tr("Text file (*.txt)"));

    if (!fileName.isEmpty()) {
        _impl->loadFile(fileName);
    }
}

void MainWindow::openRecent()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        _impl->loadFile(action->data().toString());
    }
}

void MainWindow::drawInfoInStatusBar(int x)
{
    auto scene = _impl->view->scene();
    QRectF rect(x, 0, 1, _impl->maxY);
    auto items = scene->items(rect);
    ui->statusbar->showMessage(QString(tr("Concurrent compilations: %1")).arg(items.size()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::readWindowSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

