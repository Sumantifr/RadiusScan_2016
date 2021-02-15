#include<iostream>

//#include<windows.h>

//#include<conio.h>

#include<time.h>

void getSeconds(unsigned long *par);

int main()

{
	unsigned long sec;
       for(int ij=0; ij<10000; ij++){
	getSeconds(&sec);
	std::cout<<ij<<'\t';
	std::cout<<"Number of seconds:"<<sec<<"\n";
}
}

void getSeconds(unsigned long *par)

{

	*par=time(NULL);

}
