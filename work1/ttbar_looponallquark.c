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

void ttbar_hs()
{TFile *f = new TFile("ttbar_style.root","read");
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


  TH1D * hist = new TH1D ("hist" , "W Mass", 100 , 0, 100);
  Long64_t j = tout->GetEntries();

    vector<TLorentzVector> quarks;
	  TLorentzVector quark;
	  
  for (Long64_t j=0; j<=2; j++)
    {
      tout->GetEntry(j);
     
      
      for(int n=0; n< npar ; n++)
	{

	  
	  cout<<"Status= "<<Status[n]<<" "<<"PID[n]:"<<PID[n]<<endl;

	  // if (fabs(PID[n]==6) || fabs(PID[n]==5) || fabs(PID[n]==24) || fabs(PID[n]==21) || fabs(PID[n]==3)) continue;
	  
	 
	  quark.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
	  
	  //cout << "mass: " << quark.M() << endl;
		  
	  quarks.push_back(quark);
	      
	  // cout<<"quarks.size()= "<<quarks.size()<<endl;
	  for (Int_t jj=0; jj < (Int_t)quarks.size() ; jj++)
	    {
      
	      for (Int_t kk = 0; kk <(Int_t)quarks.size(); kk++)
		{
	  
		  if (kk == jj)
		    continue;

		  //cout << "mass1 " << fabs( quarks[jj].M() + quarks[kk].M() ) << endl;

		  if(fabs(quarks[jj].M()+ quarks[kk].M() - 80.40) < 5)
			  {	      
			    hist->Fill(fabs( quarks[jj].M() + quarks[kk].M() ));
		      }

			 
	  
		}
	    }
	 
     
	}
       cout<<"##################################"<<endl;

    }
  

      
        TFile*file = new TFile("mother.root","RECREATE");
	file->cd();
        hist->Write();

}
	      
    	
