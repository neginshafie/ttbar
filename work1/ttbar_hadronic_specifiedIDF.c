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

void ttbar_hadronic_specifiedID()
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


  TH1D * hist_quark = new TH1D ("hist_quark" , "W Mass", 1000 , -100, 100);
  TH1D * hist_quark4 = new TH1D ("hist_quark2" , "W Mass", 1000 , -100, 100);
  TH1D * hist_quark3 = new TH1D ("hist_quark3" , "W Mass", 1000 , -100, 100);
  TH1D * hist_diff = new TH1D ("hist_diff" , "mass-W Mass", 1000 , -100, 100);
  TH1D * hist_quark1 = new TH1D ("hist_quark1" , "W Mass", 1000 , -100, 100);
  TH1D * hist_diff1 = new TH1D ("hist_diff1" , "mass-W Mass", 1000 , -100, 100);
  TH1D * hist_lept = new TH1D ("hist_lept" , "W Mass", 100 , 0, 100);
  
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

	//cout << "Status[n]: " <<  Status[n] << " PID[n]: "<< PID[n] << " M[n]: " << M[n] << endl;
	//status loop
	if (Status[n]==1)
	  {
	    if (fabs(PID[n])==1 || fabs(PID[n])==2 || fabs(PID[n])==3 || fabs(PID[n])==4)
	      {
		quark.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
		quarks.push_back(quark);
		
		if(PID[n]==2 || PID[n]==-1)
		  {
		    for (Int_t jj=0; jj < (Int_t)quarks.size() ; jj++)
		      {
      
			for (Int_t kk = jj+1; kk <(Int_t)quarks.size(); kk++)
			  {
			    mass[jj][kk]=(fabs((quarks[jj]+ quarks[kk]).M()));
			    double m= mass[jj][kk];
			       hist_quark->Fill(m);

			    //cout<< "mass1:"<<mass[jj][kk]<<endl;
			   
			  }
		      }
		    // hist_quark->Fill(m);
		  }
	  
		else if(PID[n]==-2 || PID[n]==1)
		  {
		    for (Int_t m=0; m < (Int_t)quarks.size() ; m++)
		      {
      
			for (Int_t k = m+1; k <(Int_t)quarks.size(); k++)
			  {
			    mass[m][k]=(fabs((quarks[m]+ quarks[k]).M()));
			    // doube m1=mass[m][k];
			    // cout<< "mass2:"<<mass[m][k]<<endl;  
			    hist_quark1->Fill(mass[m][k]);
			  }
		      }
		  }
	  
		if(PID[n]==3 || PID[n]==-4)
		  {
		    for (Int_t mm=0; mm< (Int_t)quarks.size() ; mm++)
		      {
      
			for (Int_t tt = mm+1; tt <(Int_t)quarks.size(); tt++)
			  {
			    mass[mm][tt]=(fabs((quarks[mm]+ quarks[tt]).M()));
			    //double m2=mass[mm][tt];
			    // cout<< "mass3:"<<mass[mm][tt]<<endl;  	      
			    hist_quark3->Fill(mass[mm][tt]);
			  }
		      }
		  }
		else if(PID[n]==-3 || PID[n]==4)
		  {
		    for (Int_t t=0; t < (Int_t)quarks.size() ; t++)
		      {
      
			for (Int_t s= t+1; s <(Int_t)quarks.size(); s++)
			  {
			    mass[t][s]=(fabs((quarks[t]+ quarks[s]).M()));
			    
			    //cout<< "mass4:"<<mass[t][s]<<endl;   
			    hist_quark4->Fill(mass[t][s]);
			  }
		      }
		  }	
	      }
	 
       
	    else if (fabs(PID[n])==11 || fabs(PID[n])==12 || fabs(PID[n])==13 || fabs(PID[n])==14 || fabs(PID[n])==15 || fabs(PID[n])==16)
	      { 
		lept.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
		lepts.push_back(lept);
	     	
	      }
	  }
	

 }//Loops for particles
      
       
      // cout<<"quarks size()= "<< quarks.size() <<endl;
      //  cout<<"lepts size()= " << lepts.size() <<endl;
      
      if(quarks.size()>=4)
	is_fullHadronic= true;
      if(lepts.size()==2)
      	is_semiLeptonic = true;
      if(lepts.size()>2)
      	is_fullLeptonic = true;

      
	 	      

       cout <<"is_fullHadronic: " << is_fullHadronic<<endl;
      cout <<"is_semiLeptonic: " << is_semiLeptonic <<endl;
      cout <<"is_fullLeptonic: " << is_fullLeptonic <<endl;
      
     

	cout<<"##################"<<endl;	 

            lepts.clear();
            quarks.clear();

    }//loop for event
  
TCanvas *first = new TCanvas("first","first",0,0,900,700); 
  first->Divide(2,2);
first->cd(1);
hist_quark->GetXaxis()->SetTitle(" sum of u&dbar quarks ");
 hist_quark->GetYaxis()->SetTitle("Event ");
hist_quark->SetMaximum(30);
hist_quark->SetLineColor(kRed);    
hist_quark->Draw();

first->cd(2);
hist_quark1->GetXaxis()->SetTitle(" sum of d&ubar quarks");
 hist_quark1->GetYaxis()->SetTitle(" Event");
hist_quark1->SetMaximum(30);
hist_quark1->SetLineColor(kBlue);    
hist_quark1->Draw();

first->cd(3);
hist_quark3->GetXaxis()->SetTitle(" sum of s&cbar quarks ");
 hist_quark3->GetYaxis()->SetTitle(" Event ");
hist_quark3->SetMaximum(30);
hist_quark3->SetLineColor(kPink);    
hist_quark3->Draw();

first->cd(4);
hist_quark4->GetXaxis()->SetTitle(" sum of c&sbar quarks ");
 hist_quark4->GetYaxis()->SetTitle(" Event ");
hist_quark4->SetMaximum(30);
hist_quark4->SetLineColor(kPink);    
hist_quark4->Draw("same");




TFile *file = new TFile("w1_mass.root","RECREATE");
file->cd();
 hist_quark1->Write();
 hist_quark3->Write();
 hist_quark4->Write();
 hist_quark->Write();
 file->Close();
  
delete file;
    }
