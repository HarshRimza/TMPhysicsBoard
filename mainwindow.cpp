#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawingPanels=new QList<DrawingPanel *>();
    drawingPanel=new DrawingPanel(this->ui->frame);
    drawingPanel->model->componentPanel=ui->componentPanel;
    this->drawingPanels->append(this->drawingPanel);

    QRadioButton *radioButton=new QRadioButton(this);
    radioButton->setGeometry(1766,20,16,16);
    radioButton->setChecked(true);
    connect(radioButton,SIGNAL(clicked()),this,SLOT(radioButtonClicked()));
    drawingPanel->radioButton=radioButton;

    ui->frame->setStyleSheet("border-image: url(:/images/whiteBoard-blueBorder1.jpg);");
    ui->freeHandTool->setIcon(QIcon(":images/pencil_icon"));
    ui->drawLine->setIcon(QIcon(":images/line_icon2"));
    ui->drawRectangle->setIcon(QIcon(":images/rectangle_icon"));
    ui->drawCircle->setIcon(QIcon(":images/circle_icon"));
    ui->imageButton->setIcon(QIcon(":images/image_icon.png"));
    ui->selectionButton->setIcon(QIcon(":images/selectComponent_icon"));
    ui->groupComponentsButton->setIcon(QIcon(":images/group_icon.png"));
    ui->ungroupComponentsButton->setIcon(QIcon(":images/ungroup_icon.png"));
    ui->taskBarButton->setIcon(QIcon(":images/taskbar2_icon.png"));
    ui->signsPanelButton->setIcon(QIcon(":images/pi.png"));
    ui->startRecordingButton->setIcon(QIcon(":images/start_recording_icon.png"));
    ui->stopRecordingButton->setIcon(QIcon(":images/stop_recording_icon.png"));
    ui->saveButton->setIcon(QIcon(":images/save_icon"));
    ui->openButton->setIcon(QIcon(":images/open_icon"));
    ui->redoButton->setIcon(QIcon(":images/redo.png"));
    ui->undoButton->setIcon(QIcon(":images/undo.png"));
    ui->deleteComponentButton->setIcon(QIcon(":images/bin.png"));
    ui->newPageButton->setIcon(QIcon(":images/add_page_icon.png"));
    ui->newBlankPageButton->setIcon(QIcon(":images/add_blank_page_icon.png"));
    ui->deletePageButton->setIcon(QIcon(":images/delete_page_icon.png"));

    ui->startRecordingButton->setVisible(false);
    ui->stopRecordingButton->setVisible(false);

    ui->freeHandTool->setToolTip("Pencil");
    ui->drawLine->setToolTip("Line");
    ui->drawRectangle->setToolTip("Rectangle");
    ui->drawCircle->setToolTip("Circle");
    ui->imageButton->setToolTip("Image");
    ui->selectionButton->setToolTip("Select Component");
    ui->groupComponentsButton->setToolTip("Group Components (Ctrl+G)");
    ui->ungroupComponentsButton->setToolTip("Ungroup Components (Ctrl+U)");
    ui->taskBarButton->setToolTip("Minimize Application");
    ui->signsPanelButton->setToolTip("Signs and Symbols Panel");
    ui->startRecordingButton->setToolTip("Start Recording");
    ui->stopRecordingButton->setToolTip("Stop Recording");
    ui->saveButton->setToolTip("Save (Ctrl+S)");
    ui->openButton->setToolTip("Open (Ctrl+O)");
    ui->redoButton->setToolTip("Redo (Ctrl+Y)");
    ui->undoButton->setToolTip("Undo (Ctrl+Z)");
    ui->brushSize->setToolTip("Select the width of the selected Tool");
    ui->colorSelectionButton->setToolTip("This color is used for shape fills");
    ui->backgroundColorButton->setToolTip("This color is used with pencil as well as for shapes outlines");
    ui->deleteComponentButton->setToolTip("Delete Component (Ctrl+D)");
    ui->newPageButton->setToolTip("Add Lined Page (Ctrl+N)");
    ui->newBlankPageButton->setToolTip("Add Blank Page (Ctrl+B)");
    ui->deletePageButton->setToolTip("Delete Page (Del)");

    ui->signsAndSymbolsPanel->setVisible(false);
    ui->signsAndSymbolsPanel->setGeometry(110,220,236,223);

    SymbolTray *st=new SymbolTray(this->ui->signsFrame);

    setWindowIcon(QIcon(":images/app_icon.png"));
    setWindowFlags(Qt::FramelessWindowHint);
    showFullScreen();
}

