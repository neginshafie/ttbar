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
#include <iostream>
using namespace std;

void ttbar_fullleptonic()
{
  TFile *f = new TFile("ttbar_style.root","read");
  TTree *tout = (TTree*)f->Get("tout");
  Double_t PT[12],Eta[12],Phi[12],M[12];
  Int_t PID[12]; int Status[12];
  Int_t  npar,s,p;
  Double_t mass [12][12];
  
  
  tout->SetBranchAddress("PT",&PT);
  tout->SetBranchAddress("Eta",&Eta);
  tout->SetBranchAddress("Phi",&Phi);
  tout->SetBranchAddress("M",&M);
  tout->SetBranchAddress("PID",&PID);
  tout->SetBranchAddress("npar",&npar);
  tout->SetBranchAddress("Status",&Status);


  TH1D * hist_quark = new TH1D ("hist_quark" , "W Mass", 40 , 0, 200);
  TH1D * hist_diff = new TH1D ("hist_diff" , "mass-W Mass", 1000 , -100, 100);
  TH1D * hist_lept1 = new TH1D ("hist_lept1" , "W Mass", 1000 , -100, 100);
  TH1D * hist_diff1 = new TH1D ("hist_diff1" , "mass-W Mass", 1000 , -100, 100);
  TH1D * hist_lept = new TH1D ("hist_lept" , "W Mass", 40 , 0, 200);
  
  vector<TLorentzVector> quarks,lepts;
  TLorentzVector quark;
  TLorentzVector lept;
  TLorentzVector w;
 

  Bool_t  is_semiLeptonic;
  Bool_t  is_fullHadronic;
  Bool_t  is_fullLeptonic;
     

  Long64_t nevt1 = tout->GetEntries();
  //event loop
  for (Long64_t j=0; j<nevt1  ; j++)
    {
      tout->GetEntry(j);

      is_semiLeptonic = false;
      is_fullHadronic = false;
      is_fullLeptonic = false;

      //particle loop
      for(int n=0; n< npar ; n++)
      {

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
      Double_t a=1000,b=1000;
      Int_t submm=-1,subkk=-1,subk=-1,subm=-1,submass=-1000,submass1=-1000;
      
      if (is_fullLeptonic)//in this code we cann't udrestand e+meun or e+nuetrino
       {
	 for (Int_t kk =0; kk < lepts.size(); kk++)
		      {
			for (Int_t mm =kk+1; mm < lepts.size(); mm++)
			  {
			    mass[kk][mm] = ((lepts[mm]+lepts[kk]).M());
			      cout<<"MASS = "<<( mass[kk][mm])<<endl;
   
			  
			    double m=mass[kk][mm];
			      cout<<"MASS Dif= "<<(m-80.4)<<endl;
   
			
			    if( a >abs(m-80.4))
			      {
				a =  abs(m-80.4);
				submass=m;
				submm=mm;
				subkk=kk;

			      }
			  
			  }
		
				hist_diff->Fill(a);
				hist_lept->Fill(submass);
		      }
	 
	 for (Int_t k =0; k < lepts.size(); k++)
		      {
		    	if(subkk==k)
		    	  continue;
		    	for (Int_t t =k+1; t < lepts.size(); t++)
		    	  {
		    	    if(submm==t)
		    	      continue;
 
		    	    mass[k][t] = ((lepts[t] + lepts[k]).M());
			    // cout<<"MASS= "<<mass[kk][mm]<<endl;
			   
			    double m1=mass[k][t];
			    // cout<<"MASS Dif= "<<(m-80.4)<<endl;
   
				  
		    	    if( b >(m1-80.40))
		    	      {
		    		b =  (m1-80.40);
				    
				submass1=m1;
			        subm=t;
				subk=k;
		    		 
		    	      }
			   
		    	  }

			hist_diff1->Fill(b);	     
		    	hist_lept1->Fill(submass1);
		      }

		  }//loop for fullleptonic
       	cout<<"##################"<<endl;	 

            lepts.clear();
            quarks.clear();
	   
    }//Loops for events

  hist_lept->Draw();
hist_lept1->Draw();
  
	  
TFile *file = new TFile("w2 mass.root","RECREATE");
file->cd();
//hist_lept->Write();
hist_lept->Write();
hist_lept1->Write();
file->Close();
  
delete file;
} 
