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
#include "LHEF.h"
#include "TClonesArray.h" 
using namespace std;

void ttbar50_all()
{

  TFile *f = new TFile("ttbar50k.root","read");
  TTree *lhef = (TTree*)f->Get("LHEF");
   Double_t mass [12][12];

   LHEF *test = new LHEF(lhef);

  vector<TLorentzVector> quarks,lepts;
  TLorentzVector quark,lept;


 

  TH1D *hist_quarkfull = new TH1D("hist_quark" , "W Mass", 40 , 0, 200);
  //  TH1D hist_quark("hist_quark" , "W Mass", 1000 , 0, 1000);
  
  TH1D *hist_diff = new TH1D("hist_diff" , "fullquarkmass-W Mass", 1000 , -100, 100);
  TH1D *hist_diff1 = new TH1D("hist_diff1" , "semileptonmass-W Mass", 1000 , -100, 100);
  TH1D *hist_diff2 = new TH1D("hist_diff2" , "semiquarkmass-W Mass", 1000 , -100, 100);
  TH1D *hist_quarksemi = new TH1D("hist_quarksemi" , "W Mass", 40 , 0, 200);
  TH1D *hist_diff3 = new TH1D("hist_diff3" , "fullleptonmass-W Mass", 1000 , -100, 100);
  TH1D *hist_leptsemi = new TH1D ("hist_leptsemi" , "W Mass", 40 , 0, 200);
  TH1D *hist_leptfull = new TH1D ("hist_leptfull" , "W Mass", 40 , 0, 200);
  


 Long64_t nevt1 = lhef->GetEntries();
 //cout<<nevt1<<endl;
 //event loop
  for (Long64_t j=1; j<nevt1; j++)
    {
    test->GetEntry(j);

  Bool_t  is_semiLeptonic = false;
  Bool_t  is_fullHadronic=false;
  Bool_t  is_fullLeptonic=false;

  // cout<<"test->Particle_size= "<< test->Particle_size <<endl;
    
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



      }//Loops for particles

    //  cout<<"quarks size()= "<< quarks.size() <<endl;
    //cout<<"lepts size()= " << lepts.size() <<endl;
    
      if(quarks.size()>=4)
      	is_fullHadronic = true;      
      if(lepts.size()==2)
      	is_semiLeptonic = true;
      if(lepts.size()>2)
      	is_fullLeptonic = true;
      
      // cout <<"is_fullHadronic: " << is_fullHadronic <<endl;
      //  cout <<"is_semiLeptonic: " << is_semiLeptonic <<endl;
      // cout <<"is_fullLeptonic: " << is_fullLeptonic <<endl;
      

  Double_t a=1000,b=1000;
      Int_t submm=-1,subkk=-1,subk=-1,subm=-1,submass=-1000,submass1=-1000;
      
		if (is_fullHadronic)
		  {

		    for (Int_t kk =0; kk <(Int_t) quarks.size(); kk++)
		      {
			for (Int_t mm =kk+1; mm <(Int_t) quarks.size(); mm++)
			  {
			    mass[kk][mm] = ((quarks[mm]+quarks[kk]).M());
			    //cout<<"MASS= "<<mass[kk][mm]<<endl;
			    
			    double m=mass[kk][mm];	      
			    // cout<<"MASS Dif= "<<(m-80.4)<<endl;
   
			    if( a >fabs(m-80.4))
			      {
				a =fabs (m-80.4);
				submass=m;
				submm=mm;
				subkk=kk;

			      }
			    // cout << "submm:  " << mm << " "<<endl;
			    // cout<< "min mass:"<< m<<endl; 
			  }
				   
				hist_diff->Fill(a);
				hist_quarkfull->Fill(submass);
		      }
		   

		    for (Int_t k =0; k <(Int_t) quarks.size(); k++)
		      {
		    	if(subkk==k)
		    	  continue;
		    	for (Int_t m =k+1; m <(Int_t) quarks.size(); m++)
		    	  {
		    	    if(submm==m)
		    	      continue;
 
		    	    mass[k][m] = ((quarks[m] + quarks[k]).M());
			   
			    double m1=mass[k][m];
				  
		    	    if( b >fabs(m1-80.40))
		    	      {
		    		b = fabs(m1-80.40);
				//	cout<<"b:"<<b<<endl;
				    
				submass1=m1;
				//cout<<" submass1:"<<submass1<<endl;
			        subm=m;
				subk=k;
		    		 
		    	      }
			   
		    	  }
		       
			hist_diff->Fill(b);
			hist_quarkfull->Fill(submass1);
		      }
		   	

		  }//loop for fullhadronic

      	if (is_semiLeptonic)
		  {

		    for (Int_t tt =0; tt< (Int_t)lepts.size(); tt++)
		      {
			for (Int_t ss =tt+1; ss <(Int_t) lepts.size(); ss++)
			  {
			    mass[tt][ss] = ((lepts[tt]+lepts[ss]).M());
			    // cout<<"MASS= "<<mass[kk][mm]<<endl;
			    
			    double m=mass[tt][ss];	      
			    // cout<<"MASS Dif= "<<(m-80.4)<<endl;
   
			    if( a >(m-80.4))
			      {
				a =  (m-80.4);
				submass=m;
				submm=tt;
				subkk=ss;

			      }
			    //  cout << "submm:  " << mm << " "<<endl;
			    //cout<< "min mass:"<< m<<endl; 
			  }
			//	cout << "subkk:  " << kk << " "<<endl;
			   
			//	cout<< "min mass after:"<< a<<endl; 
				hist_diff1->Fill(a);
				hist_leptsemi->Fill(submass);

		      }
		   

		    for (Int_t t =0; t <(Int_t)quarks.size(); t++)
		      {
		    
		    	for (Int_t s =t+1; s <(Int_t)quarks.size(); s++)
		    	  {
		    	    mass[s][t] = ((quarks[s] + quarks[t]).M());
			   
			    double m1=mass[s][t];
				  
		    	    if( b >(m1-80.40))
		    	      {
		    		b =  (m1-80.40);
				    
				submass1=m1;
			        subm=s;
				subk=t;
		    		 
		    	      }
			   
		    	    //cout<< "min mass after:"<< b<<endl;
			    // cout << "subm: " << " "<< m <<endl;
		    	  }
			//	cout << "subk: " << " "<< k <<endl;
			   
		    	//cout<< "min mass after:"<< b<<endl;
			hist_diff2->Fill(b);	     
		    	hist_quarksemi->Fill(submass1);
		      }

		  }//loop for semileptonic
		  
	  	if (is_fullLeptonic)
		  {

		    for (Int_t pp =0; pp <(Int_t)lepts.size(); pp++)
		      {
			for (Int_t rr =pp+1; rr<(Int_t)lepts.size(); rr++)
			  {
			    mass[pp][rr] = ((lepts[pp]+lepts[rr]).M());
			    // cout<<"MASS= "<<mass[kk][mm]<<endl;
			    
			    double m=mass[pp][rr];	      
			    // cout<<"MASS Dif= "<<(m-80.4)<<endl;
   
			    if( a >(m-80.4))
			      {
				a =  (m-80.4);
				submass=m;
				submm=pp;
				subkk=rr;

			      }
			    //  cout << "submm:  " << mm << " "<<endl;
			    //cout<< "min mass:"<< m<<endl; 
			  }
			//	cout << "subkk:  " << kk << " "<<endl;
			   
			//	cout<< "min mass after:"<< a<<endl; 
				hist_diff3->Fill(a);
				hist_leptfull->Fill(submass);

		      }
		   

		    for (Int_t p=0; p <(Int_t)lepts.size(); p++)
		      {
		        if(submm==p)
		    continue;
		      
		    	for (Int_t r =p+1; r <(Int_t)lepts.size(); r++)
		    	  {
			  if(subkk==r)
			  continue;
		    	    mass[p][r] = ((lepts[p] + lepts[r]).M());
			   
			    double m1=mass[p][r];
				  
		    	    if( b >(m1-80.40))
		    	      {
		    		b =  (m1-80.40);
				    
				submass1=m1;
			        subm=r;
				subk=p;
		    		 
		    	      }
			   
		    	    //cout<< "min mass after:"<< b<<endl;
			    // cout << "subm: " << " "<< m <<endl;
		    	  }
			//	cout << "subk: " << " "<< k <<endl;
			   
		    	//cout<< "min mass after:"<< b<<endl;
			hist_diff3->Fill(b);	     
		    	hist_leptfull->Fill(submass1);
		      }

		  }//loop for fullleptonic
      


		// cout<<"##################"<<endl;	 

     lepts.clear();
     quarks.clear();
     
    }//Loops for events

  
  TCanvas *t = new TCanvas("t","t",0,0,900,700); 
  t->Divide(2,2);
