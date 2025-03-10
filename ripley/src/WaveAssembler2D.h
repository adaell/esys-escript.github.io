
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
#ifndef __RIPLEY_WAVEASSEMBLER2D_H__
#define __RIPLEY_WAVEASSEMBLER2D_H__

#include <ripley/Rectangle.h>

namespace ripley {


class WaveAssembler2D : public AbstractAssembler
{
public:
    WaveAssembler2D(escript::const_Domain_ptr dom, const double *dx,
                    const dim_t *NE, const dim_t *NN,
                    const DataMap& c);

    ~WaveAssembler2D() {}

    /* The only assembly function we care about right now*/
    void assemblePDESystem(escript::AbstractSystemMatrix* mat,
                           escript::Data& rhs, const DataMap& coefs) const;

    void assemblePDESingle(escript::AbstractSystemMatrix* mat,
                           escript::Data& rhs, const DataMap& coefs) const {
        throw escript::NotImplementedError("assemblePDESingle() not supported by this assembler");
    }
    void assemblePDEBoundarySingle(escript::AbstractSystemMatrix* mat,
                           escript::Data& rhs, const DataMap& coefs) const {
        throw escript::NotImplementedError("assemblePDEBoundarySingle() not supported by this assembler");
    }
    void assemblePDESingleReduced(escript::AbstractSystemMatrix* mat,
                           escript::Data& rhs, const DataMap& coefs) const {
        throw escript::NotImplementedError("assemblePDESingleReduced() not supported by this assembler");
    }
    void assemblePDEBoundarySingleReduced(escript::AbstractSystemMatrix* mat,
                           escript::Data& rhs, const DataMap& coefs) const {
        throw escript::NotImplementedError("assemblePDEBoundarySingleReduced() not supported by this assembler");
    }
    void assemblePDEBoundarySystem(escript::AbstractSystemMatrix* mat,
                           escript::Data& rhs, const DataMap& coefs) const {
        throw escript::NotImplementedError("assemblePDEBoundarySystem() not supported by this assembler");
    }
    void assemblePDESystemReduced(escript::AbstractSystemMatrix* mat,
                           escript::Data& rhs, const DataMap& coefs) const {
        throw escript::NotImplementedError("assemblePDESystemReduced() not supported by this assembler");
    }
    void assemblePDEBoundarySystemReduced(escript::AbstractSystemMatrix* mat,
                           escript::Data& rhs, const DataMap& coefs) const {
        throw escript::NotImplementedError("assemblePDEBoundarySystemReduced() not supported by this assembler");
    }

    void collateFunctionSpaceTypes(std::vector<int>& fsTypes,
                                   const DataMap& coefs) const;

private:
    DataMap c;
    POINTER_WRAPPER_CLASS(const Rectangle) domain;
    const double *m_dx;
    const dim_t *m_NE;
    const dim_t *m_NN;
    escript::Data c11, c12, c13, c23, c33, c44, c66;
    bool isVTI, isHTI;
};

} // namespace ripley

#endif // __RIPLEY_WAVEASSEMBLER2D_H__

