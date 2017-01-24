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
  TLorentzVector lv_quark;
  TLorentzVector lv_lept;


  Bool_t  is_semiLeptonic;
  Bool_t  is_fullHadronic;
  Bool_t  is_fullLeptonic;
     

  Long64_t nevt1 = tout->GetEntries();
  //event loop
  for (Long64_t j=0; j<nevt1 ; j++)
    {
      tout->GetEntry(j);

      lv_quark.SetPtEtaPhiM(0,0,0,0);
      lv_lept.SetPtEtaPhiM(0,0,0,0);       
      is_semiLeptonic = false;
      is_fullHadronic = false;
      is_fullLeptonic = false;

      //particle loop
      for(int n=0; n< npar ; n++)
      {

	cout << "Status[n]: " <<  Status[n] << " PID[n]: "<< PID[n] << " PT[n]: " << PT[n] << endl;
	//status loop
	if (Status[n]==1)
	  {
	    if (fabs(PID[n])==1 || fabs(PID[n])==2 || fabs(PID[n])==3 || fabs(PID[n])==4)
	      {
		quark.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
		quarks.push_back(quark);
		//		lv_quark = lv_quark + quarks[n];
		//	cout << "quarks[n].Pt(): " << "-----"<<quark.Pt() << "---" <<quarks[n].Pt() << "n: " << n<<  endl;
		hist_quark->Fill(quark.Pt());      		
	      }
       
	    else if (fabs(PID[n])==11 || fabs(PID[n])==12 || fabs(PID[n])==13 || fabs(PID[n])==14 || fabs(PID[n])==15 || fabs(PID[n])==16)
	      { 
		lept.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
		lepts.push_back(lept);
		cout << "lepts[n].Pt(): " << lept.Pt() << endl;
		//	lv_lept = lv_lept + lepts[n];
		hist_lept->Fill(lept.Pt());      	
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

	  //	  if(fabs(lv.PT() - 80.40) < 100)		 	      

       cout <<"is_fullHadronic: " << is_fullHadronic <<endl;
      cout <<"is_semiLeptonic: " << is_semiLeptonic <<endl;
      cout <<"is_fullLeptonic: " << is_fullLeptonic <<endl;
            if (is_fullHadronic)
	      {

		// Dc etesami suggestion:	cout<<(quarks[0]+quarks[1]).M()<<endl;


	      }
      //      if(is_semiLeptonic || is_fullLeptonic)
      //	hist_lept->Fill(lv_lept.Pt());      	
      

     

      cout<<"##################"<<endl;	 

            lepts.clear();
            quarks.clear();
    }//Loops for events
    
  hist_lept->Draw();
  //  hist_quark->Draw("same");
      
  TFile*file = new TFile("w.root","RECREATE");
  file->cd();
  hist_lept->Write();
  hist_quark->Write();
  file->Close();
  
  //  delete file;
} 

	  
     
