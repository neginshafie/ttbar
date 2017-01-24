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
#include "TCanvas.h"
using namespace std;

void ttbar_w_mass()
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
     

  Long64_t nevt = tout->GetEntries();
  //event loop
  for (Long64_t j=0; j<nevt ; j++)
    {
      //      quarks = null;
      //      lepts = null;
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
	//status if
	if (Status[n]==1)
	  {
	    if (fabs(PID[n])==1 || fabs(PID[n])==2 || fabs(PID[n])==3 || fabs(PID[n])==4)
	      {
		quark.SetPtEtaPhiM(PT[n],Eta[n],Phi[n],M[n]);
		quarks.push_back(quark);
		cout << "quark.Pt(): " <<quark.Pt()<< endl;
		
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

	  //	  if(fabs(lv.PT() - 80.40) < 100)		 	      

       cout <<"is_fullHadronic: " << is_fullHadronic <<endl;
       cout <<"is_semiLeptonic: " << is_semiLeptonic <<endl;
       cout <<"is_fullLeptonic: " << is_fullLeptonic <<endl;
      //      cout<<"##################"<<endl;	 

       if (is_fullHadronic)
	 {

      TLorentzVector lv (0,0,0,0);
      TLorentzVector lv1 (0,0,0,0);
      Int_t r =0;
      Int_t w =0;	    
      //Double_t mass = 0.0;
      for (Int_t k =0; k<quarks.size(); k++)
	{
	  for (Int_t m =0; m<quarks.size(); m++)
	    {	    
	    if(m==k)
	      continue;

	  lv = quarks[0] + quarks[1];
	  //      if (k==0)
	  if((quarks[m].M()+ quarks[k].M() - 80.40) < (lv.M() - 80.40) )
	    {
	      r =m;
	      w =k;	    
	      lv =  quarks[m]+quarks[k];
	    }	  //min ((lv.M()-80.40), ((quarks[m]+ quarks[k]).M() - 80.40));
	    
	    }
	}
      if(!isnan(lv.M()))
	{
	  cout << "r: w: " << r << " "<< w <<endl;
	  cout << "mass1: " << lv.M() <<endl;
	  hist_quark->Fill(lv.M());
	}

      for (Int_t kk =0; kk<quarks.size(); kk++)
	{
	  if(kk==w)
	    continue;
	  for (Int_t mm =0; mm<quarks.size(); mm++)
	    {
	    if(mm==kk || mm==r)
	      continue;
	    lv1 = quarks[0] + quarks[1];
	  //      if (k==0)
	  if((quarks[mm].M()+ quarks[kk].M() - 80.40) < (lv1.M() - 80.40) )
	    {
	      lv1 =  quarks[mm]+quarks[kk];
	    }	  //min ((lv.M()-80.40), ((quarks[m]+ quarks[k]).M() - 80.40));
          else
            continue;
	 
	    }
	}
      if(!isnan(lv1.M()))
	{
	  cout << "mass2: " << lv1.M() <<endl;
	  hist_quark->Fill(lv1.M());
	}
	 }

       if (is_fullLeptonic)
	 {

      TLorentzVector lv (0,0,0,0);
      TLorentzVector lv1 (0,0,0,0);
      Int_t r =0;
      Int_t w =0;	    
      //Double_t mass = 0.0;
      for (Int_t k =0; k<lepts.size(); k++)
	{
	  for (Int_t m =0; m<lepts.size(); m++)
	    {	    
	    if(m==k)
	      continue;

	  lv = lepts[0] + lepts[1];
	  //      if (k==0)
	  if((lepts[m].M()+ lepts[k].M() - 80.40) < (lv.M() - 80.40) )
	    {
	      r =m;
	      w =k;	    
	      lv =  lepts[m]+lepts[k];
	    }	  //min ((lv.M()-80.40), ((quarks[m]+ quarks[k]).M() - 80.40));
	  //	  else 
	  //	    continue;
	  //      cout << "quarks.Pt(): " <<quarks[k].M() << endl;    
	    }
	}
      if(!isnan(lv.M()))
	{
	  cout << "r: w: " << r << " "<< w <<endl;
	  cout << "mass1: " << lv.M() <<endl;
	  hist_lept->Fill(lv.M());
	}

      for (Int_t kk =0; kk<quarks.size(); kk++)
	{
	  if(kk==w)
	    continue;
	  for (Int_t mm =0; mm<quarks.size(); mm++)
	    {
	    if(mm==kk || mm==r)
	      continue;
	    lv1 = quarks[0] + quarks[1];
	  //      if (k==0)
	  if((quarks[mm].M()+ quarks[kk].M() - 80.40) < (lv1.M() - 80.40) )
	    {
	      lv1 =  quarks[mm]+quarks[kk];
	    }	
          else
            continue;
	  //      cout << "quarks.Pt(): " <<quarks[k].M() << endl;
	    }
	}
      if(!isnan(lv1.M()))
	{
	  cout << "mass2: " << lv1.M() <<endl;
	  hist_quark->Fill(lv1.M());
	}
	 }
       
       lepts.clear();
       quarks.clear();
       cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;	 	    
       
       
       
       
    }
  
  
  TCanvas *col  = new TCanvas("col", "col", 0, 0, 900, 700);
  col->Divide(2,1);
  col->cd(1);   
  hist_lept->SetMaximum(30);
  hist_lept->SetLineColor(kPink);    
  hist_lept->Draw();

  col->cd(2);
  hist_quark->SetMaximum(30);     
  hist_quark->SetLineColor(kBlue);
  hist_quark->Draw();

  

  
  TFile*file = new TFile("w.root","RECREATE");
  file->cd();
  hist_lept->Write();
  hist_quark->Write();
  file->Close();
  
  delete file;
} 

	  
     
