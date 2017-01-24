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
//using namespace std;

void ttbar_iclude_QuarkClass()
{
  //lepton::lepton(){;}
  //  lepton::~lepton(){;}
  //  quark::quark(){;}
  //  quark::~quark(){;}



  TFile *f = new TFile("ttbar_style.root","read");
  TTree *tout = (TTree*)f->Get("tout");
  Double_t PT[12],Eta[12],Phi[12],E[12];
  Int_t PID[12]; int Status[12];
  Int_t  npar;
  vector<quark> quarks;
  vector<quark> leptons;
  
  tout->SetBranchAddress("PT",&PT);
  tout->SetBranchAddress("Eta",&Eta);
  tout->SetBranchAddress("Phi",&Phi);
  tout->SetBranchAddress("E",&E);
  tout->SetBranchAddress("PID",&PID);
  tout->SetBranchAddress("npar",&npar);
  tout->SetBranchAddress("Status",&Status);


  TH1D * hist_quark = new TH1D ("hist_quark" , "W Mass", 100 , 0, 100);
  TH1D * hist_lept = new TH1D ("hist_lept" , "W Mass", 100 , 0, 100);

  Long64_t nevt1 = tout->GetEntries();
  //event loop
  for (Long64_t j=0; j<nevt1  ; j++)
    {
      tout->GetEntry(j);

   
      //particle loop
      for(int n=0; n< npar ; n++)
      {

	//cout << "Status[n]: " <<  Status[n] << " PID[n]: "<< PID[n] << " M[n]: " << M[n] << endl;
	//status loop
	if (Status[n]==1)
	  {
	    if (fabs(PID[n])==1 || fabs(PID[n])==2 || fabs(PID[n])==3 || fabs(PID[n])==4)
	      {
	
	     	quarks[n].lv.SetPtEtaPhiE(PT[n],Eta[n],Phi[n],E[n]);	
	      }
       
	    else if (fabs(PID[n])==11 || fabs(PID[n])==12 || fabs(PID[n])==13 || fabs(PID[n])==14 || fabs(PID[n])==15 || fabs(PID[n])==16)
	      { 
		leptons[n].lv.SetPtEtaPhiE(PT[n],Eta[n],Phi[n],E[n]);
	     	
	      }
	  }

      }//Loops for particles
      
      cout<<"quarks size()= "<< quarks.size <<endl;
      cout<<"lepts size()= " << leptons.size <<endl;
      
      if(quarks.lv.size()>=4)
	quarks.is_fullHadronic= true;
      if(leptons.lv.size()==2)
      	leptons.is_semiLeptonic = true;
      if(leptons.lv.size()>2)
      leptons.is_fullLeptonic = true;
	 	      

       cout <<"is_fullHadronic: "<<quarks.is_fullHadronic <<endl;
      cout <<"is_semiLeptonic: "<< leptons.is_semiLeptonic <<endl;
      cout <<"is_fullLeptonic: "<< leptons.is_fullLeptonic <<endl;
      
            if (quarks.is_fullHadronic)
	      {
		cout<<"(quarks[2]+quarks[3]).lv.M():"<<((quarks[2] + quarks[3]).lv.M())<<endl;
		
		if( fabs((quarks[2] + quarks[3]).lv.M() - 80.40)<5 )
		  hist_quark->Fill(fabs((quarks[2] + quarks[3]).lv.M()));
		 
			//			 cout<<"((quarks[2]+quarks[3]).lv.M()-80.4):"<<fabs((quarks[2]+quarks[3]).lv.M()-80.40)<<endl;

	      }
	    	cout<<"j:"<<j<<endl;
     
      cout<<"##################"<<endl;	 

    }//Loops for events
    
  // hist_lept->Draw();
    hist_quark->Draw("same");
      
    //TFile *file = new TFile("w mass for quarks 2_3 & event 16.root","RECREATE");
    //file->cd();
    //hist_lept->Write();
    //hist_quark->Write();
    //file->Close();
  
    // delete file;
} 

	  
     
