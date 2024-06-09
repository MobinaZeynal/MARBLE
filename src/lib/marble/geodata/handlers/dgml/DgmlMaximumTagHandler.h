/*
    SPDX-FileCopyrightText: 2008 Nikolas Zimmermann <zimmermann@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARBLE_DGML_MAXIMUMTAGHANDLER_H
#define MARBLE_DGML_MAXIMUMTAGHANDLER_H

#include "GeoTagHandler.h"

namespace Marble
{
namespace dgml
{

class DgmlMaximumTagHandler : public GeoTagHandler
{
 public:
    GeoNode* parse(GeoParser&) const override;
};

}
}

#endif
