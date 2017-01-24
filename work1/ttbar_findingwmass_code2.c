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

void ttbar_sl_1()
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
  TH1D * hist_quark1 = new TH1D ("hist_quark1" , "W Mass", 100 , 0, 100);
  TH1D * hist_lept1 = new TH1D ("hist_lept" , "W Mass", 100 , 0, 100);
  
  vector<TLorentzVector> quarks,lepts;
  TLorentzVector quark,lept;

  Bool_t  is_semiLeptonic;
  Bool_t  is_fullHadronic;
  Bool_t  is_fullLeptonic;
  
  Long64_t nevt1 = tout->GetEntries();
  //event loop
  for (Long64_t j=0; j<1 ; j++)
    {
      tout->GetEntry(j);
      lept.size()==0;
      quarks.size()==0;
      is_semiLeptonic = false;
      is_fullHadronic = false;
      is_fullLeptonic = false;

      //particle loop
      for(int n=0; n< npar ; n++)
      {
	cout << "Status[n]: " <<  Status[n] << " PID[n]: "<< PID[n]<< endl;

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
	{	is_fullHadronic = true;
	  if((PID[n])==1 || (PID[n])==-2)
	    for (Int_t jj=0; jj < (Int_t)quarks.size() ; jj++)
	  	  {
      
	  	    for (Int_t kk = 0; kk <(Int_t)quarks.size(); kk++)
	  	      {

	  		//cout << "mass1 " << fabs( quarks[jj].M() + quarks[kk].M() ) << endl;

	  		if(fabs(quarks[jj].M()+ quarks[kk].M() - 80.40) < 10)
			 	      
	  		  hist_quark->Fill(fabs( quarks[jj].M() + quarks[kk].M() ));
		      

	  	      }
	  
	  	  }
	}
      
      if(lepts.size()==2)
	{	is_semiLeptonic = true;
	  if(PID[n]==11 || PID[n]==-12){
	  for (Int_t i=0; i < (Int_t)lepts.size() ; i++)
	    	       {
      
	    	 	 for (Int_t s = 0; s <(Int_t)lepts.size(); s++)
	    	 	   {
	 	  
	    	 	     if(fabs(lepts[i].M()+ lepts[s].M() - 80.40) < 10)
			 	      
	    	 	       hist_lept->Fill(fabs( lepts[i].M() + lepts[s].M() ));

	    	 	   }
	    	       }
	  }
	  if (PID[n]==1 || PID[n]==-2)
	    {
	  for (Int_t j1=0; j1 < (Int_t)quarks.size() ; j1++)
	  	  {
      
	  	    for (Int_t k = 0; k <(Int_t)quarks.size(); k++)
	  	      {

	  		//cout << "mass1 " << fabs( quarks[j1].M() + quarks[k].M() ) << endl;

	  		if(fabs(quarks[j1].M()+ quarks[k].M() - 80.40) < 10)
			 	      
	  		  hist_quark1->Fill(fabs( quarks[j1].M() + quarks[k].M() ));
		      
	  	      }
	  
	  	  }
	}
	}
	
      if(lepts.size()>2)
	{	is_fullLeptonic = true;
	   for (Int_t ii=0; ii < (Int_t)lepts.size() ; ii++)
	    	       {
      
	    	 	 for (Int_t ss = 0; ss <(Int_t)lepts.size(); ss++)
	    	 	   {
	 
	    	 	     if(fabs(lepts[ii].M()+ lepts[ss].M() - 80.40) < 10)
			 	      
	    	 	       hist_lept1->Fill(fabs( lepts[ii].M() + lepts[ss].M() ));

	    	 	   }
	    	       }
	}
      
      cout <<"is_fullHadronic: " << is_fullHadronic <<endl;
      cout <<"is_semiLeptonic: " << is_semiLeptonic <<endl;
      cout <<"is_fullLeptonic: " << is_fullLeptonic <<endl;

      cout<<"##################"<<endl;	 

    }//Loops for events
	 
} 

	  
     
