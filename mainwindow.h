#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "aboutdialog.h"
#include "config.h"
#include "cpuutils.h"
#include "memutils.h"
#include "preferencedialog.h"
#include "processmonitor.h"
#include <QAbstractNativeEventFilter>
#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#define CONFIG_SLIDERVALUE_KEY "MainWindow/SliderValue"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow
  : public QMainWindow
  , public QAbstractNativeEventFilter
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private slots:
    void refresh();

    void on_sliderCtrl_valueChanged(int value);

    void on_processNameFilter_textChanged(const QString& text);

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void recreateTray();

    void on_sliderLabel_clicked();

  private:
    Ui::MainWindow* ui;
    AboutDialog* m_aboutDlg;
    PreferenceDialog* m_preferenceDlg;

    QThread* m_thread;
    ProcessMonitor* m_processMonitor;
    QTimer* m_timer;

    QSystemTrayIcon* trayIcon;
    QMenu* trayMenu;
    QAction* showAction;
    QAction* hideAction;
    QAction* quitAction;

    CpuUtils* m_cpu;
    MemUtils* m_mem;

    QSettings* m_settings;

    int m_back;

    void init();

    void createTray();

    double speedFactor(int sliderValue);

    int sliderValue(double speedFactor);

  protected:
    void closeEvent(QCloseEvent* event) override;

    bool nativeEventFilter(const QByteArray& eventType,
                           void* message,
                           long* result) override;
};
#endif // MAINWINDOW_H
