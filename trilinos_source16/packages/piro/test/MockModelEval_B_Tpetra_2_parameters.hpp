// @HEADER
// ************************************************************************
//
//        Piro: Strategy package for embedded analysis capabilitites
//                  Copyright (2010) Sandia Corporation
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
// Questions? Contact Andy Salinger (agsalin@sandia.gov), Sandia
// National Laboratories.
//
// ************************************************************************
// @HEADER

#ifndef MOCKMODELEVAL_B_TPETRA_2_PARAMETERS_H
#define MOCKMODELEVAL_B_TPETRA_2_PARAMETERS_H

#include "Teuchos_Assert.hpp"
#include "Teuchos_RCP.hpp"
#include "Thyra_ModelEvaluatorDefaultBase.hpp"
#include "Tpetra_MultiVector.hpp"
#include "Tpetra_CrsMatrix.hpp"
#include "Thyra_TpetraThyraWrappers.hpp"
#include "MatrixBased_LOWS.hpp"


using LO = Tpetra::Map<>::local_ordinal_type;
using GO = Tpetra::Map<>::global_ordinal_type;
typedef Tpetra::Map<LO,GO>  Tpetra_Map;
typedef Tpetra::Vector<double,LO,GO>  Tpetra_Vector;
typedef Tpetra::MultiVector<double,LO,GO>  Tpetra_MultiVector;
typedef Tpetra::Operator<double,LO,GO>  Tpetra_Operator;
typedef Tpetra::CrsGraph<LO,GO>  Tpetra_CrsGraph;
typedef Tpetra::CrsMatrix<double,LO,GO>  Tpetra_CrsMatrix;
typedef Thyra::TpetraOperatorVectorExtraction<
    double, LO, GO> ConverterT;

/** \brief Concrete Tpetra-based Model Evaluator
 *
 * Concrete model evaluator for the solution of the following PDE-Constrained problem:
 *
 * find (p_0,p_1) that minimizes
 * g = 0.5*(p0-6)^2 + 0.5*c*(p1-4)^2 + 0.5*(p0+p1-10)^2
 * subject to:
 * f_i = x_i = 0
 *
 * solution is p = (6,4).
 */

class MockModelEval_B_Tpetra_2_parameters
    : public Thyra::ModelEvaluatorDefaultBase<double>
{
  public:

  /** \name Constructors/initializers */
  //@{

  /** \brief Takes the number of elements in the discretization . */
  MockModelEval_B_Tpetra_2_parameters(const Teuchos::RCP<const Teuchos::Comm<int> >  appComm, bool adjoint = false, const Teuchos::RCP<Teuchos::ParameterList>& problemList = Teuchos::null, bool hessianSupport = false);

  //@}

  ~MockModelEval_B_Tpetra_2_parameters();


  /** \name Overridden from EpetraExt::ModelEvaluator . */
  //@{

  /** \brief . */
  Thyra::ModelEvaluatorBase::InArgs<double> getNominalValues() const;
  /** \brief . */
  Thyra::ModelEvaluatorBase::InArgs<double> getLowerBounds() const;
  /** \brief . */
  Thyra::ModelEvaluatorBase::InArgs<double> getUpperBounds() const;

  /** \brief . */
  Teuchos::RCP<Thyra::LinearOpBase<double>>
  create_W_op() const;

  /** \brief . */
  Teuchos::RCP<Thyra::PreconditionerBase<double>>
  create_W_prec() const;

  /** \brief . */
  Teuchos::RCP<const Thyra::LinearOpWithSolveFactoryBase<double>>
  get_W_factory() const;

  /** \brief . */
  Teuchos::RCP<Thyra::LinearOpBase<double>>
  create_hess_g_pp( int j, int l1, int l2 ) const;

  /** \brief . */
  Thyra::ModelEvaluatorBase::InArgs<double>
  createInArgs() const;

  /** \brief . */
  void
  reportFinalPoint(
      const Thyra::ModelEvaluatorBase::InArgs<double>& finalPoint,
      const bool wasSolved);

  /** \brief . */
  Teuchos::RCP<const Thyra::VectorSpaceBase<double>>  get_x_space() const;
  /** \brief . */
  Teuchos::RCP<const Thyra::VectorSpaceBase<double>>  get_f_space() const;
  /** \brief . */
  Teuchos::RCP<const Thyra::VectorSpaceBase<double>> get_p_space(int l) const;
  /** \brief . */
  Teuchos::RCP<const Thyra::VectorSpaceBase<double>> get_g_space(int j) const;
  /** \brief . */
  Teuchos::RCP<const Teuchos::Array<std::string> > get_p_names(int l) const;
  /** \brief . */
  Teuchos::ArrayView<const std::string> get_g_names(int j) const {
    TEUCHOS_TEST_FOR_EXCEPTION(true, std::logic_error, "not implemented");
  }
  //@}

  protected:

  //@{

  /** \brief . */
  Thyra::ModelEvaluatorBase::OutArgs<double>
  createOutArgsImpl() const;

  /** \brief . */
  void
  evalModelImpl(
      const Thyra::ModelEvaluatorBase::InArgs<double>& inArgs,
      const Thyra::ModelEvaluatorBase::OutArgs<double>& outArgs) const;
  //@}


  private:

  /** \brief . */
  Thyra::ModelEvaluatorBase::InArgs<double>
  createInArgsImpl() const;

   //These are set in the constructor and used in evalModel
  Teuchos::RCP<const Tpetra_Map> x_map;
  Teuchos::RCP<const Tpetra_Map> p_map;
  Teuchos::RCP<const Tpetra_Map> g_map;
  Teuchos::RCP<Tpetra_CrsGraph> crs_graph;
  Teuchos::RCP<Tpetra_CrsGraph> hess_crs_graph;
  Teuchos::RCP<const Teuchos::Comm<int> > comm;

  Teuchos::RCP<Tpetra_Vector> p_vec_0;
  Teuchos::RCP<Tpetra_Vector> p_vec_1;
  Teuchos::RCP<Tpetra_Vector> x_vec;
  Teuchos::RCP<Tpetra_Vector> x_dot_vec;

   //! Cached nominal values and lower/upper bounds
   Thyra::ModelEvaluatorBase::InArgs<double> nominalValues;
   Thyra::ModelEvaluatorBase::InArgs<double> lowerBounds;
   Thyra::ModelEvaluatorBase::InArgs<double> upperBounds;

   //whether hessian is supported 
   bool hessSupport;

   //Problem parameter list
   Teuchos::RCP<Teuchos::ParameterList> probList_;

};

#endif // MOCKMODELEVAL_B_TPETRA_2_PARAMETERS_H
