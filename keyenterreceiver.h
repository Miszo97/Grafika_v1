#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H

#include <QObject>

class keyEnterReceiver : public QObject
{
    Q_OBJECT
public:
    explicit keyEnterReceiver(QObject *parent = 0);

protected:
     bool eventFilter(QObject* obj, QEvent* event);

signals:

public slots:
};

#endif // KEYENTERRECEIVER_H
