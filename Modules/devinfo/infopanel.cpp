/*
 *  SPDX-FileCopyrightText: 2009 David Hubner <hubnerd@ntlworld.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "infopanel.h"

// Solid
#include <solid/device.h>

#include <QIcon>
#include <QLabel>

#include "devinfo.h"
#include "qvlistlayout.h"

InfoPanel::InfoPanel(QWidget *parent, DevInfoPlugin *stat)
    : QGroupBox(i18n("Device Information"), parent)
    , status(stat)
{
    setMinimumWidth(300);

    setInfoPanelLayout();
    setDefaultText();
    adjustSize();

    setWhatsThis(i18nc("Info Panel Whats This", "Shows information about the currently selected device."));
}

InfoPanel::~InfoPanel()
{
    delete top;
    delete bottom;
}

void InfoPanel::setInfoPanelLayout()
{
    vLayout = setAlignedLayout(this);
    setLayout(vLayout);
    setTopWidgetLayout(true);

    setBottomWidgetLayout(new QVListLayout(), true);
}

void InfoPanel::setDefaultText()
{
    QLabel *defaultText = new QLabel();
    QFont font;

    font.setBold(true);

    defaultText->setAlignment(Qt::AlignHCenter);
    defaultText->setFont(font);
    defaultText->setText(i18n("\nSolid Based Device Viewer Module"));

    QVBoxLayout *lay = static_cast<QVBoxLayout *>(top->layout());

    lay->addWidget(setDevicesIcon(QIcon::fromTheme(QStringLiteral("kde"))), 0, Qt::AlignHCenter);
    lay->addWidget(defaultText, 0, Qt::AlignHCenter);
}

void InfoPanel::setTopWidgetLayout(bool isInit)
{
    if (!isInit) {
        delete top;
    }
    top = new QWidget(this);

    vLayout->addWidget(top);
    top->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    top->setLayout(setAlignedLayout(top));
}

QVBoxLayout *InfoPanel::setAlignedLayout(QWidget *parent, int spacingHeight)
{
    QVBoxLayout *lay = new QVBoxLayout(parent);
    lay->insertSpacing(0, spacingHeight);
    lay->setAlignment(Qt::AlignTop);

    return lay;
}

void InfoPanel::setBottomWidgetLayout(QVListLayout *lay, bool isInit)
{
    if (!isInit) {
        delete bottom;
    }

    bottom = new QWidget(this);
    vLayout->addWidget(bottom);

    bottom->setLayout(lay);
}

void InfoPanel::setBottomInfo(QVListLayout *lay)
{
    lay->setAlignment(Qt::AlignTop);
    lay->insertSpacing(0, 10);
    setBottomWidgetLayout(lay);
}

QLabel *InfoPanel::setDevicesIcon(const QIcon &deviceIcon)
{
    QLabel *iconLabel = new QLabel();

    iconLabel->setPixmap(deviceIcon.pixmap(QSize(70, 50)));
    return iconLabel;
}

void InfoPanel::setTopInfo(const QIcon &deviceIcon, Solid::Device *device)
{
    setTopWidgetLayout();
    QVListLayout *tLayout = static_cast<QVListLayout *>(top->layout());

    tLayout->addWidget(setDevicesIcon(deviceIcon), 0, Qt::AlignHCenter);

    const QStringList labels{i18n("Description: "),
                             device->description(),
                             i18n("Product: "),
                             device->product(),
                             i18n("Vendor: "),
                             friendlyString(device->vendor())};

    status->updateStatus(device->udi());
    tLayout->applyQListToLayout(labels);
}

QString InfoPanel::friendlyString(const QString &input, const QString &blankName)
{
    if (input.isEmpty()) {
        return QString(blankName);
    }
    if (input.length() >= 40) {
        return input.left(39);
    }

    return input;
}

QString InfoPanel::convertTf(bool b)
{
    if (b) {
        return i18n("Yes");
    }
    return i18n("No");
}

#include "moc_infopanel.cpp"
