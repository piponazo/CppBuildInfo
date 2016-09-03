#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CompilationProcessGraphicItem.h"

#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/CompilationProcess.h>

#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>

#include <QMessageBox>
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
    , _maxFileNr(5)
{
    ui->setupUi(this);
    _ui->setupUi(this);

    createActionsAndConnections();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _ui;
}

void MainWindow::createActionsAndConnections()
{
    QAction* recentFileAction = 0;
    for(int i = 0; i < _maxFileNr; ++i){
        recentFileAction = new QAction(this);
        recentFileAction->setVisible(false);
        QObject::connect(recentFileAction, SIGNAL(triggered()), this, SLOT(openRecent()));
        _recentFileActionList.append(recentFileAction);
    }
}

void MainWindow::createMenus()
{
    for(int i = 0; i < _maxFileNr; ++i) {
        ui->menuRecentFiles->addAction(_recentFileActionList.at(i));
    }

    updateRecentActionList();
}

void MainWindow::updateRecentActionList()
{
    QSettings settings;
    QStringList recentFilePaths = settings.value("recentFiles").toStringList();

    int itEnd = 0;
    if(recentFilePaths.size() <= _maxFileNr)
        itEnd = recentFilePaths.size();
    else
        itEnd = _maxFileNr;

    for (int i = 0; i < itEnd; ++i) {
        QString strippedName = QFileInfo(recentFilePaths.at(i)).fileName();
        _recentFileActionList.at(i)->setText(strippedName);
        _recentFileActionList.at(i)->setData(recentFilePaths.at(i));
        _recentFileActionList.at(i)->setVisible(true);
    }

    for (int i = itEnd; i < _maxFileNr; ++i) {
        _recentFileActionList.at(i)->setVisible(false);
    }
}

void MainWindow::loadFile(const QString &path)
{
    DataParser parser(path);
    const auto & processes = parser.getAllProcesses();
    if (processes.empty()) {
        QMessageBox::warning(this, tr("Error parsing the file"),
            tr("Either the data file is empty or the data is incorrect"));
        return;
    }

    QGraphicsScene * scene = new QGraphicsScene;
    qint64 xStart = processes[0].start;
    qint64 y = 0;

    for (const auto & p : processes) {
        auto * item = new CompilationProcessGraphicItem(p.fileName(), p.start - xStart, y,
                                                        p.duration(), 20);
        scene->addItem(item);
        y += 22;
    }

    QRectF rect;
    rect.setX(processes.front().start);
    rect.setY(0);
    rect.setWidth(parser.getTotalTime());
    rect.setHeight(y);

    _ui->view->setScene(scene);
    _ui->labelTotalTime->setText(QString("Total time: %1 msecs").arg(parser.getTotalTime()));

    _ui->view->fitInView(rect);
    saveIntoRecentList(path);
}

void MainWindow::saveIntoRecentList(const QString &path)
{
    _currentFilePath = path;
    setWindowFilePath(_currentFilePath);

    QSettings settings;
    QStringList recentFilePaths = settings.value("recentFiles").toStringList();
    recentFilePaths.removeAll(path);
    recentFilePaths.prepend(path);
    while (recentFilePaths.size() > _maxFileNr) {
        recentFilePaths.removeLast();
    }
    settings.setValue("recentFiles", recentFilePaths);

    // see note
    updateRecentActionList();
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                                    tr("Text file (*.txt)"));

    if (!fileName.isEmpty()) {
        loadFile(fileName);
    }
}

void MainWindow::openRecent()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        loadFile(action->data().toString());
    }
}

