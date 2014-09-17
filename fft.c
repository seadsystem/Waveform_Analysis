//author Henry Crute
#include <stdio.h>
#include <math.h>

#define SWAP(a,b)tempr=(a);(a)=(b);(b)=tempr
//tempr is a variable from our FFT function

//data -> float array that represent the array of complex samples
//number_of_complex_samples -> number of samples (N^2 order number) 
//isign -> 1 to calculate FFT and -1 to calculate Reverse FFT
float FFT (float data[], unsigned long number_of_complex_samples, int isign)
{
   //variables for trigonometric recurrences
   unsigned long n,mmax,m,j,istep,i;
   double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;
   
   //the complex array is real+complex so the array 
   //as a size n = 2* number of complex samples
   // real part is the data[index] and 
   //the complex part is the data[index+1]
   n=number_of_complex_samples * 2; 
   //binary inversion (note that the indexes 
   //start from 0 witch means that the
   //real part of the complex is on the even-indexes 
   //and the complex part is on the odd-indexes
   j=0;
   for (i=0;i<n/2;i+=2) {
      if (j > i) {
         //swap the real part
         SWAP(data[j],data[i]);
         //swap the complex part
         SWAP(data[j+1],data[i+1]);
         // checks if the changes occurs in the first half
         // and use the mirrored effect on the second half
         if((j/2)<(n/4)){
            //swap the real part
            SWAP(data[(n-(i+2))],data[(n-(j+2))]);
            //swap the complex part
            SWAP(data[(n-(i+2))+1],data[(n-(j+2))+1]);
         }
      }
      m=n/2;
      while (m >= 2 && j >= m) {
         j -= m;
         m = m/2;
      }
      j += m;
   }
   
   //Danielson-Lanzcos routine 
   mmax=2;
   //external loop
   while (n > mmax)
   {
      istep = mmax<<  1;
      theta=isign*(2*PI/mmax);
      wtemp=sin(0.5*theta);
      wpr = -2.0*wtemp*wtemp;
      wpi=sin(theta);
      wr=1.0;
      wi=0.0;
      //internal loops
      for (m=1;m<mmax;m+=2) {
         for (i= m;i<=n;i+=istep) {
            j=i+mmax;
            tempr=wr*data[j-1]-wi*data[j];
            tempi=wr*data[j]+wi*data[j-1];
            data[j-1]=data[i-1]-tempr;
            data[j]=data[i]-tempi;
            data[i-1] += tempr;
            data[i] += tempi;
         }
         wr=(wtemp=wr)*wpr-wi*wpi+wr;
         wi=wi*wpr+wtemp*wpi+wi;
      }
      mmax=istep;
   }
   //end of the algorithm
	
	//determine the fundamental frequency
	//look for the maximum absolute value in the complex array
	fundamental_frequency=0;
	for(i=2; i<=sample_rate; i+=2)
	{
		if((pow(vector[i],2)+pow(vector[i+1],2))>(pow(vector[fundamental_frequency],2)+pow(vector[fundamental_frequency+1],2))){
			fundamental_frequency=i;
		}
	}

	//since the array of complex has the format [real][complex]=>[absolute value]
	//the maximum absolute value must be ajusted to half
	fundamental_frequency=(long)floor((float)fundamental_frequency/2);
   return fundamental_frequency;
}
   

int main(int argc, char *argv[]) {
   printf("hello world");
   return(0);
}
