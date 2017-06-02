
/*
 * kcmcategoryitem.h
 *
 *  Copyright (C) 2010 David Hubner <hubnerd@ntlworld.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef KCMCATEGORYITEM
#define KCMCATEGORYITEM

#include "kcmtreeitem.h"

//KDE
#include <KCModuleInfo>
#include <QIcon>

class KcmCategoryItem : public KcmTreeItem
{
    public:

        /**
        * Category Tree Item for InfoKcmModel. Holds information about a Category
        *
        * @param module pointer to KCM module
        * @param parent objects parent
        */
        explicit KcmCategoryItem(const KService::Ptr module, KcmTreeItem *parent=0);

        /**
        * Category Tree Item for InfoKcmModel. Holds information about a Category
        *
        * @note Used for root folder objects
        */
        explicit KcmCategoryItem(const QString& category);

        /**
        * Get data of tree item
        */
        QString data() const Q_DECL_OVERRIDE;

        /**
        * Get category of tree item.
        * Set in X-KDE-KInfoCenter-Category
        */
        QString category() const Q_DECL_OVERRIDE;

        /**
        * Gets the item type.
        */
        itemType type() const Q_DECL_OVERRIDE;

        /**
        * Get tree item KCMs Data
        */
        KCModuleInfo kcm() const Q_DECL_OVERRIDE;

        /**
        * Get tree items KCM's weight
        */
        int weight() Q_DECL_OVERRIDE;

        /**
        * Get icon tied to KCM
        */
        QIcon icon() const Q_DECL_OVERRIDE;

        /**
        * Get whatsThis information from KCM
        */
        QString whatsThis() const Q_DECL_OVERRIDE;

        /**
        * Get KCM tree item keywords
        */
        QStringList keywords() const Q_DECL_OVERRIDE;

    private:

        const QString m_category;
};

#endif //KCMCATEGORYITEM

