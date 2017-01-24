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

void ttbar_fullhadroni()
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


  TH1D * hist_quark = new TH1D ("hist_quark" , "W Mass", 200 , 0, 1000);
  TH1D * hist_diff = new TH1D ("hist_diff" , "mass-W Mass", 1000 , -100, 100);
  TH1D * hist_quark1 = new TH1D ("hist_quark1" , "W Mass", 200 , 0, 1000);
  TH1D * hist_diff1 = new TH1D ("hist_diff1" , "mass-W Mass", 1000 , -100, 100);
  TH1D * hist_lept = new TH1D ("hist_lept" , "W Mass", 200 , 0, 1000);
  
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
      
      Double_t a=1000,b=1000;
      Int_t submm=-1,subkk=-1,subk=-1,subm=-1,submass=-1000,submass1=-1000;
		if (is_fullHadronic)
		  {

		    for (Int_t kk =0; kk < quarks.size(); kk++)
		      {
			for (Int_t mm =kk+1; mm < quarks.size(); mm++)
			  {
			    mass[kk][mm] = ((quarks[mm]+quarks[kk]).M());
			    // cout<<"MASS= "<<mass[kk][mm]<<endl;
			    
			    double m=mass[kk][mm];	      
			    // cout<<"MASS Dif= "<<(m-80.4)<<endl;
   
			    if( a >(m-80.4))
			      {
				a = (m-80.4);
				submass=m;
				submm=mm;
				subkk=kk;

			      }
			    //  cout << "submm:  " << mm << " "<<endl;
			    //cout<< "min mass:"<< m<<endl; 
			  }
			//	cout << "subkk:  " << kk << " "<<endl;
			   
			cout<< "min mass after:"<< a<<endl; 
				hist_diff->Fill(a);
				hist_quark->Fill(submass);

		      }
		   

		    for (Int_t k =0; k < quarks.size(); k++)
		      {
		    	if(subkk==k)
		    	  continue;
		    	for (Int_t m =k+1; m < quarks.size(); m++)
		    	  {
		    	    if(submm==m)
		    	      continue;
 
		    	    mass[k][m] = ((quarks[m] + quarks[k]).M());
			   
			    double m1=mass[k][m];
				  
		    	    if( b >(m1-80.40))
		    	      {
		    		b =  (m1-80.40);
				    
				submass1=m1;
			        subm=m;
				subk=k;
		    		 
		    	      }
			   
		    	    //cout<< "min mass after:"<< b<<endl;
			    // cout << "subm: " << " "<< m <<endl;
		    	  }
			//	cout << "subk: " << " "<< k <<endl;
			   
			//	cout<< "min mass after:"<< b<<endl;
			hist_diff1->Fill(b);	     
		    	hist_quark1->Fill(submass1);
		      }

		  }//loop for fullhadronic
	  
	
		// 	cout<<"j:"<<j<<endl;
     
		cout<<"##################"<<endl;	 

            lepts.clear();
            quarks.clear();
	   
    }//Loops for events
    
TCanvas *third = new TCanvas("third","third",0,0,900,700); 
  third->Divide(2,2);
third->cd(1);
hist_quark->GetXaxis()->SetTitle(" sum of quarks");
hist_quark->SetMaximum(30);
hist_quark->SetLineColor(kPink);    
hist_quark->Draw();
hist_quark1->GetXaxis()->SetTitle(" sum  of quarks");
hist_quark1->SetMaximum(30);
hist_quark1->SetLineColor(kPink);    
hist_quark1->Draw("same");

third->cd(2);
hist_quark1->GetXaxis()->SetTitle(" sum of quarks");
hist_quark1->SetMaximum(30);
hist_quark1->SetLineColor(kBlue);    
hist_quark1->Draw("same");

third->cd(3);
hist_diff->GetXaxis()->SetTitle(" diff of Quarkmass and Wmass");
hist_diff->SetMaximum(30);
hist_diff->SetLineColor(kPink);    
hist_diff->Draw();

third->cd(4);
hist_diff1->GetXaxis()->SetTitle(" diff of Quarkmass and Wmass");
hist_diff1->SetMaximum(30);
hist_diff1->SetLineColor(kPink);    
hist_diff1->Draw();




TFile *file = new TFile("wmass.root","RECREATE");
file->cd();
//hist_lept->Write();
hist_quark->Write();
 hist_diff->Write();
hist_diff1->Write();
 hist_quark1->Write();
file->Close();
  
delete file;
} 

	  
     
