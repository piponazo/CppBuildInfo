#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpenFile_triggered();
    void openRecent();

private:
    void createActionsAndConnections();
    void createMenus();
    void updateRecentActionList();
    void loadFile(const QString &path);
    void saveIntoRecentList(const QString &path);

    Ui::MainWindow *ui;

    struct Pimpl;
    Pimpl * _ui;

    QList<QAction*> _recentFileActionList;
    const int _maxFileNr;
    QString _currentFilePath;
};
