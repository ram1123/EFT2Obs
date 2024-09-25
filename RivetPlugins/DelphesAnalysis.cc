// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/ChargedLeptons.hh"

namespace Rivet {


  class DelphesAnalysis : public Analysis {
  public:

    /// Constructor
    RIVET_DEFAULT_ANALYSIS_CTOR(DelphesAnalysis);


    /// Book histograms and initialize projections before the run
    void init() {
      // Define the final state
      const FinalState fs(Cuts::abseta < 5.0);

      // Projector for jets
      declare(FastJets(fs, JetAlg::ANTIKT, 0.4), "Jets");

      // Projector for electrons and muons
      declare(ChargedLeptons(fs), "Leptons");

      // Projector for missing transverse energy
      declare(MissingMomentum(fs), "MissingET");

      // Book histograms
      book(_h_Z_mass, "Z_mass", 100, 40, 120);
      book(_h_Z_e1_Pt, "Z_e1_Pt", 100, 0, 500);
      book(_h_Z_e1_Eta, "Z_e1_Eta", 50, -2.5, 2.5);
      book(_h_Z_e2_Pt, "Z_e2_Pt", 100, 0, 500);
      book(_h_Z_e2_Eta, "Z_e2_Eta", 50, -2.5, 2.5);
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      // Retrieve the jets, leptons, and missing ET projections
      const Jets &jets = apply<FastJets>(event, "Jets").jetsByPt(Cuts::pT > 25 * GeV && Cuts::abseta < 4.7);

      const Particles& leptons = apply<ChargedLeptons>(event, "Leptons").particlesByPt(Cuts::pT > 20*GeV);
      const MissingMomentum& met = apply<MissingMomentum>(event, "MissingET");

      if (leptons.size() < 3) return;

      // Select electrons and muons
      Particles electrons, muons;
      for (const Particle& lep : leptons) {
        if (lep.abspid() == PID::ELECTRON) electrons.push_back(lep);
        if (lep.abspid() == PID::MUON) muons.push_back(lep);
      }

      // Z boson reconstruction
      bool foundZ = false;
      double bestZmassDiff = 999.0;
      Particle Z_e1, Z_e2;

      for (size_t i = 0; i < electrons.size(); ++i) {
        for (size_t j = i + 1; j < electrons.size(); ++j) {
          if (electrons[i].charge() * electrons[j].charge() > 0) continue;
          const FourMomentum ee = electrons[i].momentum() + electrons[j].momentum();
          const double Zmass = 91.1876*GeV;
          const double massDiff = fabs(ee.mass() - Zmass);
          if (massDiff < bestZmassDiff) {
            bestZmassDiff = massDiff;
            Z_e1 = electrons[i];
            Z_e2 = electrons[j];
            foundZ = true;
          }
        }
      }

      if (!foundZ) return;

      const FourMomentum Z = Z_e1.momentum() + Z_e2.momentum();

      if (Z.mass() < 40*GeV || Z.mass() > 120*GeV) return;

      // Fill histograms
      _h_Z_mass->fill(Z.mass()/GeV);
      _h_Z_e1_Pt->fill(Z_e1.pT()/GeV);
      _h_Z_e1_Eta->fill(Z_e1.eta());
      _h_Z_e2_Pt->fill(Z_e2.pT()/GeV);
      _h_Z_e2_Eta->fill(Z_e2.eta());
    }


    /// Finalize
    void finalize() {
      normalize(_h_Z_mass);
      normalize(_h_Z_e1_Pt);
      normalize(_h_Z_e1_Eta);
      normalize(_h_Z_e2_Pt);
      normalize(_h_Z_e2_Eta);
    }


  private:

    // Histograms
    Histo1DPtr _h_Z_mass;
    Histo1DPtr _h_Z_e1_Pt;
    Histo1DPtr _h_Z_e1_Eta;
    Histo1DPtr _h_Z_e2_Pt;
    Histo1DPtr _h_Z_e2_Eta;

  };

  // The hook for the plugin system
  RIVET_DECLARE_PLUGIN(DelphesAnalysis);

}
