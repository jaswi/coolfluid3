// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "sdm/Tags.hpp"

namespace cf3 {
namespace sdm {

////////////////////////////////////////////////////////////////////////////////

const char * Tags::fields()         { return "fields"; }
const char * Tags::actions()        { return "actions"; }
const char * Tags::solution_vars()  { return "solution_vars"; }
const char * Tags::input_vars()     { return "input_vars"; }
const char * Tags::solution_order() { return "solution_order"; }

const char * Tags::solution()       { return "solution"; }
const char * Tags::wave_speed()     { return "wave_speed"; }
const char * Tags::update_coeff()   { return "update_coefficient"; }
const char * Tags::residual()       { return "residual"; }
const char * Tags::jacob_det()      { return "jacobian_determinant"; }
const char * Tags::delta()          { return "delta"; }
const char * Tags::plane_jacob_normal()  { return "plane_jacobian_normal"; }
const char * Tags::shared_caches()  { return "shared_caches"; }
const char * Tags::L2norm()         { return "L2norm"; }

////////////////////////////////////////////////////////////////////////////////

} // sdm
} // cf3
