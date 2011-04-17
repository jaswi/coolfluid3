// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_RDM_SchemeCSysB_hpp
#define CF_RDM_SchemeCSysB_hpp

#include "Math/MathChecks.hpp"

#include "RDM/SchemeBase.hpp"

/////////////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace RDM {

///////////////////////////////////////////////////////////////////////////////////////

template < typename SF, typename QD, typename PHYS >
class RDM_API CSysB::Scheme : public SchemeBase<SF,QD,PHYS> {

public: // typedefs

  /// base class type
  typedef SchemeBase<SF,QD,PHYS> B;

  /// pointers
  typedef boost::shared_ptr< Scheme > Ptr;
  typedef boost::shared_ptr< Scheme const> ConstPtr;

public: // functions

  /// Contructor
  /// @param name of the component
  Scheme ( const std::string& name ) : SchemeBase<SF,QD,PHYS>(name)
  {
    for(Uint n = 0; n < SF::nb_nodes; ++n)
      DvPlus[n].setZero();
  }

  /// Virtual destructor
  virtual ~Scheme() {};

  /// Get the class name
  static std::string type_name () { return "CSysB.Scheme<" + SF::type_name() + ">"; }
	
  /// execute the action
  virtual void execute ();

protected: // data

  /// The operator L in the advection equation Lu = f
  /// Matrix Ki_n stores the value L(N_i) at each quadrature point for each shape function N_i
  typename B::PhysicsMT  Ki_n [SF::nb_nodes];
  /// sum of Lplus to be inverted
  typename B::PhysicsMT  sumLplus;
  /// inverse Ki+ matix
  typename B::PhysicsMT  InvKi_n;
  /// right eigen vector matrix
  typename B::PhysicsMT  Rv;
  /// left eigen vector matrix
  typename B::PhysicsMT  Lv;
  /// diagonal matrix with eigen values
  typename B::PhysicsVT  Dv;
  /// temporary hold of Values of the operator L(u) computed in quadrature points.
  typename B::PhysicsVT  LUwq;
  /// diagonal matrix with positive eigen values
  typename B::PhysicsVT  DvPlus [SF::nb_nodes];
  /// dissipative part of the residual coming from the N scheme
  typename B::SolutionMT Phi_n_diss;
  /// blending parameter
  Real theta;
  /// helper variables to compute the blending parameter
  Real sum_phi;
  Real sum_phi_N;
};

/////////////////////////////////////////////////////////////////////////////////////

template<typename SF,typename QD, typename PHYS>
void CSysB::Scheme<SF, QD,PHYS>::execute()
{
  // get element connectivity

  const Mesh::CTable<Uint>::ConstRow nodes_idx = this->connectivity_table->array()[B::idx()];

  B::interpolate( nodes_idx );

  // L(N)+ @ each quadrature point

  for(Uint q=0; q < QD::nb_points; ++q)
  {

    PHYS::compute_properties(B::X_q.row(q),
                             B::U_q.row(q),
                             B::dUdX[XX].row(q).transpose(),
                             B::dUdX[YY].row(q).transpose(),
                             B::phys_props);

    for(Uint n=0; n < SF::nb_nodes; ++n)
    {
      B::dN[XX] = B::dNdX[XX](q,n);
      B::dN[YY] = B::dNdX[YY](q,n);

      PHYS::jacobian_eigen_structure(B::phys_props,
                                     B::X_q.row(q),
                                     B::U_q.row(q),
                                     B::dN,
                                     Rv,
                                     Lv,
                                     Dv );

      // diagonal matrix of positive eigen values

      DvPlus[n] = Dv.unaryExpr(std::ptr_fun(plus));

      Ki_n[n] = Rv * DvPlus[n].asDiagonal() * Lv;
    }

    // compute L(u)

    PHYS::Lu(B::phys_props,
             B::X_q.row(q),
             B::U_q.row(q),
             B::dUdX[XX].row(q).transpose(),
             B::dUdX[YY].row(q).transpose(),
             B::dFdU,
             B::LU );

    // compute L(N)+

    sumLplus = Ki_n[0];
    for(Uint n = 1; n < SF::nb_nodes; ++n)
      sumLplus += Ki_n[n];

    // invert the sum L plus

    InvKi_n = sumLplus.inverse();

    // compute the phi_i LDA intergral

    LUwq = InvKi_n * B::LU * B::wj[q];

    for(Uint n = 0; n < SF::nb_nodes; ++n)
      B::Phi_n.row(n) +=  Ki_n[n] * LUwq;

    // compute the phi_i LDA intergral


    // N dissipation
    Phi_n_diss.setZero();
    for(Uint i = 0; i < SF::nb_nodes; ++i)
    {
      LUwq.setZero();
      for(Uint j = 0; j < SF::nb_nodes; ++j)
      {
        if (i==j) continue;
        LUwq += Ki_n[j] * ( B::U_n.row(i).transpose() - B::U_n.row(j).transpose() );
      }
      Phi_n_diss.row(i) +=  Ki_n[i] * InvKi_n * LUwq * B::wj[q];
    }

    // compute the wave_speed for scaling the update

    for(Uint n = 0; n < SF::nb_nodes; ++n)
      (*B::wave_speed)[nodes_idx[n]][0] += DvPlus[n].maxCoeff() * B::wj[q];


  } // loop qd points

  // update the residual
  
  for (Uint v=0; v < PHYS::neqs; ++v)
  {
    sum_phi   = 0.0;
    sum_phi_N = 0.0;
    for (Uint n=0; n<SF::nb_nodes; ++n)
    {
        sum_phi   += B::Phi_n(n,v); // + Phi_n_diss(n,v);
        sum_phi_N += std::abs(B::Phi_n(n,v) + Phi_n_diss(n,v));
    }

    theta = Math::MathChecks::is_not_zero(sum_phi_N) ? std::abs(sum_phi)/sum_phi_N : 0.0;

    for (Uint n=0; n<SF::nb_nodes; ++n)
    {
      (*B::residual)[nodes_idx[n]][v] += B::Phi_n(n,v) + theta * Phi_n_diss(n,v);
    }

  } // loop over equations
}

////////////////////////////////////////////////////////////////////////////////////

} // RDM
} // CF

/////////////////////////////////////////////////////////////////////////////////////

#endif // CF_RDM_SchemeCSysB_hpp