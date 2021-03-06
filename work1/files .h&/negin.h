//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Dec 31 10:59:22 2016 by ROOT version 5.34/36
// from TTree tout/tout
// found on file: ttbar_style.root
//////////////////////////////////////////////////////////

#ifndef negin_h
#define negin_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class negin {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           nevt;
   Int_t           npar;
   Int_t           Event;
   Int_t           Ev_fUniqueID[1];   //[nevt]
   Int_t           Ev_fBits[1];   //[nevt]
   Int_t           Ev_Number[1];   //[nevt]
   Int_t           Ev_Nparticles[1];   //[nevt]
   Int_t           Ev_ProcessID[1];   //[nevt]
   Double_t        Ev_Weight[1];   //[nevt]
   Double_t        Ev_ScalePDF[1];   //[nevt]
   Double_t        Ev_CouplingQED[1];   //[nevt]
   Double_t        Ev_CouplingQCD[1];   //[nevt]
   Int_t           Ev_size;
   Int_t           Particle;
   Int_t           fUniqueID[12];   //[npar]
   Int_t           fBits[12];   //[npar]
   Int_t           PID[12];   //[npar]
   Int_t           Status[12];   //[npar]
   Int_t           Mother1[12];   //[npar]
   Int_t           Mother2[12];   //[npar]
   Int_t           ColorLine1[12];   //[npar]
   Int_t           ColorLine2[12];   //[npar]
   Double_t        Px[12];   //[npar]
   Double_t        Py[12];   //[npar]
   Double_t        Pz[12];   //[npar]
   Double_t        E[12];   //[npar]
   Double_t        M[12];   //[npar]
   Double_t        PT[12];   //[npar]
   Double_t        Eta[12];   //[npar]
   Double_t        Phi[12];   //[npar]
   Double_t        Rapidity[12];   //[npar]
   Double_t        LifeTime[12];   //[npar]
   Double_t        Spin[12];   //[npar]
   Int_t           P_size;

   // List of branches
   TBranch        *b_nevt;   //!
   TBranch        *b_npar;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_Ev_fUniqueID;   //!
   TBranch        *b_Ev_fBits;   //!
   TBranch        *b_Ev_Number;   //!
   TBranch        *b_Ev_Nparticles;   //!
   TBranch        *b_Ev_ProcessID;   //!
   TBranch        *b_Ev_Weight;   //!
   TBranch        *b_Ev_ScalePDF;   //!
   TBranch        *b_Ev_CouplingQED;   //!
   TBranch        *b_Ev_CouplingQCD;   //!
   TBranch        *b_Ev_size;   //!
   TBranch        *b_Particle;   //!
   TBranch        *b_fUniqueID;   //!
   TBranch        *b_fBits;   //!
   TBranch        *b_PID;   //!
   TBranch        *b_Status;   //!
   TBranch        *b_Mother1;   //!
   TBranch        *b_Mother2;   //!
   TBranch        *b_ColorLine1;   //!
   TBranch        *b_ColorLine2;   //!
   TBranch        *b_Px;   //!
   TBranch        *b_Py;   //!
   TBranch        *b_Pz;   //!
   TBranch        *b_E;   //!
   TBranch        *b_M;   //!
   TBranch        *b_PT;   //!
   TBranch        *b_Eta;   //!
   TBranch        *b_Phi;   //!
   TBranch        *b_Rapidity;   //!
   TBranch        *b_LifeTime;   //!
   TBranch        *b_Spin;   //!
   TBranch        *b_P_size;   //!

   negin(TTree *tree=0);
   virtual ~negin();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef negin_cxx
negin::negin(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ttbar_style.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ttbar_style.root");
      }
      f->GetObject("tout",tree);

   }
   Init(tree);
}

negin::~negin()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t negin::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t negin::LoadTree(Long64_t entry)
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

void negin::Init(TTree *tree)
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

   fChain->SetBranchAddress("nevt", &nevt, &b_nevt);
   fChain->SetBranchAddress("npar", &npar, &b_npar);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("Ev_fUniqueID", Ev_fUniqueID, &b_Ev_fUniqueID);
   fChain->SetBranchAddress("Ev_fBits", Ev_fBits, &b_Ev_fBits);
   fChain->SetBranchAddress("Ev_Number", Ev_Number, &b_Ev_Number);
   fChain->SetBranchAddress("Ev_Nparticles", Ev_Nparticles, &b_Ev_Nparticles);
   fChain->SetBranchAddress("Ev_ProcessID", Ev_ProcessID, &b_Ev_ProcessID);
   fChain->SetBranchAddress("Ev_Weight", Ev_Weight, &b_Ev_Weight);
   fChain->SetBranchAddress("Ev_ScalePDF", Ev_ScalePDF, &b_Ev_ScalePDF);
   fChain->SetBranchAddress("Ev_CouplingQED", Ev_CouplingQED, &b_Ev_CouplingQED);
   fChain->SetBranchAddress("Ev_CouplingQCD", Ev_CouplingQCD, &b_Ev_CouplingQCD);
   fChain->SetBranchAddress("Ev_size", &Ev_size, &b_Ev_size);
   fChain->SetBranchAddress("Particle", &Particle, &b_Particle);
   fChain->SetBranchAddress("fUniqueID", fUniqueID, &b_fUniqueID);
   fChain->SetBranchAddress("fBits", fBits, &b_fBits);
   fChain->SetBranchAddress("PID", PID, &b_PID);
   fChain->SetBranchAddress("Status", Status, &b_Status);
   fChain->SetBranchAddress("Mother1", Mother1, &b_Mother1);
   fChain->SetBranchAddress("Mother2", Mother2, &b_Mother2);
   fChain->SetBranchAddress("ColorLine1", ColorLine1, &b_ColorLine1);
   fChain->SetBranchAddress("ColorLine2", ColorLine2, &b_ColorLine2);
   fChain->SetBranchAddress("Px", Px, &b_Px);
   fChain->SetBranchAddress("Py", Py, &b_Py);
   fChain->SetBranchAddress("Pz", Pz, &b_Pz);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("M", M, &b_M);
   fChain->SetBranchAddress("PT", PT, &b_PT);
   fChain->SetBranchAddress("Eta", Eta, &b_Eta);
   fChain->SetBranchAddress("Phi", Phi, &b_Phi);
   fChain->SetBranchAddress("Rapidity", Rapidity, &b_Rapidity);
   fChain->SetBranchAddress("LifeTime", LifeTime, &b_LifeTime);
   fChain->SetBranchAddress("Spin", Spin, &b_Spin);
   fChain->SetBranchAddress("P_size", &P_size, &b_P_size);
   Notify();
}

Bool_t negin::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void negin::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t negin::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef negin_cxx