MainWindow::~MainWindow()
{
    for(DrawingPanel *drawingPanel:*drawingPanels) delete drawingPanel;
    delete drawingPanels;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void MainWindow::on_drawRectangle_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    DrawingPanel::selectedComponent=2;
    this->drawingPanel->model->removeAllSelection(false);
    this->ui->componentPanel->reset();
    QIcon icon(":images/crayon_icon.png");
    QPixmap pixmap=icon.pixmap(QSize(48,48));
    this->drawingPanel->setCursor(QCursor(pixmap,14,1));
    this->drawingPanel->update();
}

void MainWindow::on_drawLine_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    DrawingPanel::selectedComponent=1;
    this->drawingPanel->model->removeAllSelection(false);
    this->ui->componentPanel->reset();
    QIcon icon(":images/crayon_icon.png");
    QPixmap pixmap=icon.pixmap(QSize(48,48));
    this->drawingPanel->setCursor(QCursor(pixmap,14,1));
    this->drawingPanel->update();
}

void MainWindow::on_drawCircle_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    DrawingPanel::selectedComponent=3;
    this->drawingPanel->model->removeAllSelection(false);
    this->ui->componentPanel->reset();
    QIcon icon(":images/crayon_icon.png");
    QPixmap pixmap=icon.pixmap(QSize(48,48));
    this->drawingPanel->setCursor(QCursor(pixmap,14,1));
    this->drawingPanel->update();
}

void MainWindow::on_freeHandTool_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    QIcon icon(":images/pencil_icon4.png");
    QPixmap pixmap=icon.pixmap(QSize(48,48));
    this->drawingPanel->setCursor(QCursor(pixmap,14,1));
    DrawingPanel::selectedComponent=4;
    this->drawingPanel->model->removeAllSelection(false);
    this->ui->componentPanel->reset();
    this->drawingPanel->update();
}

void MainWindow::on_selectionButton_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    DrawingPanel::selectedComponent=5;
    this->ui->componentPanel->reset();
    this->drawingPanel->model->removeAllSelection(false);
    this->drawingPanel->update();
}

void MainWindow::on_imageButton_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    this->ui->componentPanel->reset();
    this->drawingPanel->model->removeAllSelection(false);
    this->drawingPanel->setCursor(Qt::CrossCursor);
    this->drawingPanel->update();
    QString imagePath=QFileDialog::getOpenFileName(this,tr("Select Image"),"c:\\qteg\\Images",tr("Image Files (*.png *.jpg *.bmp)"));
    if(imagePath.length()==0) return;
    TMImageComponent *tmic=new TMImageComponent;
    tmic->imagePath=imagePath;
    this->drawingPanel->tmImageComponent=tmic;
    DrawingPanel::selectedComponent=6;
}

void MainWindow::on_groupComponentsButton_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    this->drawingPanel->model->createGroup();
    this->drawingPanel->update();
}

void MainWindow::on_ungroupComponentsButton_clicked()
{
    DrawingPanel::selectedComponent=0;
    on_signsAndSymbolsPanelCloseButton_clicked();
    this->drawingPanel->model->unGroup();
    this->drawingPanel->update();
    DrawingPanel::selectedComponent=5;
}

void MainWindow::on_saveButton_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save File"),"c:\\qteg\\SavedFiles","*.phy");
    if(fileName.length()==0) return;
    QJsonArray drawingPanels;
    for(DrawingPanel *dp:*this->drawingPanels)
    {
        drawingPanels.append(dp->toJSON());
    }
    QJsonDocument jsonDocument;
    jsonDocument.setArray(drawingPanels);
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox m;
        m.setText("File cannot be saved");
        m.exec();
        return;
    }
    file.resize(0);
    file.write(jsonDocument.toJson());
    file.close();
}

void MainWindow::on_openButton_clicked()
{
    DrawingPanel::selectedComponent=0;
    on_signsAndSymbolsPanelCloseButton_clicked();
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open File"),"c:\\qteg\\SavedFiles","*.phy");
    if(fileName.length()==0) return;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox m;
        m.setText("File cannot be open");
        m.exec();
        return;
    }
    QString componentsListString=file.readAll();
    file.close();
    QJsonDocument jsonDocument=QJsonDocument::fromJson(componentsListString.toUtf8());
    QJsonArray drawingPanels=jsonDocument.array();
    for(DrawingPanel *dp:*this->drawingPanels) delete dp;
    this->drawingPanels->clear();
    this->drawingPanel=nullptr;
    for(QJsonValue jsonModel:drawingPanels)
    {
        on_newPageButton_clicked();
        this->drawingPanel->fromJSON(jsonModel);
    }
    this->drawingPanels->front()->radioButton->setChecked(true);
    radioButtonClicked();
}

