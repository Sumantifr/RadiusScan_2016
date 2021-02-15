#include <iostream>
#include <TRandom3.h>

void MikkoUnc(){

 if (true) {
     cout << "Creating a shuffled list of jackknife removals based on AK5"
          << endl;
     vector<int> _jkmore;
     int *_outlist = new int[ 100000000 ];
     int count[10] = {0};
     // Modification pre-CWR, Sep 27, 2013
     // Randomly remove event from one of the histograms that was not
     // yet left out in the latest cycle (these are tracked in jkmore)
     // ...but how to make sure same event is removed from AK5 and AK7?
     // => Create list here at the beginning together with ak5entry mappin
     TRandom3 *rnd = new TRandom3();
     Long64_t nentries5 = 37624515;//(fChain2 ? fChain2->GetEntriesFast()
                          // : fChain->GetEntriesFast());
     for (Long64_t jentry5=0; jentry5<nentries5; jentry5++) {

       int n = 10;
       if (_jkmore.size()==0) { // if jkmore is empty, reset it first
         for (int ijk = 0; ijk != n; ++ijk) _jkmore.push_back(ijk);
       }
       int m = _jkmore.size(); assert(m!=0);
       int mout = rnd->Integer(m);
//       cout<<"mout "<<mout<<endl;
       
       int iout = _jkmore[mout];
       _outlist[jentry5] = iout;
       _jkmore.erase(_jkmore.begin()+mout);
       if (jentry5<300) {
         cout << " " << iout;
         if (jentry5%10==9) cout << ",  ";
         if (jentry5%20==19) cout << endl;
       }
     }
    cout << endl;
    
    for (Long64_t jentry5=0; jentry5<nentries5; jentry5++) {
		if(_outlist[jentry5]<10){
		count[_outlist[jentry5]] += 1;
	   }  
	}
    
    int sum = 0;
    for(int ic=0; ic<10; ic++){
		cout<<count[ic]<<endl;
		sum += count[ic];
		}
		cout<<sum<<endl;
		delete _outlist;
   } // _ak5ak7  
}
