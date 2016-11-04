#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <iostream>
#include <sys/time.h>
#include <fstream>


#include "kklog.h"

using namespace cv;
using namespace std;

int main(){
	
	fstream in; 
	in.open("/home/ply/out.ply",ios::in);
//	in.open("out.ply",ios::in);

	if(!in){
		cout << "open file error " <<endl;
		return 0 ;
	}
	string filein;
	int vertexNum=1378;
//	Mat points(2377, 3, CV_64FC1,Scalar(0) );	
	Mat points(vertexNum, 3, CV_64FC1,Scalar(1) );
	int k = 0;
	double sum1,sum2,sum3;
	
	while(!in.eof() && !k ){
		in>>filein;
		LOGKP("filein:"<<filein);

		if(filein=="ply"||filein=="PLY")  
        	{   
        	    LOGKP("filein:"<<filein);
	        }else if(filein=="comment")  
	        {  
	            getline(in,filein,'\n');  
	        }else if(filein=="format")  
	        {   
	            getline(in,filein,'\n');  
	        }
		else if(filein=="element")  
	        { 
		    in>>filein;  
	            if(filein=="vertex")  
	            {   
	                in>>vertexNum;  
			LOGKP("vertexNum:"<<vertexNum);
	            }	            				
		}else if(filein=="end_header"){
							
			for(int i=0;i<vertexNum;i++) 
			
		        {  
		        	double f1,f2,f3;
				
				in>>f1>>f2>>f3;
				
//				cout<< "f1:"<<f1<<" "<<f2<<" "<<f3<<endl;
				sum1 += f1;
				sum2 += f2;
				sum3 += f3;
				
				Mat t = (Mat_<double>(1,3)<< f1,f2,f3);							
				if( f1!= 0 ||f2!= 0 ||f3!= 0 ) {
					points.at<double>(i, 0) = f1;
					points.at<double>(i, 1) = f2;
					points.at<double>(i, 2) = f3;	
				}			
			}
			k = 1;
			
			
		}

	}
//	cout << "points = " << points << "\n";
	
	in.close();
	double mean_x =  sum1/vertexNum;
	double mean_y =  sum2/vertexNum;
	double mean_z =  sum3/vertexNum;

	Mat mean_points(vertexNum, 3, CV_64FC1,Scalar(0) );

	for(int i=0;i<vertexNum;i++) 			
        {       														
			mean_points.at<double>(i, 0) = 21.8722;
			mean_points.at<double>(i, 1) =18.8528;
			mean_points.at<double>(i, 2) = 268.453;	
	}			
	
//	cout << "mean_points = " << mean_points << "\n";

	points = points - mean_points ;
	cout << "points = " << points << "\n";


	SVD svd(points.t());
	   	
	Mat U(svd.u);
	Mat W(svd.w); 
	Mat V(svd.vt);
		
	cout << "U= " << U << "\n"<<endl;
	cout << "W= " << W << "\n"<< endl;
	cout << "V= " << V.t() << "\n"<< endl;


//	double va[] = {-0.52486312,0.01997359,0.85095239};  
//	double vb[] = {-0.01153201,-0.99979979,0.01635438}; 

//	double va[] = {0.132205,-0.5055,0.8526};  
//	double vb[] = {0.96879,0.2479,-0.0033};  


	double va[] = {0.132205,0.96879,-0.2097};  
	double vb[] = {-0.5055,0.2479,0.8265};  

	double vc[3];  

	CvMat Va=cvMat(3, 1, CV_64FC1, va);  
	CvMat Vb=cvMat(3, 1, CV_64FC1, vb);  
	CvMat Vc=cvMat(3, 1, CV_64FC1, vc);  
	
	cvCrossProduct(&Va, &Vb, &Vc);    
	

	
	cout <<"normal:"<<CV_MAT_ELEM(Vc,double,0,0)<< "\n"<<endl;
	cout <<"normal:"<<CV_MAT_ELEM(Vc,double,1,0)<< "\n"<<endl;
	cout<<"normal:" <<CV_MAT_ELEM(Vc,double,2,0)<< "\n"<<endl;

	return 0;


}



