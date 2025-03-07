// @HEADER
// ***********************************************************************
// 
//    Thyra: Interfaces and Support for Abstract Numerical Algorithms
//                 Copyright (2004) Sandia Corporation
// 
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
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
// Questions? Contact Roscoe A. Bartlett (bartlettra@ornl.gov) 
// 
// ***********************************************************************
// @HEADER

#ifndef THYRA_EPETRAEXT_ADD_TRANSFORMER_HPP
#define THYRA_EPETRAEXT_ADD_TRANSFORMER_HPP

#include "Thyra_LinearOpTransformerBase.hpp"


namespace Thyra {


/** \brief Transformer subclass for adding Epetra/Thyra operators using
 * EpetraExt::MatrixMatrix.
 *
 * \ingroup EpetraExt_Thyra_Op_Vec_adapters_grp
 */
class EpetraExtAddTransformer : public LinearOpTransformerBase<double>
{
public:

  /** \name Overridden from LinearOpTransformerBase. */
  //@{

  /** \brief . */
  virtual bool isCompatible(const LinearOpBase<double> &op_in) const;

  /** \brief . */
  virtual RCP<LinearOpBase<double> > createOutputOp() const;

  /** \brief . */
  virtual void transform(
    const LinearOpBase<double> &op_in,
    const Ptr<LinearOpBase<double> > &op_inout
    ) const;

  //@}

private:
  
};


/** \brief Nonmember constructor.
 *
 * \relates EpetraExtAddTransformer
 */
inline
RCP<EpetraExtAddTransformer>
epetraExtAddTransformer()
{
  return Teuchos::rcp(new EpetraExtAddTransformer());
}


} // namespace Thyra


#endif	// THYRA_EPETRAEXT_ADD_TRANSFORMER_HPP

#if defined(Thyra_SHOW_DEPRECATED_WARNINGS)
#ifdef __GNUC__
#warning "The ThyraEpetraExtAdapters package is deprecated"
#endif
#endif

