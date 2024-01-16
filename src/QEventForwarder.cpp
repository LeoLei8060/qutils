#include "QEventForwarder.h"
#include <QWriteLocker>

namespace qutils {
QMap<QByteArray, QList<QObject *>> QEventForwarder::m_eventsPool;
QReadWriteLock                     QEventForwarder::m_eventLock;
QString                            QEventForwarder::m_lastError;

void QEventForwarder::unSubscribe(QObject *listener, const QByteArray &eventName)
{
    QWriteLocker locker(&m_eventLock);
    int          index = -1;
    if (m_eventsPool.contains(eventName) && (index = m_eventsPool[eventName].indexOf(listener)) >= 0
        && index < m_eventsPool[eventName].count())
        m_eventsPool[eventName].takeAt(index);
}

bool QEventForwarder::subscribe(QObject *listener, const QByteArray &eventName)
{
    QWriteLocker locker(&m_eventLock);
    if (m_eventsPool.contains(eventName)) {
        if (-1 != m_eventsPool[eventName].indexOf(listener)) {
            m_lastError = QString("This object is subscribed to this eventName");
            return false;
        }
        m_eventsPool[eventName].push_back(listener);
        return true;
    } else {
        m_eventsPool.insert(eventName, {listener});
        return true;
    }
}

bool QEventForwarder::publish(const QByteArray  &eventName,
                              Qt::ConnectionType connectionType,
                              QGenericArgument   val0,
                              QGenericArgument   val1,
                              QGenericArgument   val2,
                              QGenericArgument   val3,
                              QGenericArgument   val4,
                              QGenericArgument   val5,
                              QGenericArgument   val6,
                              QGenericArgument   val7,
                              QGenericArgument   val8,
                              QGenericArgument   val9)
{
    QReadLocker locker(&m_eventLock);
    if (!m_eventsPool.contains(eventName)) {
        m_lastError = QString("No objects subscribe to this eventName");
        return false;
    }
    auto        methodName = methodFormatting(eventName);
    QStringList errors;
    auto        listeners = m_eventsPool[eventName];
    locker.unlock();
    for (auto listener : listeners) {
        if (!listener)
            continue;
        auto ret = QMetaObject::invokeMethod(listener,
                                             methodName,
                                             connectionType,
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
        if (!ret)
            errors.append(QString("%1:%2")
                              .arg(listener->metaObject()->className())
                              .arg(listener->objectName()));
    }
    if (errors.isEmpty())
        return true;
    m_lastError = QString("%1 execution failed:[\n").arg(QString(eventName));
    for (auto &err : errors)
        m_lastError += QString("%1;\n").arg(err);
    m_lastError += "]\n";
    return false;
}

} // namespace qutils