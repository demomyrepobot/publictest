/*
 * Copyright (C) 2015-2022 Département de l'Instruction Publique (DIP-SEM)
 *
 * Copyright (C) 2013 Open Education Foundation
 *
 * Copyright (C) 2010-2013 Groupement d'Intérêt Public pour
 * l'Education Numérique en Afrique (GIP ENA)
 *
 * This file is part of OpenBoard.
 *
 * OpenBoard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License,
 * with a specific linking exception for the OpenSSL project's
 * "OpenSSL" library (or with modified versions of it that use the
 * same license as the "OpenSSL" library).
 *
 * OpenBoard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenBoard. If not, see <http://www.gnu.org/licenses/>.
 */




#ifndef UBDOCUMENTPROXY_H_
#define UBDOCUMENTPROXY_H_

#include <QtGui>

#include "frameworks/UBStringUtils.h"

class UBGraphicsScene;

class UBDocumentProxy
{
    friend class UBPersistenceManager;

    public:

        UBDocumentProxy();
        UBDocumentProxy(const UBDocumentProxy &rValue);
        UBDocumentProxy(const QString& pPersistencePath);

        virtual ~UBDocumentProxy();

        std::shared_ptr<UBDocumentProxy> deepCopy() const;
        bool theSameDocument(std::shared_ptr<UBDocumentProxy> proxy);

        QString persistencePath() const;

        void setPersistencePath(const QString& pPersistencePath);

        void setMetaData(const QString& pKey , const QVariant& pValue);
        QVariant metaData(const QString& pKey) const;
        QMap<QString, QVariant> metaDatas() const;

        QString name() const;
        QString groupName() const;
        QDateTime documentDate();

        //For display purposes
        QString documentDateLittleEndian()
        {
            if (mDocumentDateLittleEndian.isEmpty())
            {
                mDocumentDateLittleEndian = UBStringUtils::toLittleEndian(documentDate());
            }

            return mDocumentDateLittleEndian;
        }

        QString documentUpdatedAtLittleEndian()
        {
            if (mDocumentUpdatedAtLittleEndian.isEmpty())
            {
                mDocumentUpdatedAtLittleEndian = UBStringUtils::toLittleEndian(lastUpdate());
            }

            return mDocumentUpdatedAtLittleEndian;
        }

        QDateTime lastUpdate();


        QSize defaultDocumentSize() const;
        void setDefaultDocumentSize(QSize pSize);
        void setDefaultDocumentSize(int pWidth, int pHeight);

        QUuid uuid() const;
        void setUuid(const QUuid& uuid);

        bool isModified() const;

        int pageCount();

        int pageDpi();
        void setPageDpi(int dpi);

        bool isWidgetCompatible(const QUuid& uuid) const;
        void setWidgetCompatible(const QUuid& uuid, bool compatible);
        
        bool testAndResetCleanupNeeded();

        int lastVisitedSceneIndex() const;
        void setLastVisitedSceneIndex(int lastVisitedSceneIndex);

        bool isInFavoriteList() const;
        void setIsInFavoristeList(bool isInFavoristeList);

    protected:
        void setPageCount(int pPageCount);
        int incPageCount();
        int decPageCount();

    private:

        void init();

        QString mPersistencePath;

        QString mDocumentDateLittleEndian;
        QString mDocumentUpdatedAtLittleEndian;

        QMap<QString, QVariant> mMetaDatas;

        bool mIsModified;

        int mPageCount;

        int mPageDpi;

        QMap<QUuid, bool> mWidgetCompatibility;
        
        bool mNeedsCleanup;

       int mLastVisitedIndex;

       bool mIsInFavoriteList;
};

inline bool operator==(const UBDocumentProxy &proxy1, const UBDocumentProxy &proxy2)
{
    return proxy1.persistencePath() == proxy2.persistencePath();
}

inline uint qHash(const UBDocumentProxy &key)
{
    return qHash(key.persistencePath());
}


#endif /* UBDOCUMENTPROXY_H_ */
