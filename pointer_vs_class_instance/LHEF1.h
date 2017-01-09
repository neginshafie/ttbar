//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan  4 15:31:18 2017 by ROOT version 5.34/36
// from TTree LHEF/Analysis tree
// found on file: ttbar50k.root
//////////////////////////////////////////////////////////

#ifndef LHEF_h
#define LHEF_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TClonesArray.h"
#include "TObject.h"
// Header file for the classes stored in the TTree if any.
//#include "/Volumes/MacintoshHD2/build/electric_commander/build/workspace/root-release-5.34/BUILDTYPE/Release/COMPILER/native/LABEL/mac1011/sources/root_v5.34.36/root/core/cont/inc/TClonesArray.h"
//#include "/Volumes/MacintoshHD2/build/electric_commander/build/workspace/root-release-5.34/BUILDTYPE/Release/COMPILER/native/LABEL/mac1011/sources/root_v5.34.36/root/core/base/inc/TObject.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
//   const Int_t 1 = 1;
//   const Int_t 12 = 12;

class LHEF {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

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

#ifndef LHEF_cxx
#define LHEF_cxx
LHEF::LHEF(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ttbar50k.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ttbar50k.root");
      }
      f->GetObject("LHEF",tree);

   }
   Init(tree);
}

LHEF::~LHEF()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t LHEF::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t LHEF::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void LHEF::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Event", &Event_, &b_Event_);
   fChain->SetBranchAddress("Event.fUniqueID", Event_fUniqueID, &b_Event_fUniqueID);
   fChain->SetBranchAddress("Event.fBits", Event_fBits, &b_Event_fBits);
   fChain->SetBranchAddress("Event.Number", Event_Number, &b_Event_Number);
   fChain->SetBranchAddress("Event.Nparticles", Event_Nparticles, &b_Event_Nparticles);
   fChain->SetBranchAddress("Event.ProcessID", Event_ProcessID, &b_Event_ProcessID);
   fChain->SetBranchAddress("Event.Weight", Event_Weight, &b_Event_Weight);
   fChain->SetBranchAddress("Event.ScalePDF", Event_ScalePDF, &b_Event_ScalePDF);
   fChain->SetBranchAddress("Event.CouplingQED", Event_CouplingQED, &b_Event_CouplingQED);
   fChain->SetBranchAddress("Event.CouplingQCD", Event_CouplingQCD, &b_Event_CouplingQCD);
   fChain->SetBranchAddress("Event_size", &Event_size, &b_Event_size);
   fChain->SetBranchAddress("Particle", &Particle_, &b_Particle_);
   fChain->SetBranchAddress("Particle.fUniqueID", Particle_fUniqueID, &b_Particle_fUniqueID);
   fChain->SetBranchAddress("Particle.fBits", Particle_fBits, &b_Particle_fBits);
   fChain->SetBranchAddress("Particle.PID", Particle_PID, &b_Particle_PID);
   fChain->SetBranchAddress("Particle.Status", Particle_Status, &b_Particle_Status);
   fChain->SetBranchAddress("Particle.Mother1", Particle_Mother1, &b_Particle_Mother1);
   fChain->SetBranchAddress("Particle.Mother2", Particle_Mother2, &b_Particle_Mother2);
   fChain->SetBranchAddress("Particle.ColorLine1", Particle_ColorLine1, &b_Particle_ColorLine1);
   fChain->SetBranchAddress("Particle.ColorLine2", Particle_ColorLine2, &b_Particle_ColorLine2);
   fChain->SetBranchAddress("Particle.Px", Particle_Px, &b_Particle_Px);
   fChain->SetBranchAddress("Particle.Py", Particle_Py, &b_Particle_Py);
   fChain->SetBranchAddress("Particle.Pz", Particle_Pz, &b_Particle_Pz);
   fChain->SetBranchAddress("Particle.E", Particle_E, &b_Particle_E);
   fChain->SetBranchAddress("Particle.M", Particle_M, &b_Particle_M);
   fChain->SetBranchAddress("Particle.PT", Particle_PT, &b_Particle_PT);
   fChain->SetBranchAddress("Particle.Eta", Particle_Eta, &b_Particle_Eta);
   fChain->SetBranchAddress("Particle.Phi", Particle_Phi, &b_Particle_Phi);
   fChain->SetBranchAddress("Particle.Rapidity", Particle_Rapidity, &b_Particle_Rapidity);
   fChain->SetBranchAddress("Particle.LifeTime", Particle_LifeTime, &b_Particle_LifeTime);
   fChain->SetBranchAddress("Particle.Spin", Particle_Spin, &b_Particle_Spin);
   fChain->SetBranchAddress("Particle_size", &Particle_size, &b_Particle_size);
   Notify();
}

Bool_t LHEF::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void LHEF::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t LHEF::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void LHEF::Loop()
{
//   In a ROOT session, you can do:
//      root> .L LHEF.C
//      root> LHEF t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}



#endif // #ifdef LHEF_cxx