void MainWindow::on_newPageButton_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    this->ui->componentPanel->reset();
    this->ui->componentPanel->clear();
    if(this->drawingPanel!=nullptr)
    {
        this->drawingPanel->model->removeAllSelection(false);
        this->drawingPanel->setVisible(false);
    }
    int length=this->drawingPanels->length();
    if(length==1 && this->drawingPanel->model->components->length()==0)
    {
        this->drawingPanel->drawLines=true;
        this->drawingPanel->setVisible(true);
        return;
    }
    this->drawingPanel=new DrawingPanel(this->ui->frame);
    this->drawingPanel->model->componentPanel=this->ui->componentPanel;
    this->drawingPanel->drawLines=true;
    this->drawingPanel->setVisible(true);

    QRadioButton *radioButton=new QRadioButton(this);
    radioButton->setGeometry(1766,(20*length)+20,16,16);
    radioButton->setChecked(true);
    radioButton->setVisible(true);
    this->drawingPanel->radioButton=radioButton;
    connect(radioButton,SIGNAL(clicked()),this,SLOT(radioButtonClicked()));
    this->drawingPanels->append(this->drawingPanel);

    int selectedComponent=DrawingPanel::selectedComponent;
    if(selectedComponent==1) on_drawLine_clicked();
    else if(selectedComponent==2) on_drawRectangle_clicked();
    else if(selectedComponent==3) on_drawCircle_clicked();
    else if(selectedComponent==4) on_freeHandTool_clicked();
    else if(selectedComponent==5) on_selectionButton_clicked();
    else if(selectedComponent==6) on_drawLine_clicked();
}

void MainWindow::on_newBlankPageButton_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    this->ui->componentPanel->reset();
    this->ui->componentPanel->clear();
    if(this->drawingPanel!=nullptr)
    {
        this->drawingPanel->model->removeAllSelection(false);
        this->drawingPanel->setVisible(false);
    }

    this->drawingPanel=new DrawingPanel(this->ui->frame);
    this->drawingPanel->model->componentPanel=this->ui->componentPanel;
    this->drawingPanel->setVisible(true);

    int length=this->drawingPanels->length();
    QRadioButton *radioButton=new QRadioButton(this);
    radioButton->setGeometry(1766,(20*length)+20,16,16);
    radioButton->setChecked(true);
    radioButton->setVisible(true);
    this->drawingPanel->radioButton=radioButton;
    connect(radioButton,SIGNAL(clicked()),this,SLOT(radioButtonClicked()));
    this->drawingPanels->append(this->drawingPanel);

    int selectedComponent=DrawingPanel::selectedComponent;
    if(selectedComponent==1) on_drawLine_clicked();
    else if(selectedComponent==2) on_drawRectangle_clicked();
    else if(selectedComponent==3) on_drawCircle_clicked();
    else if(selectedComponent==4) on_freeHandTool_clicked();
    else if(selectedComponent==5) on_selectionButton_clicked();
    else if(selectedComponent==6) on_drawLine_clicked();
}

void MainWindow::radioButtonClicked()
{
    if(this->drawingPanels->length()!=1)
    {
        on_signsAndSymbolsPanelCloseButton_clicked();
        this->ui->componentPanel->reset();
        this->drawingPanel->model->removeAllSelection(false);
        this->drawingPanel->setVisible(false);
        int i=0;
        for(DrawingPanel *dp:*this->drawingPanels)
        {
            if(dp->radioButton->isChecked())
            {
                this->drawingPanel=dp;
                this->drawingPanel->setVisible(true);
                this->drawingPanel->model->showComponents();
                break;
            }
            ++i;
        }
        this->drawingPanel->update();
    }
}

void MainWindow::on_componentPanel_itemChanged(QListWidgetItem *item)
{
    int row=item->listWidget()->row(item);
    QString text=item->text().trimmed();
    if(text.length()==0)
    {
        item->setText(this->drawingPanel->model->components->value(row)->getComponentNameByUser());
    }
    if(text.length()!=0)
    {
        this->drawingPanel->model->components->value(row)->setComponentNameByUser(text);
        item->setText(text);
    }
}

