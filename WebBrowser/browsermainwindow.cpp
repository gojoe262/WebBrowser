#include "browsermainwindow.h"
#include "ui_browsermainwindow.h"

BrowserMainWindow::BrowserMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrowserMainWindow)
{
    home = DEFAULT_HOME_PAGE;

    qputenv("QTWEBKIT_PLUGIN_PATH", "./plugins");
    this->setWindowIcon(QIcon("./icons/go.ico"));


    ui->setupUi(this);
    this->setCentralWidget(ui->tabWidget);

    ui->lineEdit->setMinimumWidth(300);

    ui->toolBarTopRight->addWidget(ui->toolButtonAddTab);
    ui->toolBarTopRight->addWidget(ui->lineEdit);
    ui->toolBarTopRight->addWidget(ui->toolButtonHome);
    ui->tabWidget->setCornerWidget(ui->toolBarTopRight, Qt::TopRightCorner);


    ui->toolBarTopLeft->addWidget(ui->toolButtonBack);
    ui->toolBarTopLeft->addWidget(ui->toolButtonForward);
    ui->tabWidget->setCornerWidget(ui->toolBarTopLeft, Qt::TopLeftCorner);


    ui->toolBarBottom->addWidget(ui->progressBar);

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseTab(int)));

    AddTab();
}

BrowserMainWindow::~BrowserMainWindow()
{
    for(int i = 0; i < ui->tabWidget->count(); i++)
        CloseTab(i);
    delete ui;
}


QWebView* BrowserMainWindow::CurrentWebpage()
{
    return (QWebView*) ui->tabWidget->currentWidget();
}

QWebView* BrowserMainWindow::CurrentWebpage(int index)
{
    return (QWebView*) ui->tabWidget->widget(index);
}


void BrowserMainWindow::AddTab(const QString inUrl)
{
    ui->tabWidget->addTab(new QWebView(), "");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);

    connect(CurrentWebpage(), SIGNAL(loadStarted()), this, SLOT(LoadStarted()));
    connect(CurrentWebpage(), SIGNAL(loadProgress(int)), this, SLOT(LoadProgress(int)));
    connect(CurrentWebpage(), SIGNAL(loadFinished(bool)), this, SLOT(LoadFinished(bool)));

    CurrentWebpage()->settings()->setAttribute(QWebSettings::PluginsEnabled, true);


    CurrentWebpage()->load(QUrl::fromUserInput(inUrl));

}

void BrowserMainWindow::AddTab()
{
    AddTab(home);
}


void BrowserMainWindow::CloseTab(int index)
{
    delete CurrentWebpage(index);
    if(ui->tabWidget->count() == 0)
        this->close();
}

void BrowserMainWindow::on_toolButtonAddTab_clicked()
{
    AddTab();
}

void BrowserMainWindow::on_lineEdit_returnPressed()
{
    CurrentWebpage()->load(QUrl::fromUserInput(ui->lineEdit->text()));
}

void BrowserMainWindow::LoadStarted()
{
    ui->toolBarBottom->show();
    CurrentWebpage()->setFocus();
}

void BrowserMainWindow::LoadProgress(int progress)
{
    ui->progressBar->setValue(progress);
}

void BrowserMainWindow::LoadFinished(bool ok)
{
    ui->toolBarBottom->hide();
    ui->lineEdit->setText(CurrentWebpage()->url().toString());
    if(ok)
        ChangeTitles();
    else
        CurrentWebpage()->setHtml("Webpage Not Found: " + ui->lineEdit->text());
}

void BrowserMainWindow::ChangeTitles()
{
    for(int i = 0; i < ui->tabWidget->count(); i++)
    {
        QString tabTitle = CurrentWebpage(i)->title();
        if(tabTitle.length() > TAB_TITLE_MAX_LEN)
        {
            tabTitle = tabTitle.mid(0, TAB_TITLE_MAX_LEN);
            tabTitle.append("...");
        }
        ui->tabWidget->setTabText(i, tabTitle);
    }
    this->on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}

void BrowserMainWindow::on_tabWidget_currentChanged(int index)
{
    if(ui->tabWidget->count() > 0)
    {
        ui->lineEdit->setText(CurrentWebpage(index)->url().toString());
        if(index > -1)
            this->setWindowTitle(CurrentWebpage(index)->title() + "  -  " + WINDOW_TITLE);
        else
            this->setWindowTitle(WINDOW_TITLE);
    }
}

void BrowserMainWindow::on_toolButtonBack_clicked()
{
    CurrentWebpage()->back();
}

void BrowserMainWindow::on_toolButtonForward_clicked()
{
    CurrentWebpage()->forward();
}

void BrowserMainWindow::on_toolButtonHome_clicked()
{
    CurrentWebpage()->load(home);
}


