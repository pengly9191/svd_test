#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <iostream>
#include <core.h>
using namespace std;
int main() 
{ 



	SVD svd(covObjectPoints);
   	Mat R(svd.vt);
	Mat U(svd.u);
	Mat W(svd.w);
 	







  double a[5][5] = 
  {    
    {7,2,4,5,6},
    {3,4,5,8,2},
    {1,0,9,7,5},
    {0,5,3,2,1},
    {4,6,7,3,1}
  };

  CvMat va = cvMat(5,5, CV_64FC1,a);

  cout<<"目标矩阵："<<endl;

  for(int i=0;i<5;i++)
  {
    for(int j=0;j<5;j++)
      printf("%f\t",cvmGet(&va,i,j));
    cout << endl;
  }

  double b[5][5] = {0};

  CvMat vb = cvMat(5,5, CV_64FC1,b);

	for(int i=0;i<5;i++)
	  {
	    for(int j=0;j<5;j++)
	      printf("%f\t",cvmGet(&vb,i,j));
	    cout << endl;
	  }

  double c[5][5] = {0};

  CvMat vc = cvMat(5,5, CV_64FC1,c);

  double d[5][5] = {0};

  CvMat vd = cvMat(5,5, CV_64FC1,d);

  cvSVD(&va,&vb,&vc,&vd);


  cout<<"结果矩阵vb："<<endl;

  for(int i=0;i<5;i++)
  {
    for(int j=0;j<5;j++)
      printf("%f\t",cvmGet(&vb,i,j));
    cout << endl;
  }

  cout<<"结果矩阵vc："<<endl;

  for(int i=0;i<5;i++)
  {
    for(int j=0;j<5;j++)
      printf("%f\t",cvmGet(&vc,i,j));
    cout << endl;
  }

  cout<<"结果矩阵vd："<<endl;

  for(int i=0;i<5;i++)
  {
    for(int j=0;j<5;j++)
      printf("%f\t",cvmGet(&vd,i,j));
    cout << endl;
  }

  getchar();
  return 0;





}