void MainWindow::on_componentPanel_itemClicked(QListWidgetItem *item)
{
    if(DrawingPanel::selectedComponent==5 && !QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        this->drawingPanel->model->removeAllSelection(false);
        int row=item->listWidget()->row(item);
        DrawableComponent *drawableComponent;
        QList<DrawableComponent *> *components=this->drawingPanel->model->components;
        drawableComponent=components->value(row);
        if(item->isSelected())
        {
            drawableComponent->select();
            drawableComponent->setSelected(true);
        }
        this->drawingPanel->model->addSelectedComponentsToGroupedComponents(570,365);
        this->drawingPanel->update();
    }
    item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void MainWindow::on_taskBarButton_clicked()
{
    this->showMinimized();
}

void MainWindow::on_signsPanelButton_clicked()
{
    this->ui->componentPanel->reset();
    this->drawingPanel->model->removeAllSelection(false);
    DrawingPanel::selectedComponent=5;
    this->ui->signsAndSymbolsPanel->setVisible(true);
}

void MainWindow::on_signsAndSymbolsPanelCloseButton_clicked()
{
    this->ui->signsAndSymbolsPanel->setVisible(false);
}

void MainWindow::on_brushSize_valueChanged(int value)
{
    DrawingPanel::brushSize=value;
}

void MainWindow::on_colorSelectionButton_clicked()
{
    QColorDialog colorDialog;
    colorDialog.open();
    QColor color=colorDialog.getColor().toRgb();
    DrawingPanel::color=color.name();
    this->ui->colorSelectionButton->setStyleSheet(QString("background-color: rgb("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+");"));
}

void MainWindow::on_backgroundColorButton_clicked()
{
    QColorDialog colorDialog;
    colorDialog.open();
    QColor color=colorDialog.getColor();
    DrawingPanel::borderColor=color.name();
    this->ui->backgroundColorButton->setStyleSheet(QString("background-color: rgb("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+");"));
}

void MainWindow::on_undoButton_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    this->ui->componentPanel->reset();
    this->drawingPanel->model->removeAllSelection(false);
    this->drawingPanel->model->undo();
    this->drawingPanel->update();
}

void MainWindow::on_redoButton_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    this->ui->componentPanel->reset();
    this->drawingPanel->model->removeAllSelection(false);
    this->drawingPanel->model->redo();
    this->drawingPanel->update();
}

void MainWindow::on_deleteComponentButton_clicked()
{
    on_signsAndSymbolsPanelCloseButton_clicked();
    this->ui->componentPanel->reset();
    this->drawingPanel->model->removeAllSelection(false);
    this->drawingPanel->model->deleteComponent();
    this->drawingPanel->update();
}


void MainWindow::on_startRecordingButton_clicked()
{

}

void MainWindow::on_stopRecordingButton_clicked()
{

}

void MainWindow::on_componentPanel_itemSelectionChanged()
{
    if(DrawingPanel::selectedComponent==5 && QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        QList<DrawableComponent *> *components=this->drawingPanel->model->components;
        int length=components->length();
        QListWidgetItem *item=nullptr;
        DrawableComponent *drawableComponent;
        for(int i=0;i<length;++i)
        {
            item=this->ui->componentPanel->item(i);
            drawableComponent=components->value(i);
            if(item->isSelected())
            {
                drawableComponent->select();
                drawableComponent->setSelected(true);
            }
            else
            {
                drawableComponent->setPointsToNull();
                drawableComponent->setSelected(false);
            }
        }
        this->drawingPanel->model->addSelectedComponentsToGroupedComponents(570,365);
        this->drawingPanel->update();
    }
}

void MainWindow::on_deletePageButton_clicked()
{
        DrawingPanel *drawingPanel=nullptr;
        bool found=false;
        for(DrawingPanel *dp:*this->drawingPanels)
        {
            if(found) dp->radioButton->setGeometry(1766,dp->radioButton->y()-20,16,16);
            else if(this->drawingPanel!=dp) drawingPanel=dp;
            else found=true;
        }
        this->drawingPanels->removeOne(this->drawingPanel);
        delete this->drawingPanel;

        if(drawingPanel==nullptr && this->drawingPanels->length()!=0) this->drawingPanel=this->drawingPanels->front();
        else this->drawingPanel=drawingPanel;

        if(this->drawingPanel==nullptr)
        {
            this->on_newBlankPageButton_clicked();
        }
        this->drawingPanel->setVisible(true);
        this->drawingPanel->radioButton->setChecked(true);
//        this->drawingPanel->update();
        this->drawingPanel->model->showComponents();
}

