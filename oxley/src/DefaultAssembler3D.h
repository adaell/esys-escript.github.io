
/*****************************************************************************
*
* Copyright (c) 2003-2020 by The University of Queensland
* http://www.uq.edu.au
*
* Primary Business: Queensland, Australia
* Licensed under the Apache License, version 2.0
* http://www.apache.org/licenses/LICENSE-2.0
*
* Development until 2012 by Earth Systems Science Computational Center (ESSCC)
* Development 2012-2013 by School of Earth Sciences
* Development from 2014-2017 by Centre for Geoscience Computing (GeoComp)
* Development from 2019 by School of Earth and Environmental Sciences
**
*****************************************************************************/
#ifndef __OXLEY_DEFAULTASSEMBLER3D_H__
#define __OXLEY_DEFAULTASSEMBLER3D_H__

#include <oxley/Brick.h>

namespace oxley {

template<class Scalar = double>
class DefaultAssembler3D : public AbstractAssembler
{
public:
    DefaultAssembler3D<Scalar>(escript::const_Domain_ptr dom)
        : AbstractAssembler()
    {
        domain = REFCOUNTNS::static_pointer_cast<const Brick>(dom);
    }

    ~DefaultAssembler3D() {}

    /* The default RipleyDomain assemblers, with original signatures */
    
    /// assembles a single PDE into the system matrix 'mat' and the right hand
    /// side 'rhs'
    virtual void assemblePDESingle(escript::AbstractSystemMatrix* mat,
                               escript::Data& rhs, const escript::Data& A,
                               const escript::Data& B, const escript::Data& C,
                               const escript::Data& D, const escript::Data& X,
                               const escript::Data& Y) const;

    /// assembles boundary conditions of a single PDE into the system matrix
    /// 'mat' and the right hand side 'rhs'
    virtual void assemblePDEBoundarySingle(escript::AbstractSystemMatrix* mat,
                                   escript::Data& rhs, const escript::Data& d,
                                   const escript::Data& y) const;

    /// assembles a single PDE with reduced order into the system matrix 'mat'
    /// and the right hand side 'rhs'
    virtual void assemblePDESingleReduced(escript::AbstractSystemMatrix* mat,
            escript::Data& rhs, const escript::Data& A, const escript::Data& B,
            const escript::Data& C, const escript::Data& D,
            const escript::Data& X, const escript::Data& Y) const;

    /// assembles boundary conditions of a single PDE with reduced order into
    /// the system matrix 'mat' and the right hand side 'rhs'
    virtual void assemblePDEBoundarySingleReduced(
                                   escript::AbstractSystemMatrix* mat,
                                   escript::Data& rhs, const escript::Data& d,
                                   const escript::Data& y) const;

    /// assembles a system of PDEs into the system matrix 'mat' and the right
    /// hand side 'rhs'
    virtual void assemblePDESystem(escript::AbstractSystemMatrix* mat,
                                escript::Data& rhs, const escript::Data& A,
                                const escript::Data& B, const escript::Data& C,
                                const escript::Data& D, const escript::Data& X,
                                const escript::Data& Y) const;

    /// assembles boundary conditions of a system of PDEs into the system
    /// matrix 'mat' and the right hand side 'rhs'
    virtual void assemblePDEBoundarySystem(escript::AbstractSystemMatrix* mat,
                                   escript::Data& rhs, const escript::Data& d,
                                   const escript::Data& y) const;

    /// assembles a system of PDEs with reduced order into the system matrix
    /// 'mat' and the right hand side 'rhs'
    virtual void assemblePDESystemReduced(escript::AbstractSystemMatrix* mat,
            escript::Data& rhs, const escript::Data& A, const escript::Data& B,
            const escript::Data& C, const escript::Data& D,
            const escript::Data& X, const escript::Data& Y) const;

    /// assembles boundary conditions of a system of PDEs with reduced order
    /// into the system matrix 'mat' and the right hand side 'rhs'
    virtual void assemblePDEBoundarySystemReduced(
                                   escript::AbstractSystemMatrix* mat,
                                   escript::Data& rhs, const escript::Data& d,
                                   const escript::Data& y) const;

    /* The new interface for assemblers */

    virtual void assemblePDESingle(escript::AbstractSystemMatrix* mat,
                              escript::Data& rhs, const DataMap& coefs) const;
    virtual void assemblePDEBoundarySingle(escript::AbstractSystemMatrix* mat,
                              escript::Data& rhs, const DataMap& coefs) const;
    virtual void assemblePDESingleReduced(escript::AbstractSystemMatrix* mat,
                              escript::Data& rhs, const DataMap& coefs) const;
    virtual void assemblePDEBoundarySingleReduced(
                              escript::AbstractSystemMatrix* mat,
                              escript::Data& rhs, const DataMap& coefs) const;
    virtual void assemblePDESystem(escript::AbstractSystemMatrix* mat,
                              escript::Data& rhs, const DataMap& coefs) const;
    virtual void assemblePDEBoundarySystem(escript::AbstractSystemMatrix* mat,
                              escript::Data& rhs, const DataMap& coefs) const;
    virtual void assemblePDESystemReduced(escript::AbstractSystemMatrix* mat,
                              escript::Data& rhs, const DataMap& coefs) const;
    virtual void assemblePDEBoundarySystemReduced(
                              escript::AbstractSystemMatrix* mat,
                              escript::Data& rhs, const DataMap& coefs) const;

#ifdef ESYS_HAVE_TRILINOS
    virtual void assemblePDEHanging(Teuchos::RCP<Tpetra::CrsMatrix<double,esys_trilinos::LO,esys_trilinos::GO,esys_trilinos::NT>>* mat) const;
#endif
    
    void collateFunctionSpaceTypes(std::vector<int>& fsTypes,
                                   const DataMap& coefs) const;

protected:
    POINTER_WRAPPER_CLASS(const Brick) domain;
    const double *m_dx;
    const dim_t *m_NE;
    const dim_t *m_NN;
};

} // namespace oxley

#endif // __OXLEY_DEFAULTASSEMBLER3D_H__

