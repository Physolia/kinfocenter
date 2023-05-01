/*
    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
    SPDX-FileCopyrightText: 2021 Harald Sitter <sitter@kde.org>
*/

#include <KPluginFactory>
#include <KQuickConfigModule>

#include <CommandOutputContext.h>

class KCMWayland : public KQuickConfigModule
{
    Q_OBJECT
public:
    explicit KCMWayland(QObject *parent, const KPluginMetaData &data)
        : KQuickConfigModule(parent, data)
    {
        auto outputContext = new CommandOutputContext(QStringLiteral("wayland-info"), {}, parent);
        qmlRegisterSingletonInstance("org.kde.kinfocenter.wayland.private", 1, 0, "InfoOutputContext", outputContext);
    }
};

K_PLUGIN_CLASS_WITH_JSON(KCMWayland, "kcm_wayland.json")

#include "main.moc"
