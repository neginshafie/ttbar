// #include "TROOT.h"
// #include "TFile.h"
// #include "TTree.h"
// #include "TBrowser.h"
// #include "TRandom.h"
// #include "TMath.h"
// #include "TH2.h"
// #include "TCanvas.h"
// #include <vector>
// #include "TLorentzVector.h"
// #include <iostream>
//#include "LHEF.C"
#include "LHEF1.h"
// #include "TClonesArray.h"
// #include "TDirectory.h"

using namespace std;

void ttbar_fullhadronic(){

  TFile *f = new TFile("./ttbar50k.root","read");
  TTree *lhef = (TTree*)f->Get("LHEF");
  Double_t mass [12][12];

  LHEF *test = new LHEF(lhef);
  //  LHEF test(lhef);

  vector<TLorentzVector> quarks,lepts;
  TLorentzVector quark,lept;


 
  TH1D * hist_fullHadronic = new TH1D ("hist_fullHadronic" , "W Mass Full Hadronic", 100 , 0, 100);
  //  TH1D *hist_quark = new TH1D("hist_quark" , "W Mass", 1000 , 0, 1000);
  //  TH1D hist_quark("hist_quark" , "W Mass", 1000 , 0, 1000);
  
  //  TH1D *hist_diff = new TH1D("hist_diff" , "mass-W Mass", 1000 , -100, 100);
  //  TH1D *hist_secondquark = new TH1D("hist_quark1" , "W Mass", 1000 , 0, 1000);
  //  TH1D *hist_diffwmass = new TH1D("hist_diff1" , "mass-W Mass", 1000 , -100, 100);
  //TH1D * hist_lept = new TH1D ("hist_lept" , "W Mass", 1000 , 0, 1000);
  


 Long64_t nevt1 = lhef->GetEntries();
 cout<<nevt1<<endl;
 //event loop
  for (Long64_t j=1; j<nevt1; j++)
    {
    test->GetEntry(j);

    Bool_t  is_semiLeptonic = false;
    Bool_t  is_fullHadronic=false;
    Bool_t  is_fullLeptonic=false;

    cout<<"test->Particle_size= "<< test->Particle_size <<endl;
    
    //particle loop
    for(Int_t n=0;n<test->Particle_size;n++)
      {
      
      //status loop
      	if (test->Particle_Status[n]==1)
	  {

	cout << "test->Particle_Status[n]" << test->Particle_Status[n] << "test->Particle_PID[n]" << test->Particle_PID[n]<< endl;

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
      
       cout <<"is_fullHadronic: " << is_fullHadronic <<endl;
       cout <<"is_semiLeptonic: " << is_semiLeptonic <<endl;
       cout <<"is_fullLeptonic: " << is_fullLeptonic <<endl;
      

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
				a = fabs(m-80.4);
				submass=m;
				submm=mm;
				subkk=kk;

			      }
			    // cout << "submm:  " << mm << " "<<endl;
			    // cout<< "min mass:"<< m<<endl; 
			  }
				   
			hist_fullHadronic->Fill(submass);	
			//			hist_diff->Fill(a);
			//				hist_quark->Fill(submass);
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
		        hist_fullHadronic->Fill(submass1);
			//			hist_diffwmass->Fill(b);
			//			hist_quark->Fill(submass1);
		      }
		   	

		  }//loop for fullhadronic

      


		// cout<<"##################"<<endl;	 

     lepts.clear();
     quarks.clear();
     
    }//Loops for events

  //  delete lhef, f;
  // 	hist_quark->Draw();
	//}
 
  //  TCanvas *tcal = new TCanvas("tcal","tcal",200,10,900,700);
  
   
/* tcal->Divide(2,2); */
//    tcal->cd(); 

    //    hist_quark->Write();
  //  hist_quark->Draw();

/* hist_quark1->GetXaxis()->SetTitle(" sum of quarks"); */
/* hist_quark1->SetMaximum(30); */
/* hist_quark1->SetLineColor(kPink); */
/* hist_quark1->Draw(); */
/* hist_quark1->GetXaxis()->SetTitle(" sum  of quarks"); */
/* hist_quark1->SetMaximum(30); */
/* hist_quark1->SetLineColor(kPink);     */
/* hist_quark1->Draw("same"); */

//  TCanvas *col  = new TCanvas("col", "col", 0, 0, 900, 700);
  //  col->Divide(2,2);
  //  col->cd();
  //  hist_fullHadronic->SetMaximum(30);
  //  hist_fullHadronic->SetLineColor(kPink);
  hist_fullHadronic->Draw();
  //  hist_quark->Draw();
  //  col->Draw();

  //TFile *file = new TFile("w1mass.root","RECREATE");
  //file->cd();
  //hist_quark->Write();
//hist_diff->Write();
//hist_diff1->Write();
//hist_quark1->Write();
//file->Close();
  
//delete file;
	 
} 
