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

void ttbar_semi()
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


  TH1D * hist_quark = new TH1D ("hist_quark" , "W Mass", 100 , 0, 100);
  TH1D * hist_lept = new TH1D ("hist_lept" , "W Mass", 100 , 0, 100);
  
  vector<TLorentzVector> quarks,lepts;
  TLorentzVector quark,lept;
  
  Long64_t j = tout->GetEntries();
  //event loop
  for (Long64_t j=0; j<=1; j++)
    {
      tout->GetEntry(j);
      
      //particle loop
      for(int n=0; n< npar ; n++)
	{	  

	 // cout<<"Status= "<<Status[n]<<" "<<"PID[n]:"<<PID[n]<<endl;
	  
	  //reading status and pID
	  if (Status[n]==1){

	    if (PID[n]==2 || PID[n]==-1 )
	   
	      {
	 
		quark.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
	  
		//cout << "mass: " << quark.M() << endl;
		  
		quarks.push_back(quark);
	      }

		  if (PID[n]==13 || PID[n]==-14)
	    	   {
	 
	    	     lept.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
		  
	    	     lepts.push_back(lept);
		   }
	

	  }//ending loop of status
	      
	
	  //calculation of w mass
	  	for (Int_t jj=0; jj < (Int_t)quarks.size() ; jj++)
	  	  {
      
	  	    for (Int_t kk = 0; kk <(Int_t)quarks.size(); kk++)
	  	      {
	  
	  		if (kk == jj)
	  		  continue;

	  		//cout << "mass1 " << fabs( quarks[jj].M() + quarks[kk].M() ) << endl;

	  		if(fabs(quarks[jj].M()+ quarks[kk].M() - 80.40) < 10)
			 	      
	  		  hist_quark->Fill(fabs( quarks[jj].M() + quarks[kk].M() ));
		      

	  	      }
	  
	  	  }
		 for (Int_t i=0; i < (Int_t)lepts.size() ; i++)
	    	       {
      
	    	 	 for (Int_t s = 0; s <(Int_t)lepts.size(); s++)
	    	 	   {
	 
		  
	    	 	     if(fabs(lepts[i].M()+ lepts[s].M() - 80.40) < 10)
			 	      
	    	 	       hist_lept->Fill(fabs( lepts[i].M() + lepts[s].M() ));
		      

	    	 	   }
	    	       }
	        
	  // cout<<"##################################"<<endl;
      

	}//ending of particle's loop
  
    }//ending of event's loop
      
        TFile*file = new TFile("mother2.root","RECREATE");
	file->cd();
        hist_lept->Write();
	hist_quark->Write();

}
	      
