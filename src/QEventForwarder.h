#pragma once

#include <cxxabi.h>
#include <memory>
#include <QDebug>
#include <QList>
#include <QMap>
#include <QObject>
#include <QReadWriteLock>

#define METHOD_PREFIX "onEvent_"

class QEventForwarder : public QObject
{
    Q_OBJECT
public:
    static void unSubscribe(QObject *listener, const QByteArray &eventName);

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

    static inline QString get_Errors() { return m_lastError; }

    static inline void clearEvents()
    {
        QWriteLocker locker(&m_eventLock);
        m_eventsPool.clear();
    }

    static inline QByteArray methodFormatting(const QByteArray &eventName)
    {
        return METHOD_PREFIX + eventName;
    }

private:
    static QMap<QByteArray, QList<QObject *>> m_eventsPool;

    static QReadWriteLock m_eventLock;

    static QString m_lastError;
};


/*
* Suggested to use type inference:
*   Use the third-party library https://github.com/Neargye/nameof to implement type inference, abandoning the Q_ARG macro.
* The current version does not provide this method temporarily.
*/
//template<typename T>
//QGenericArgument toArg(T &&val)
//{
//    return QGenericArgument(NAMEOF_TYPE_EXPR(val).data(), &val);
//}
