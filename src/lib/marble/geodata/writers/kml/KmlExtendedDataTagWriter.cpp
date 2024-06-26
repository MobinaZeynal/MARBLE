// SPDX-License-Identifier: LGPL-2.1-or-later
//
// SPDX-FileCopyrightText: 2010 Gaurav Gupta <1989.gaurav@googlemail.com>
//


#include "KmlExtendedDataTagWriter.h"

#include "GeoDataTypes.h"
#include "GeoWriter.h"
#include "KmlElementDictionary.h"
#include "GeoDataExtendedData.h"
#include "GeoDataData.h"
#include "GeoDataSchemaData.h"

#include <QHash>

namespace Marble
{

static GeoTagWriterRegistrar s_writerExtendedData( GeoTagWriter::QualifiedName( GeoDataTypes::GeoDataExtendedDataType,
                                                                            kml::kmlTag_nameSpaceOgc22 ),
                                               new KmlExtendedDataTagWriter() );


bool KmlExtendedDataTagWriter::write( const GeoNode *node,
                               GeoWriter& writer ) const
{
    const GeoDataExtendedData *extended = static_cast<const GeoDataExtendedData*>( node );

    writer.writeStartElement( kml::kmlTag_ExtendedData );
    
    QHash< QString, GeoDataData >::const_iterator begin = extended->constBegin();
    QHash< QString, GeoDataData >::const_iterator end = extended->constEnd();

    for( QHash< QString, GeoDataData >::const_iterator i = begin; i != end; ++i ){
        writeElement( &i.value(), writer );
    }

    for( const GeoDataSchemaData &schemaData: extended->schemaDataList() ) {
        writeElement( &schemaData, writer );
    }

    writer.writeEndElement();

    return true;
}

}
