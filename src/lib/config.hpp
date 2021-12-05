/*!
 * \file
 * \brief Конфиг файл
 */
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QtGlobal>
#include <QString>

namespace config
{
    //! Название программы
    const char applicationName[] = QT_TRANSLATE_NOOP("Config", "Call Center");
    //! Версия программы
    const char applicationVersion[] = "20211205";
    //! Название файла с пользователей
    const QString fileUsers = "users.tnb";
    //! Настройки администратора и самой фирмы Call Center
    const QString fileCalls = "calls.tnb";

    const QString nameManagers = "Call Center Manager";
    const QString nameAdmin = "CallCenterAdmin";
    const QString passwordAdmin = "adminCallCenter";
    const QString bankNumCallCenter = "12345678911123456789";
    const QString cityCallCenter = "Krasnoyarsk";
    const QString innCallCenter = "9876654321";
    const QString numberCallCenter = "+79509777777";

}


#endif // CONFIG_HPP
