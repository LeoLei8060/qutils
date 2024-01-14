#include "FontManager.h"

namespace qutils {

FontManager *FontManager::instance()
{
    static FontManager instance;
    return &instance;
}

bool FontManager::addThirdpartyFont(const QString &path, int type)
{
    int fontID = QFontDatabase::addApplicationFont(path);
    if (fontID < 0)
        return false;

    QString fontName = QFontDatabase::applicationFontFamilies(fontID).at(0);
    QFont   font(fontName);
    m_fontsMap[type] = font;
    return true;
}

QFont FontManager::fontAt(int type)
{
    if (m_fontsMap.find(type) != m_fontsMap.end())
        return m_fontsMap[type];
    return QFont();
}

} // namespace qutils
