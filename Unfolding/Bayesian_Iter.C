void Bayesian_Iter()
{
const int num = 11;
double xval[num]={1,2,3,4,5,6,7,8,9,10,11};
double yval[num] = {148.823,112.132,97.3361,93.3894,91.117,89.0713,87.5872,86.8477,86.7542,87.0873,87.6019};

for(int ij=0; ij<num; ij++){
yval[ij]*=1./62;
}

char name[100];
TCanvas *c1 = new TCanvas("Bayesian_Iteration_ak4_y1","Bayesian_Iteration_ak4_y1",600,600);
c1->cd();

TGraphErrors *dataplot = new TGraphErrors(num,xval,yval,NULL,NULL);
sprintf(name,"Bayesian Unfolding for ak4 Jets y<0.5");
dataplot->SetTitle(name);
dataplot->GetXaxis()->SetTitle("No. of Iterations");
dataplot->GetXaxis()->CenterTitle();
dataplot->GetXaxis()->SetTitleSize(0.04);
dataplot->GetXaxis()->SetLabelSize(0.05);
dataplot->GetYaxis()->SetTitle("#chi^2/ndf");
dataplot->GetYaxis()->CenterTitle();
dataplot->GetYaxis()->SetTitleSize(0.04);
dataplot->GetYaxis()->SetLabelSize(0.038);

dataplot->SetMarkerColor(2);
dataplot->SetMarkerStyle(21);

dataplot->Draw();

sprintf(name,"%s.eps",c1->GetName());
c1->SaveAs(name);
}

