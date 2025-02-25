/*
 * SPDX-FileCopyrightText: 2020 Carl Schwan <carl@carlschwan.eu>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QAbstractTableModel>

class NetworkModel : public QAbstractListModel
{
    Q_OBJECT

public:
    struct MyNIC {
        QString name;
        QString addr;
        QString netmask;
        bool state;
        QString type;
        QString HWaddr;
    };

    enum Roles {
        NameRole = Qt::UserRole + 1,
        AddrRole,
        NetMaskRole,
        TypeRole,
        HWAddrRole,
        StateRole,
    };

    explicit NetworkModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE void update();

private:
    QList<MyNIC *> m_nics;
};
