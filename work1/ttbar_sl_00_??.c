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
//#include <TClassTable.h>
#include <cstdio>
#include <iostream>
//using namespace std;

void ttbar_sl_00()
{
  TFile *f = new TFile("ttbar_style.root","read");
  TTree *tout = (TTree*)f->Get("tout");
  Double_t PT[12],Eta[12],Phi[12],M[12];
  Int_t PID[12]; int Status[12];
  Int_t  npar;
  
  
  tout->SetBranchAddress("PT",&PT);
  tout->SetBranchAddress("Eta",&Eta);
  tout->SetBranchAddress("Phi",&Phi);
  tout->SetBranchAddress("M",&M);
  tout->SetBranchAddress("PID",&PID);
  tout->SetBranchAddress("npar",&npar);
  tout->SetBranchAddress("Status",&Status);


  TH1D * hist_quark = new TH1D ("hist_quark" , "W Mass", 100 , 0, 100);
  TH1D * hist_lept = new TH1D ("hist_lept" , "W Mass", 100 , 0, 100);
  
  vector<TLorentzVector> quarks,lepts;
  TLorentzVector quark;
  TLorentzVector lept;

  Bool_t  is_semiLeptonic;
  Bool_t  is_fullHadronic;
  Bool_t  is_fullLeptonic;
     

  Long64_t nevt1 = tout->GetEntries();
  //event loop
  for (Long64_t j=7; j<9  ; j++)
    {
      tout->GetEntry(j);

      is_semiLeptonic = false;
      is_fullHadronic = false;
      is_fullLeptonic = false;

      //particle loop
      for(int n=0; n< npar ; n++)
      {

	//cout << "Status[n]: " <<  Status[n] << " PID[n]: "<< PID[n] << " M[n]: " << M[n] << endl;
	//status loop
	if (Status[n]==1)
	  {
	    if (fabs(PID[n])==1 || fabs(PID[n])==2 || fabs(PID[n])==3 || fabs(PID[n])==4)
	      {
		quark.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
		quarks.push_back(quark);
	     		
	      }
       
	    else if (fabs(PID[n])==11 || fabs(PID[n])==12 || fabs(PID[n])==13 || fabs(PID[n])==14 || fabs(PID[n])==15 || fabs(PID[n])==16)
	      { 
		lept.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
		lepts.push_back(lept);
	     	
	      }
	  }

      }//Loops for particles
      
      cout<<"quarks size()= "<< quarks.size() <<endl;
      cout<<"lepts size()= " << lepts.size() <<endl;
      
      if(quarks.size()>=4)
	is_fullHadronic= true;
      if(lepts.size()==2)
      	is_semiLeptonic = true;
      if(lepts.size()>2)
      	is_fullLeptonic = true;
	 	      

       cout <<"is_fullHadronic: " << is_fullHadronic<<endl;
      cout <<"is_semiLeptonic: " << is_semiLeptonic <<endl;
      cout <<"is_fullLeptonic: " << is_fullLeptonic <<endl;
      
            if (is_fullHadronic)
	      {
			cout<<"(quarks[2]+quarks[3]).M():"<<(quarks[2]+quarks[3]).M()<<endl;
		
		if( fabs((quarks[2]+quarks[3]).M()-80.40)<7 )
		  hist_quark->Fill(fabs((quarks[2]+quarks[3]).M()));
		 
		 cout<<"((quarks[3]+quarks[2]).M()-80.4):"<<((quarks[3]+quarks[2]).M()-80.40)<<endl;

	      }
	    	cout<<"j:"<<j<<endl;
     
      cout<<"##################"<<endl;	 

            lepts.clear();
            quarks.clear();
    }//Loops for events
    
  // hist_lept->Draw();
    hist_quark->Draw("same");
      
  TFile *file = new TFile("w mass for quarks 3 & event 7.root","RECREATE");
  file->cd();
  // hist_lept->Write();
  hist_quark->Write();
  file->Close();
  
  //  delete file;
} 

	  
     
