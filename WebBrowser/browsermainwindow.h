#ifndef BROWSERMAINWINDOW_H
#define BROWSERMAINWINDOW_H

#include <QMainWindow>
#include <QWebView>


const int TAB_TITLE_MAX_LEN = 10;
const QString WINDOW_TITLE = "Joe's Browser";
const QString SEARCH_URL = "https://www.google.com/search?q=";
const QString DEFAULT_HOME_PAGE = "https://www.google.com/";


namespace Ui {
class BrowserMainWindow;
}

class BrowserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrowserMainWindow(QWidget *parent = 0);
    ~BrowserMainWindow();

private slots:
    //Slot
    //Adds a new tab
    void on_toolButtonAddTab_clicked();

    //Slot
    //Close Tab at the specified index
    void CloseTab(int index);


    //Slot
    //Shows the bottom tool bar (containing the progress bar)
    void LoadStarted();

    //Slot
    //Updates progress bar's value.
    void LoadProgress(int progress);

    //Slot
    //If ok, ...
    void LoadFinished(bool ok);


    //Slot
    //Loads the url in lineEdit to the
    //current webpage.
    void on_lineEdit_returnPressed();

    //Slot
    //If tab count is greater than 0, then
    //window title is updated. Else program is closed.
    void on_tabWidget_currentChanged(int index);

    void on_toolButtonBack_clicked();

    void on_toolButtonForward_clicked();

    void on_toolButtonHome_clicked();

private:
    Ui::BrowserMainWindow *ui;

    //Qstring that represents the home page
    QString home;

    //Gets the current QWebView
    QWebView* CurrentWebpage();

    //Gets the QWebView at index
    QWebView* CurrentWebpage(int index);

    //Add a new tab with the specified url
    void AddTab(const QString inUrl);

    //Add a new tab. Page loaded will be home
    void AddTab();

    //Updates all the tiles on each tab and sets
    //the window title to the current webpage title.
    void ChangeTitles();

};

#endif // BROWSERMAINWINDOW_H
