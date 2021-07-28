#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFileDialog>
#include<drawingpanel.h>
#include<symboltray.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QList<DrawingPanel *> *drawingPanels;
    DrawingPanel *drawingPanel;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    static void showComponents(QListWidget *listWidget);

private slots:
    void on_drawRectangle_clicked();

    void on_drawLine_clicked();

    void on_drawCircle_clicked();

    void on_freeHandTool_clicked();

    void on_selectionButton_clicked();

    void on_saveButton_clicked();

    void on_openButton_clicked();

    void on_startRecordingButton_clicked();

    void on_stopRecordingButton_clicked();

    void on_imageButton_clicked();

    void on_componentPanel_itemChanged(QListWidgetItem *item);

    void on_componentPanel_itemClicked(QListWidgetItem *item);

    void on_groupComponentsButton_clicked();

    void on_ungroupComponentsButton_clicked();

    void on_taskBarButton_clicked();

    void on_signsPanelButton_clicked();

    void on_signsAndSymbolsPanelCloseButton_clicked();

    void on_brushSize_valueChanged(int value);

    void on_colorSelectionButton_clicked();

    void on_backgroundColorButton_clicked();

    void on_undoButton_clicked();

    void on_redoButton_clicked();

    void on_deleteComponentButton_clicked();

    void on_newPageButton_clicked();

    void radioButtonClicked();

    void on_componentPanel_itemSelectionChanged();

    void on_deletePageButton_clicked();

    void on_newBlankPageButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
