#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TMath.h"
#include "TH2.h"
#include "TCanvas.h"
#include <vector>
#include "TLorentzVector.h"
#include <iostream>
#include "LHEF.C"
#include "TClonesArray.h"
using namespace std;

void ttbar50_specifiedID()
{

  TFile *f = new TFile("ttbar50k.root","read");
  TTree *lhef = (TTree*)f->Get("LHEF");
   Double_t mass [12][12];

    LHEF *test = new LHEF(lhef);

  vector<TLorentzVector> quarks,lepts;
  TLorentzVector quark,lept;


 

  TH1D *hist_quark = new TH1D("hist_quark" , "W Mass", 20 , 0, 200);
  TH1D *hist_quark1 = new TH1D("hist_quark1" , "W Mass", 40 , 0, 200);
  TH1D *hist_quark3 = new TH1D("hist_quark3" , "W Mass", 40 , 0, 200);
  TH1D *hist_quark4 = new TH1D("hist_quark4" , "W Mass", 20 , 0, 200);
  TH1D * hist_lept = new TH1D ("hist_lept" , "W Mass", 40 , 0, 200);
  TH1D * hist_lept1 = new TH1D ("hist_lept1" , "W Mass", 40 , 0, 200);
  TH1D *hist_quarksemi = new TH1D("hist_quarksemi" , "W Mass", 20 , 0, 200);
  TH1D *hist_quarksemi1 = new TH1D("hist_quarksemi1" , "W Mass", 20 , 0, 200);
  TH1D *hist_quarksemi2 = new TH1D("hist_quarksemi2" , "W Mass", 20 , 0, 200);
  TH1D *hist_quarksemi3 = new TH1D("hist_quarksemi2" , "W Mass", 20 , 0, 200);
  TH1D * hist_leptfull = new TH1D ("hist_leptfull" , "W Mass", 40 , 0, 200);
  TH1D * hist_leptfull1 = new TH1D ("hist_leptfull1" , "W Mass", 40 , 0, 200);



 Long64_t nevt1 = lhef->GetEntries();
 cout<<nevt1<<endl;
 //event loop
  for (Long64_t j=1; j<nevt1; j++)
    {
    test->GetEntry(j);

  Bool_t  is_semiLeptonic = false;
  Bool_t  is_fullHadronic=false;
  Bool_t  is_fullLeptonic=false;

  //cout<<"test->Particle_size= "<< test->Particle_size <<endl;
    
    //particle loop
    for(Int_t n=0;n<test->Particle_size;n++)
      {
      
      //status loop
      	if (test->Particle_Status[n]==1)
	  {

	/* cout << "test->Particle_Status[n]" << test->Particle_Status[n] << "test->Particle_PID[n]" << test->Particle_PID[n]<< endl; */

	    if (fabs(test->Particle_PID[n])==1 || fabs(test->Particle_PID[n])==2 || fabs(test->Particle_PID[n])==3 || fabs(test->Particle_PID[n])==4)
	      {
	
		quark.SetPtEtaPhiM(test->Particle_PT[n],test->Particle_Eta[n],test->Particle_Phi[n],test->Particle_M[n]);
		quarks.push_back(quark);
		
	      }
       
	    else if (fabs(test->Particle_PID[n])==11 || fabs(test->Particle_PID[n])==12 || fabs(test->Particle_PID[n])==13 || fabs(test->Particle_PID[n])==14 || fabs(test->Particle_PID[n])==15 || fabs(test->Particle_PID[n])==16)
	   { 
	    
	     lept.SetPtEtaPhiM(test->Particle_PT[n],test->Particle_Eta[n],test->Particle_Phi[n],test->Particle_M[n]);
	     lepts.push_back(lept);
	     
	   }
	    
	  }//status loop
    

    //  cout<<"quarks size()= "<< quarks.size() <<endl;
    //cout<<"lepts size()= " << lepts.size() <<endl;
    
      if(quarks.size()>=4)
      	is_fullHadronic = true;      
      if(lepts.size()==2)
      	is_semiLeptonic = true;
      if(lepts.size()>2)
      	is_fullLeptonic = true;
      
      // cout <<"is_fullHadronic: " << is_fullHadronic <<endl;
      //cout <<"is_semiLeptonic: " << is_semiLeptonic <<endl;
      //cout <<"is_fullLeptonic: " << is_fullLeptonic <<endl;
       
       	if (is_fullHadronic)
	  {
	  	if(test->Particle_PID[n]==2 || test->Particle_PID[n]==-1)
		  {
		    for (Int_t jj=0; jj < (Int_t)quarks.size() ; jj++)
		      {
      
			for (Int_t kk = jj+1; kk <(Int_t)quarks.size(); kk++)
			  {
			    mass[jj][kk]=(((quarks[jj]+ quarks[kk]).M()));
			    double m= mass[jj][kk];
			       hist_quark->Fill(m);

			    //cout<< "mass1:"<<mass[jj][kk]<<endl;
			   
			  }
		      }
		    // hist_quark->Fill(m);
		  }
	  
		else if(test->Particle_PID[n]==-2 || test->Particle_PID[n]==1)
		  {
		    for (Int_t m=0; m < (Int_t)quarks.size() ; m++)
		      {
      
			for (Int_t k = m+1; k <(Int_t)quarks.size(); k++)
			  {
			    mass[m][k]=(((quarks[m]+ quarks[k]).M()));
			    // cout<< "mass2:"<<mass[m][k]<<endl;  
			    hist_quark1->Fill(mass[m][k]);
			  }
		      }
		  }
	  
		if(test->Particle_PID[n]==3 || test->Particle_PID[n]==-4)
		  {
		    for (Int_t mm=0; mm< (Int_t)quarks.size() ; mm++)
		      {
      
			for (Int_t tt = mm+1; tt <(Int_t)quarks.size(); tt++)
			  {
			    mass[mm][tt]=(((quarks[mm]+ quarks[tt]).M()));
			    // cout<< "mass3:"<<mass[mm][tt]<<endl;  	      
			    hist_quark3->Fill(mass[mm][tt]);
			  }
		      }
		  }
		else if(test->Particle_PID[n]==-3 || test->Particle_PID[n]==4)
		  {
		    for (Int_t t=0; t < (Int_t)quarks.size() ; t++)
		      {
      
			for (Int_t s= t+1; s <(Int_t)quarks.size(); s++)
			  {
			    mass[t][s]=(((quarks[t]+ quarks[s]).M()));
			    //cout<< "mass4:"<<mass[t][s]<<endl;   
			    hist_quark4->Fill(mass[t][s]);
			  }
		      }
		  }	
	  }//loop for fullhadronic
	

    if (is_semiLeptonic)
	  {
	    	if(test->Particle_PID[n]==2 ||test->Particle_PID[n]==-1)
		  {
		    for (Int_t rr=0; rr < (Int_t)quarks.size() ; rr++)
		      {
      
			for (Int_t pp = rr+1; pp <(Int_t)quarks.size(); pp++)
			  {
			    mass[rr][pp]=(fabs((quarks[rr]+ quarks[pp]).M()));
			    double m= mass[rr][pp];
			       hist_quarksemi->Fill(m);

			    //cout<< "mass1:"<<mass[jj][kk]<<endl;
			   
			  }
		      }
		    // hist_quark->Fill(m);
		  }
	  
		else if(test->Particle_PID[n]==-2 || test->Particle_PID[n]==1)
		  {
		    for (Int_t r=0; r < (Int_t)quarks.size() ; r++)
		      {
      
			for (Int_t p= r+1; p <(Int_t)quarks.size(); p++)
			  {
			    mass[r][p]=(fabs((quarks[r]+ quarks[p]).M()));
			    // cout<< "mass2:"<<mass[m][k]<<endl;  
			    hist_quarksemi1->Fill(mass[r][p]);
			  }
		      }
		  }
	  
		if(test->Particle_PID[n]==3 || test->Particle_PID[n]==-4)
		  {
		    for (Int_t h=0; h< (Int_t)quarks.size() ; h++)
		      {
      
			for (Int_t n = h+1; n <(Int_t)quarks.size(); n++)
			  {
			    mass[h][n]=(fabs((quarks[h]+ quarks[n]).M()));
			    // cout<< "mass3:"<<mass[mm][tt]<<endl;  	      
			    hist_quarksemi2->Fill(mass[h][n]);
			  }
		      }
		  }
		else if(test->Particle_PID[n]==-3 || test->Particle_PID[n]==4)
		  {
		    for (Int_t hh=0; hh < (Int_t)quarks.size() ; hh++)
		      {
      
			for (Int_t nn= hh+1; nn <(Int_t)quarks.size(); nn++)
			  {
			    mass[hh][nn]=(fabs((quarks[hh]+ quarks[nn]).M()));
			    //cout<< "mass4:"<<mass[t][s]<<endl;   
			    hist_quarksemi3->Fill(mass[hh][nn]);
			  }
		      }
		  }	
	      
	
		if(fabs(test->Particle_PID[n])==11 || fabs(test->Particle_PID[n])==12)
	  {
	    for (Int_t a=0; a < (Int_t)lepts.size() ; a++)
	      {
      
		for (Int_t b= a+1; b <(Int_t)lepts.size(); b++)
		  {
		    mass[a][b]=(fabs((lepts[a]+ lepts[b]).M()));
		    //cout<< "mass4:"<<mass[t][s]<<endl;   
		    hist_lept->Fill(mass[a][b]);
		  }
	      }
	  }
		if(fabs(test->Particle_PID[n])==13 || fabs(test->Particle_PID[n])==14)
	  {
	    for (Int_t c=0; c < (Int_t)lepts.size() ; c++)
	      {
      
		for (Int_t d= c+1; d <(Int_t)lepts.size(); d++)
		  {
		    mass[c][d]=(fabs((lepts[c]+ lepts[d]).M()));
		    //cout<< "mass4:"<<mass[t][s]<<endl;   
		    hist_lept1->Fill(mass[c][d]);
		  }
	      }
	  }
	  }//loop for semileptonic
    
    if(is_fullLeptonic)
      {
    
	if(fabs(test->Particle_PID[n])==11 || fabs(test->Particle_PID[n])==12)
	  {
	    for (Int_t e=0; e < (Int_t)lepts.size() ; e++)
	      {
      
		for (Int_t f= e+1; f <(Int_t)lepts.size(); f++)
		  {
		    mass[e][f]=(fabs((lepts[e]+ lepts[f]).M()));
		    //cout<< "mass4:"<<mass[t][s]<<endl;   
		    hist_leptfull->Fill(mass[e][f]);
		  }
	      }
	  }
	if(fabs(test->Particle_PID[n])==13 || fabs(test->Particle_PID[n])==14)
	  {
	    for (Int_t g=0; g< (Int_t)lepts.size() ; g++)
	      {
      
		for (Int_t ff= g+1; ff <(Int_t)lepts.size(); ff++)
		  {
		    mass[g][ff]=(fabs((lepts[g]+ lepts[ff]).M()));
		    //cout<< "mass4:"<<mass[t][s]<<endl;   
		    hist_leptfull1->Fill(mass[g][ff]);
		  }
	      }
	  }
      }//loop for fullleptonic
    
      }//loop for particles
	 
    // cout<<"##################"<<endl;	 

            lepts.clear();
            quarks.clear();
     
    }//loop for event


  TCanvas *hadronic = new TCanvas("hadronic","hadronic",0,0,900,700); 
  hadronic->Divide(2,2);
hadronic->cd(1);
hist_quark->GetXaxis()->SetTitle("  sum of u&dbar quarks");
hist_quark->SetMaximum(200);
hist_quark->SetLineColor(kPink);    
hist_quark->Draw();

hadronic->cd(2);
hist_quark3->GetXaxis()->SetTitle("sum of s&cbar quarks");
hist_quark3->SetMaximum(100);
hist_quark3->SetLineColor(kBlue);    
hist_quark3->Draw("same");
 
 hadronic->cd(3);
hist_quark1->GetXaxis()->SetTitle(" sum of d&ubar quarks");
hist_quark1->SetMaximum(100);
hist_quark1->SetLineColor(kPink);    
hist_quark1->Draw();

 hadronic->cd(4);
hist_quark4->GetXaxis()->SetTitle(" sum of c&sbar quarks");
hist_quark4->SetMaximum(200);
hist_quark4->SetLineColor(kPink);    
hist_quark4->Draw();

 TCanvas *semi = new TCanvas("semi","semi",0,0,900,700); 
  semi->Divide(2,2);
semi->cd(1);
hist_lept->GetXaxis()->SetTitle(" sum of e&ne leptons ");
hist_lept->SetMaximum(200);
hist_lept->SetLineColor(kPink);    
hist_lept->Draw();

semi->cd(2);
hist_lept1->GetXaxis()->SetTitle(" sum of meun&nmuen leptons");
 hist_lept1->SetMaximum(200);
hist_lept1->SetLineColor(kPink);    
hist_lept1->Draw();
 
 
 
  semi->cd(3);
hist_quarksemi1->GetXaxis()->SetTitle("sum of d&ubar quarks ");
hist_quarksemi1->SetMaximum(200);
hist_quarksemi1->SetLineColor(kPink);    
hist_quarksemi1->Draw();
 
  semi->cd(4);
hist_quarksemi2->GetXaxis()->SetTitle("sum of s&cbar quarks ");
hist_quarksemi2->SetMaximum(200);
hist_quarksemi2->SetLineColor(kPink);    
hist_quarksemi2->Draw();

  

  TCanvas *leptonic = new TCanvas("leptonic","leptonic",0,0,900,700); 
  leptonic->Divide(2,1);

  leptonic->cd(1);
hist_leptfull->GetXaxis()->SetTitle(" sum of e&ne leptons ");
hist_leptfull->SetMaximum(200);
hist_leptfull->SetLineColor(kPink);    
hist_leptfull->Draw();

leptonic->cd(2);
hist_leptfull1->GetXaxis()->SetTitle(" sum of meun&nmuen leptons");
 hist_leptfull1->SetMaximum(200);
hist_leptfull1->SetLineColor(kPink);    
hist_leptfull1->Draw();

TFile *file = new TFile("w50massall.root","RECREATE");
file->cd();
 hist_quark1->Write();
 hist_quark3->Write();
 hist_quark4->Write();
 hist_quark->Write();
 hist_lept->Write();
 hist_lept1->Write();
 hist_quarksemi->Write();
 hist_quarksemi1->Write();
 hist_quarksemi2->Write();
 hist_quarksemi3->Write();
 hist_leptfull->Write();
 hist_leptfull1->Write();
 file->Close();
  
delete file;
}
      
