#include "edittimerwindow.h"
#include "ui_edittimerwindow.h"
#include "mywidget.h"
#include <QTime>
#include <QDebug>
#include <QColorDialog>
#include <QColor>
#include <QString>

editTimerWindow::editTimerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editTimerWindow)
{
    ui->setupUi(this);


    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    setWindowTitle("Edit: " + widgetPtr->windowTitle());

    connect(ui->showEndTimeCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWindowTitle()));

    //default values
    ui->lineEdit_windowTitle->setText(widgetPtr->windowTitleOnly);
    ui->updateIntervalSpinBox->setValue(widgetPtr->updateTimer.interval() / 1000);
    if(ui->updateIntervalSpinBox->value() == 0) ui->updateIntervalSpinBox->setValue(4);
    ui->endTimeRadioButton->setChecked(true);
    ui->fontSizeSpinBox->setValue(widgetPtr->fontSize);
    ui->reminderCheckBox->setChecked(widgetPtr->reminderBool);
    ui->reminderBeforeDoneCheckBox->setChecked(widgetPtr->reminderBeforeDoneBool);
    ui->reminderBeforeMins_lineEdit->setText(QString::number(widgetPtr->reminderBeforeMins));
    ui->timeEdit->setTime(widgetPtr->endTime);
    ui->showProgressBarCheckBox->setChecked(widgetPtr->getProgressBarVisibility());
    ui->showEndTimeCheckBox->setChecked(widgetPtr->displayTimeInTitle);

    QColorDialog *colorDialog = new QColorDialog(this);
    colorDialogPtr = colorDialog;
    connect(colorDialog, SIGNAL(currentColorChanged(QColor)), this,  SLOT(setFontColor()));
}


void editTimerWindow::on_createButton_clicked() //button text was renamed to "Start Timer"
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    if(ui->endTimeRadioButton->isChecked())       widgetPtr->setEndTime(ui->timeEdit->time());
    else if(ui->durationRadioButton->isChecked()) widgetPtr->setDuration(ui->hoursTextEdit->text().toInt(), ui->minutesTextEdit->text().toInt());
    widgetPtr->updateTimer.start();
    widgetPtr->reminderBeforeDoneShowedBool = false;
    updateWindowTitle();
    widgetPtr->updateTimeDisplay();
    hide();
}


void editTimerWindow::updateWindowTitle()
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    QString str;
    str = widgetPtr->windowTitleOnly = ui->lineEdit_windowTitle->text();
    if(ui->showEndTimeCheckBox->isChecked()) str.append(" at " + widgetPtr->endTime.toString());
    widgetPtr->setWindowTitle(str);
    widgetPtr->displayTimeInTitle = ui->showEndTimeCheckBox->isChecked();
    setWindowTitle("Edit: " + widgetPtr->windowTitle());
}


editTimerWindow::~editTimerWindow()
{
    delete ui;
}

void editTimerWindow::on_cancelButton_clicked() //button text was renamed to "Close"
{
    hide();
    colorDialogPtr->hide();
}

void editTimerWindow::on_fontColorButton_clicked()
{
    colorDialogPtr->show();
}

void editTimerWindow::redirectColorSlot(QColor color){
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->setTextColor(color);
}

void editTimerWindow::setFontColor(){
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->setTextColor(colorDialogPtr->currentColor());
}

void editTimerWindow::on_fontSizeSpinBox_valueChanged(int arg1)
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->setTextSize(arg1);
}

void editTimerWindow::on_secondsComboBox_currentIndexChanged(int index)
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->sDisplay = index;
}

void editTimerWindow::on_reminderCheckBox_toggled(bool checked)
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->reminderBool = checked;
    }

void editTimerWindow::on_reminderBeforeDoneCheckBox_toggled(bool checked)
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->reminderBeforeDoneBool = checked;
    widgetPtr->reminderBeforeMins = ui->reminderBeforeMins_lineEdit->text().toInt();
}

void editTimerWindow::on_showProgressBarCheckBox_toggled(bool checked)
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->setProgressBarVisibility(checked);
}

void editTimerWindow::on_reminderBeforeMins_lineEdit_textEdited(const QString &arg1)
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->reminderBeforeMins = ui->reminderBeforeMins_lineEdit->text().toInt();
}

void editTimerWindow::on_updateIntervalSpinBox_valueChanged(int arg1)
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->updateTimer.setInterval(ui->updateIntervalSpinBox->value() * 1000); // *1000 because its milliseconds
}

void editTimerWindow::on_lineEdit_windowTitle_textEdited(const QString &arg1)
{
    MyWidget *widgetPtr = (MyWidget*)(this->parent());
    widgetPtr->windowTitleOnly = ui->lineEdit_windowTitle->text();
    updateWindowTitle();
}