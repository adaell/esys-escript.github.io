// @HEADER
// ***********************************************************************
//
//           Panzer: A partial differential equation assembly
//       engine for strongly coupled complex multiphysics systems
//                 Copyright (2011) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Roger P. Pawlowski (rppawlo@sandia.gov) and
// Eric C. Cyr (eccyr@sandia.gov)
// ***********************************************************************
// @HEADER

#ifndef EXAMPLE_SIMPLE_SOURCE_IMPL_HPP
#define EXAMPLE_SIMPLE_SOURCE_IMPL_HPP

#include <cmath>

#include "Panzer_BasisIRLayout.hpp"
#include "Panzer_Workset.hpp"
#include "Panzer_Workset_Utilities.hpp"

namespace Example {

//**********************************************************************
template <typename EvalT,typename Traits>
SimpleSource<EvalT,Traits>::SimpleSource(const std::string & name,
                                         const panzer::IntegrationRule & ir,
                                         const bool curvilinear)
  : curvilinear_(curvilinear)
{
  using Teuchos::RCP;

  Teuchos::RCP<PHX::DataLayout> data_layout = ir.dl_scalar;
  ir_degree = ir.cubature_degree;

  source = PHX::MDField<ScalarT,Cell,Point>(name, data_layout);

  this->addEvaluatedField(source);
  
  std::string n = "Simple Source";
  this->setName(n);
}

//**********************************************************************
template <typename EvalT,typename Traits>
void SimpleSource<EvalT,Traits>::postRegistrationSetup(typename Traits::SetupData sd,           
                                                       PHX::FieldManager<Traits>& /* fm */)
{
  ir_index = panzer::getIntegrationRuleIndex(ir_degree,(*sd.worksets_)[0], this->wda);
}

//**********************************************************************
template <typename EvalT,typename Traits>
void SimpleSource<EvalT,Traits>::evaluateFields(typename Traits::EvalData workset)
{ 
  using panzer::index_t;
  auto ip_coordinates = workset.int_rules[ir_index]->ip_coordinates.get_static_view();
  auto source_v = source.get_static_view();

  const bool curv = this->curvilinear_;

  Kokkos::parallel_for ("SimpleSource", workset.num_cells, KOKKOS_LAMBDA (const index_t cell) {
      for (int point = 0; point < source_v.extent_int(1); ++point) {
	const double& x = ip_coordinates(cell,point,0);
	const double& y = ip_coordinates(cell,point,1);
	 
    if (curv) {
      source_v(cell,point) = 0.0;
    } else{
      source_v(cell,point) = 8.0*M_PI*M_PI*std::sin(2.0*M_PI*x)*std::sin(2.0*M_PI*y);
    }
      }
    });
  Kokkos::fence();
}

//**********************************************************************
}

#endif
