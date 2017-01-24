#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TMath.h"
#include "TH2.h"
#include "TCanvas.h"
#include <vector>
#include <TLorentzVector.h>
#include "quark.h"
#include "lepton.h"
//#include <TClassTable.h>
#include <cstdio>
#include <iostream>

void ttbar_electron_leptonclass()
{
 TFile *f = new TFile("ttbar_style.root","read");
  TTree *tout = (TTree*)f->Get("tout");
  Double_t PT[12],Eta[12],Phi[12],E[12],Px[12],Py[12],Pz[12];
  Int_t PID[12]; int Status[12];
  Int_t  npar;

   lepton electron[12];

   tout->SetBranchAddress("PT",&PT);
  tout->SetBranchAddress("Px",&Px);
  tout->SetBranchAddress("Py",&Py);
  tout->SetBranchAddress("Pz",&Pz);
  tout->SetBranchAddress("Eta",&Eta);
  tout->SetBranchAddress("Phi",&Phi);
  tout->SetBranchAddress("E",&E);
  tout->SetBranchAddress("PID",&PID);
  tout->SetBranchAddress("npar",&npar);
  tout->SetBranchAddress("Status",&Status);
  
  

  TH1F *hsize = new TH1F("hsize","number of electron",100,-100,100);
  TH1F *hpx = new TH1F("hpx", "px dis",20,0,100);
  TH1F *hpy = new TH1F("hpy", "py dis",40,-100,100);
  TH1F *hpt = new TH1F("hpt", "pt dis",40,-100,100);
  TH1F *hm = new TH1F("hm", "m dis",40,-100,100);

  TTree *tcal = new TTree("tcal","calibration Tree");
  Double_t wPT;
  //, wEta[12] , wPhi[12] , wE[12] , wPx[12] , wPy[12] , wPz[12];
  Int_t wNele;

  //  tcal->Branch("wPT",&wPT,"wPT/D");
  //  tcal->Branch("wPx",&wPx,"wPx[12]/D");
  //  tcal->Branch("wPy",&wPx,"wPy[12]/D");
  //  tcal->Branch("wPz",&wPx,"wPz[12]/D");
  tcal->Branch("wNele",&wNele,"wNele/I");
  //  tcal->Branch("wE",&wE,"wE[12]/D");
  //  tcal->Branch("wEta",&wEta,"wEta[12]/D");
  //  tcal->Branch("wPhi",&wPhi,"wPhi[12]/D");
  //tcal->Branch("wdeltaR",&deltaR,"deltaR[12]/D");
  
  Double_t wPT[wNele];
  tcal->Branch("wPT",&wPT,"wPT[wNele]/D");

 
  //  Int_t size;
  
 Long64_t nevt1 = tout->GetEntries();
  //event loop
  for (Long64_t j=0; j<nevt1  ; j++)
    {
      tout->GetEntry(j);
      wNele=0;
      //      size=0;
      //particle loop
      for(int n=0; n< npar ; n++)
      {
	//	wNele=0;
     
	if(fabs(PID[n])==1 || fabs(PID[n])==2 || fabs(PID[n])==3 ||fabs(PID[n])==4  )
	{
	wNele += 1;

	}

      }

  
      //}
  
  for (Int_t k=0; k< wNele  ; k++)
    {
      
	electron[k].lv.SetPxPyPzE(Px[k],Py[k],Pz[k],E[k]);
	wPT[k] = electron[k].lv.Pt();

	//	wPx[n]= electron[n].lv.Px();
	//	wPy[n]= electron[n].lv.Py();
	//	wPz[n]= electron[n].lv.Pz();
	//	wEta[n]= electron[n].lv.Eta();
	//	wPhi[n]= electron[n].lv.Phi();
	tcal->Fill();	
	}




    }//loop for event
  
  //  hsize->Draw();
  //  hpx->Draw();
  //  hpy->Draw();
  // hpt->Draw();
  
TFile *file = new TFile("ele.root","RECREATE");
 file->cd();
 //hsize->Write();
 //  hpx->Write();
 //  hpy->Write();
  tcal->Write();
  //hpt->Write();
  file->Close();
  delete file;
}
