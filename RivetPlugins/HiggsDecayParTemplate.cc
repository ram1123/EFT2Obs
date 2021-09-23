// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Particle.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/UnstableParticles.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/DressedLeptons.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/PromptFinalState.hh"

using HepMC::GenParticle;
using HepMC::GenVertex;

namespace Rivet {

  class HiggsDecayParTemplate : public Analysis
  {
  public:
    DEFAULT_RIVET_ANALYSIS_CTOR(HiggsDecayParTemplate);

    void init() {

      book(hist_pT_Higgs,   "pT_Higgs",80,0,400);
      // int ram = 3.0;
    }

    /// Perform the per-event analysis
    void analyze(const Event& event) {
      // std::cout << "Ram Krishna Sharma" << std::endl;
        const double weight = 1.0;

        for ( const GenParticle *ptcl : Rivet::HepMCUtils::particles(event.genEvent()) )
        {
          // std::cout << "=====================" << std::endl;
          // std::cout << "\tpdgID: "  << ptcl->pdg_id()         << std::endl;
          // std::cout << "\tStatus: " << ptcl->status()         << std::endl;
          // std::cout << "\tpT: "     << ptcl->momentum().perp()<< std::endl;

          hist_pT_Higgs->fill(ptcl->momentum().perp());
        }


      // std::cout << "Ram value: " << ram << std::endl;
    }

    /// Normalise histograms etc., after the run
    void finalize() {
      // MSG_DEBUG("crossSection sumOfWeights ");
      MSG_DEBUG("crossSection " << crossSection() << " sumOfWeights " << sumOfWeights());

    }

  private:
      Histo1DPtr hist_pT_Higgs;

  };

  DECLARE_RIVET_PLUGIN(HiggsDecayParTemplate);
}