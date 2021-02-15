#include <iostream>
#include <math.h>
#include <TH1D.h>

double Delta(TH1D* hdata, TH1D* hmc)
{

double efficiency[100] = {0.};
double error2[100] = {0.} ;

double dev = 0.; 

TH1D* hrat = (TH1D*)hmc->Clone();
hrat->Divide(hdata);

int nbins = hdata->GetNbinsX() ;
double errsq = 1.;

for(int ij=0; ij<nbins; ij++){

  efficiency[ij] = hmc->GetBinContent(ij+1)*1./max(1.e-7,hdata->GetBinContent(ij+1)) ;

  double rel_err_data = max(1.e-7,hdata->GetBinError(ij+1))*1./max(1.e-7,hdata->GetBinContent(ij+1)) ;
  double rel_err_mc = max(1.e-7,hmc->GetBinError(ij+1))*1./max(1.e-7,hmc->GetBinContent(ij+1)) ;

  error2[ij] = pow(rel_err_data,2.)+pow(rel_err_mc,2.) ;
  //cout<<"bin "<<ij+1<<error2[ij]<<" eff "<<efficiency[ij]<<endl;
  if(efficiency[ij]>1.e-7){
  dev+= pow(fabs(1.-1./efficiency[ij]),2.)*1./max(1.e-7,error2[ij]) ;
  }
  errsq+=error2[ij];
 }//ij
 //dev=int(1000.*dev*1./errsq)/1000. ;

dev = sqrt(dev); 
dev = dev*1./sqrt(errsq) ;
return dev;

}

