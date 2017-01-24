#ifndef lepton_h
#define lepton_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>
class lepton : public TObject
{
 public:
  lepton(){reset();}
  virtual ~lepton(){}
  TLorentzVector lv;
  Bool_t  is_semiLeptonic;
  // Bool_t  is_fullHadronic;
  Bool_t  is_fullLeptonic;

/*   Int_t size() */
/*   { */
/*     return size(); */
/*   } */

  
  void reset()
  {
    lv.SetPtEtaPhiE(0,0,0,0);
    is_semiLeptonic = false;
    // is_fullHadronic = false;
    is_fullLeptonic = false;
  }
  
  
};
#endif
