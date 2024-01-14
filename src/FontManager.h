#pragma once
#include "qutils_global.h"

#include <QFont>
#include <QFontDatabase>
#include <QMap>
#include <QMutex>

namespace qutils {
class QUTILS_EXPORT FontManager
{
public:
    static FontManager *instance();

    bool  addThirdpartyFont(const QString &path, int type);
    QFont fontAt(int type);

private:
    FontManager() = default;

    QMap<int, QFont> m_fontsMap;
};
} // namespace qutils
