//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jan  8 20:43:32 2017 by ROOT version 6.08/00
// from TTree LHEF/Analysis tree
// found on file: source_root_files/ttbar50k.root
//////////////////////////////////////////////////////////

#ifndef LHEF_h
#define LHEF_h

//#include <TROOT.h>
//#include <TChain.h>
//#include <TFile.h>

// Header file for the classes stored in the TTree if any.
//#include "TClonesArray.h"
//#include "TObject.h"

class LHEF {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
//   const Int_t kMaxEvent = 1;
//   const Int_t kMaxParticle = 12;

   // Declaration of leaf types
   Int_t           Event_;
   UInt_t          Event_fUniqueID[1];   //[Event_]
   UInt_t          Event_fBits[1];   //[Event_]
   Long64_t        Event_Number[1];   //[Event_]
   Int_t           Event_Nparticles[1];   //[Event_]
   Int_t           Event_ProcessID[1];   //[Event_]
   Double_t        Event_Weight[1];   //[Event_]
   Double_t        Event_ScalePDF[1];   //[Event_]
   Double_t        Event_CouplingQED[1];   //[Event_]
   Double_t        Event_CouplingQCD[1];   //[Event_]
   Int_t           Event_size;
   Int_t           Particle_;
   UInt_t          Particle_fUniqueID[12];   //[Particle_]
   UInt_t          Particle_fBits[12];   //[Particle_]
   Int_t           Particle_PID[12];   //[Particle_]
   Int_t           Particle_Status[12];   //[Particle_]
   Int_t           Particle_Mother1[12];   //[Particle_]
   Int_t           Particle_Mother2[12];   //[Particle_]
   Int_t           Particle_ColorLine1[12];   //[Particle_]
   Int_t           Particle_ColorLine2[12];   //[Particle_]
   Double_t        Particle_Px[12];   //[Particle_]
   Double_t        Particle_Py[12];   //[Particle_]
   Double_t        Particle_Pz[12];   //[Particle_]
   Double_t        Particle_E[12];   //[Particle_]
   Double_t        Particle_M[12];   //[Particle_]
   Double_t        Particle_PT[12];   //[Particle_]
   Double_t        Particle_Eta[12];   //[Particle_]
   Double_t        Particle_Phi[12];   //[Particle_]
   Double_t        Particle_Rapidity[12];   //[Particle_]
   Double_t        Particle_LifeTime[12];   //[Particle_]
   Double_t        Particle_Spin[12];   //[Particle_]
   Int_t           Particle_size;

   // List of branches
   TBranch        *b_Event_;   //!
   TBranch        *b_Event_fUniqueID;   //!
   TBranch        *b_Event_fBits;   //!
   TBranch        *b_Event_Number;   //!
   TBranch        *b_Event_Nparticles;   //!
   TBranch        *b_Event_ProcessID;   //!
   TBranch        *b_Event_Weight;   //!
   TBranch        *b_Event_ScalePDF;   //!
   TBranch        *b_Event_CouplingQED;   //!
   TBranch        *b_Event_CouplingQCD;   //!
   TBranch        *b_Event_size;   //!
   TBranch        *b_Particle_;   //!
   TBranch        *b_Particle_fUniqueID;   //!
   TBranch        *b_Particle_fBits;   //!
   TBranch        *b_Particle_PID;   //!
   TBranch        *b_Particle_Status;   //!
   TBranch        *b_Particle_Mother1;   //!
   TBranch        *b_Particle_Mother2;   //!
   TBranch        *b_Particle_ColorLine1;   //!
   TBranch        *b_Particle_ColorLine2;   //!
   TBranch        *b_Particle_Px;   //!
   TBranch        *b_Particle_Py;   //!
   TBranch        *b_Particle_Pz;   //!
   TBranch        *b_Particle_E;   //!
   TBranch        *b_Particle_M;   //!
   TBranch        *b_Particle_PT;   //!
   TBranch        *b_Particle_Eta;   //!
   TBranch        *b_Particle_Phi;   //!
   TBranch        *b_Particle_Rapidity;   //!
   TBranch        *b_Particle_LifeTime;   //!
   TBranch        *b_Particle_Spin;   //!
   TBranch        *b_Particle_size;   //!

   LHEF(TTree *tree=0);
   virtual ~LHEF();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

//#ifndef LHEF_cxx
//#define LHEF_cxx


