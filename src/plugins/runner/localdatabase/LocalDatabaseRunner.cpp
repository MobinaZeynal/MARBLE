// SPDX-License-Identifier: LGPL-2.1-or-later
//
// SPDX-FileCopyrightText: 2010 Torsten Rahn <rahn@kde.org>
// SPDX-FileCopyrightText: 2013 Bernhard Beschow <bbeschow@cs.tu-berlin.de>
//

#include "LocalDatabaseRunner.h"

#include "MarbleModel.h"
#include "MarblePlacemarkModel.h"
#include "GeoDataPlacemark.h"
#include "GeoDataCoordinates.h"
#include "GeoDataLatLonAltBox.h"

#include "MarbleDebug.h"
#include <QString>
#include <QVector>

#include <QtDebug>

namespace Marble
{

LocalDatabaseRunner::LocalDatabaseRunner(QObject *parent) :
    SearchRunner(parent)
{
}

LocalDatabaseRunner::~LocalDatabaseRunner()
{

}

void LocalDatabaseRunner::search( const QString &searchTerm, const GeoDataLatLonBox &preferred )
{
    QVector<GeoDataPlacemark*> vector;

    if (model()) {
        const QAbstractItemModel * placemarkModel = model()->placemarkModel();

        if (placemarkModel) {
            QModelIndexList resultList;
            QModelIndex firstIndex = placemarkModel->index( 0, 0 );
            resultList = placemarkModel->match( firstIndex,
                                    Qt::DisplayRole, searchTerm, -1,
                                    Qt::MatchStartsWith );

            bool const searchEverywhere = preferred.isEmpty();
            for ( const QModelIndex& index: resultList ) {
                if( !index.isValid() ) {
                    mDebug() << "invalid index!!!";
                    continue;
                }
                GeoDataPlacemark *placemark = dynamic_cast<GeoDataPlacemark*>(qvariant_cast<GeoDataObject*>( index.data( MarblePlacemarkModel::ObjectPointerRole )));
                if ( placemark &&
                     ( searchEverywhere || preferred.contains( placemark->coordinate() ) ) ) {
                    vector.append( new GeoDataPlacemark( *placemark ));
                }
            }
        }
    }

    emit searchFinished( vector );
}

}

#include "moc_LocalDatabaseRunner.cpp"
