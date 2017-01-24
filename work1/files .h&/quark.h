#ifndef quark_h
#define quark_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>

class quark : public TObject
{
 public :  
  quark(){reset();}
  virtual ~quark(){}
  
//Double_t  PT;
//Double_t  Phi;
//Double_t  Eta;
//Double_t  M;
  TLorentzVector lv;
  // Bool_t  is_semiLeptonic;
  Bool_t  is_fullHadronic;
  //Bool_t  is_fullLeptonic;

/*   Int_t size()  */
/*   { */
/*     return size(); */
/*   }  */

  void reset()
  {
    lv.SetPtEtaPhiE(0,0,0,0);
    //is_semiLeptonic = false;
    is_fullHadronic = false;
    //is_fullLeptonic = false;
    //PT=-100;
    //Phi=-100;
    //Eta=-100;
    //M=-1;
  }
  
  
};

#endif
