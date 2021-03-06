// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the BCs of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "common/Builder.hpp"

#include "sdm/BCWeak.hpp"

//////////////////////////////////////////////////////////////////////////////

namespace cf3 {
namespace sdm {

//////////////////////////////////////////////////////////////////////////////

common::ComponentBuilder<BCNull,BC,LibSDM> bcnull_builder;

/////////////////////////////////////////////////////////////////////////////

} // sdm
} // cf3