t->cd(1);
hist_quarkfull->GetXaxis()->SetTitle(" sum of quarks for full hadronic");
hist_quarkfull->SetMaximum(100);
hist_quarkfull->SetLineColor(kPink);    
hist_quarkfull->Draw();

t->cd(2);
hist_quarksemi->GetXaxis()->SetTitle(" sum of quarks for semileptonic");
hist_quarksemi->SetMaximum(100);
hist_quarksemi->SetLineColor(kBlue);    
hist_quarksemi->Draw("same");

t->cd(3);
hist_leptsemi->GetXaxis()->SetTitle(" sum of lepts for semileptonic");
hist_leptsemi->SetMaximum(100);
hist_leptsemi->SetLineColor(kPink);    
hist_leptsemi->Draw();

t->cd(4);
hist_leptfull->GetXaxis()->SetTitle(" sum of lepts for full leptonic");
hist_leptfull->SetMaximum(110);
hist_leptfull->SetLineColor(kPink);    
hist_leptfull->Draw();

 TCanvas *diff = new TCanvas("diff","diff",0,0,900,700); 
  diff->Divide(2,2);
 
 diff->cd(1);
hist_diff->GetXaxis()->SetTitle("fullquarkmass-W Mass ");
hist_diff->SetMaximum(100);
hist_diff->SetLineColor(kPink);    
hist_diff->Draw();
 
  diff->cd(2);
hist_diff1->GetXaxis()->SetTitle("semileptonmass-W Mass ");
hist_diff1->SetMaximum(100);
hist_diff1->SetLineColor(kPink);    
hist_diff1->Draw();
 
  diff->cd(3);
hist_diff2->GetXaxis()->SetTitle("semiquarkmass-W Mass ");
hist_diff2->SetMaximum(100);
hist_diff2->SetLineColor(kPink);    
hist_diff2->Draw();

  diff->cd(4);
hist_diff3->GetXaxis()->SetTitle("fullleptonmass-W Mass ");
hist_diff3->SetMaximum(100);
hist_diff3->SetLineColor(kPink);    
hist_diff3->Draw();
 


  
  TFile *file = new TFile("wmass_all.root","RECREATE");
  file->cd();
 hist_quarkfull->Write();
 hist_quarksemi->Write();
 hist_leptsemi->Write();
 hist_leptfull->Write();
 hist_diff->Write();
 hist_diff1->Write();
 hist_diff2->Write();
 hist_diff3->Write();
 file->Close();
  
delete file;
    }
