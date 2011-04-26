// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "Common/CBuilder.hpp"

#include "RDM/Schemes/CSysB.hpp"
#include "RDM/Schemes/SchemeCSysB.hpp"

#include "RDM/Core/SupportedTypes.hpp"    // supported elements

#include "RDM/Core/LinearAdv2D.hpp"       // supported physics
#include "RDM/Core/LinearAdvSys2D.hpp"    // supported physics
#include "RDM/Core/RotationAdv2D.hpp"     // supported physics

#include "RDM/Scalar/LibScalar.hpp"

using namespace CF::Common;

namespace CF {
namespace RDM {

////////////////////////////////////////////////////////////////////////////////

Common::ComponentBuilder < CellLoop<CSysB,LinearAdv2D> , RDM::ElementLoop, LibCore > CSysB_LinearAdv2D_Builder;

Common::ComponentBuilder < CellLoop<CSysB,LinearAdvSys2D> , RDM::ElementLoop, LibCore > CSysB_LinearAdvSys2D_Builder;

Common::ComponentBuilder < CellLoop<CSysB,RotationAdv2D> , RDM::ElementLoop, LibCore > CSysB_RotationAdv2D_Builder;

////////////////////////////////////////////////////////////////////////////////

} // RDM
} // CF