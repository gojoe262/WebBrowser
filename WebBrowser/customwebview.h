#ifndef CUSTOMWEBVIEW_H
#define CUSTOMWEBVIEW_H
#include <QWebView>

class CustomWebView : public QWebView
{
public:
    CustomWebView();
protected:
    keyPressEvent(QKeyEvent *e);
};

#endif // CUSTOMWEBVIEW_H
