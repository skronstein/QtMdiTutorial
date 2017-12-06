#ifndef EDITTIMERWINDOW_H
#define EDITTIMERWINDOW_H

#include <QDialog>
#include <QColorDialog>
#include <QColor>

namespace Ui {
class editTimerWindow;
}

class editTimerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editTimerWindow(QWidget *parent = 0);
    ~editTimerWindow();
    void changeToEndTime();
    void changeToDuration();

signals:
    void redirectTime();

public slots:
    void setFontColor();
    void redirectColorSlot(QColor color);

private slots:
    void updateWindowTitle();

    void on_cancelButton_clicked();

    void on_createButton_clicked();

    void on_fontColorButton_clicked();

    void on_fontSizeSpinBox_valueChanged(int arg1);

    void on_secondsComboBox_currentIndexChanged(int index);

    void on_reminderCheckBox_toggled(bool checked);

    void on_reminderBeforeDoneCheckBox_toggled(bool checked);

    void on_showProgressBarCheckBox_toggled(bool checked);

    void on_reminderBeforeMins_lineEdit_textEdited(const QString &arg1);

    void on_updateIntervalSpinBox_valueChanged(int arg1);

    void on_lineEdit_windowTitle_textEdited(const QString &arg1);

    void on_hoursTextEdit_textEdited(const QString &arg1);

    void on_minutesTextEdit_textEdited(const QString &arg1);

    void on_timeEdit_timeChanged(const QTime &time);

private:
    Ui::editTimerWindow *ui;
    QColorDialog *colorDialogPtr;
};

#endif // EDITTIMERWINDOW_H
