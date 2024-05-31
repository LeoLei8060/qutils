#pragma once

#include <memory>
#include <QDebug>
#include <QList>
#include <QMap>
#include <QObject>
#include <QReadWriteLock>

namespace qutils {

#define EVENT_METHOD_PREFIX "event_"

class QEventForwarder : public QObject
{
    Q_OBJECT
public:
    static void unsubscribe(QObject *listener, const QByteArray &eventName);

    static bool subscribe(QObject *listener, const QByteArray &eventName);

    static bool publish(const QByteArray  &eventName,
                        Qt::ConnectionType connectionType,
                        QGenericArgument   val0 = QGenericArgument(),
                        QGenericArgument   val1 = QGenericArgument(),
                        QGenericArgument   val2 = QGenericArgument(),
                        QGenericArgument   val3 = QGenericArgument(),
                        QGenericArgument   val4 = QGenericArgument(),
                        QGenericArgument   val5 = QGenericArgument(),
                        QGenericArgument   val6 = QGenericArgument(),
                        QGenericArgument   val7 = QGenericArgument(),
                        QGenericArgument   val8 = QGenericArgument(),
                        QGenericArgument   val9 = QGenericArgument());

    static inline bool publish(const QByteArray &eventName,
                               QGenericArgument  val0 = QGenericArgument(),
                               QGenericArgument  val1 = QGenericArgument(),
                               QGenericArgument  val2 = QGenericArgument(),
                               QGenericArgument  val3 = QGenericArgument(),
                               QGenericArgument  val4 = QGenericArgument(),
                               QGenericArgument  val5 = QGenericArgument(),
                               QGenericArgument  val6 = QGenericArgument(),
                               QGenericArgument  val7 = QGenericArgument(),
                               QGenericArgument  val8 = QGenericArgument(),
                               QGenericArgument  val9 = QGenericArgument())
    {
        return publish(eventName,
                       Qt::AutoConnection,
                       val0,
                       val1,
                       val2,
                       val3,
                       val4,
                       val5,
                       val6,
                       val7,
                       val8,
                       val9);
    }

    static inline QString getLastError() { return m_lastErrorMessage; }

    static inline void clearEvents()
    {
        QWriteLocker locker(&m_subscriptionLock);
        m_eventSubscriptions.clear();
    }

    static inline QByteArray formatMethodName(const QByteArray &eventName)
    {
        return EVENT_METHOD_PREFIX + eventName;
    }

private:
    static QMap<QByteArray, QList<QObject *>> m_eventSubscriptions;

    static QReadWriteLock m_subscriptionLock;

    static QString m_lastErrorMessage;
};
} // namespace qutils