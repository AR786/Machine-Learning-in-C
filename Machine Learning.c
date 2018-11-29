#include "meanshift.h"
#include "KMEANS.h"
#include "DBSCAN.h"
#include "linear.h"
#include "KNN.h"


int main(){ int z,r;int b;int ky;int kx;int kk;
while(1)
{	
printf("choose the clustering algorithm you want to implement: \n 1.K Means Clustering \n 2.Mean Shift Clustering \n 3.K-Nearest Neighbors(KNN) \n 4.DBSCAN \n 5.Linear Regression \n 6.Exit \n			(Save you inpult file as data.txt)\n");
	scanf("%d",&z);
	switch(z){
		case 1: printf("Enter the number of clusters \n");
				scanf("%d",&r);
				kmeansc(r);
				break;
				
		case 2: printf("enter the radius");
				scanf("%d",&r);
				msc(r); break;
				
		case 3: 
				printf("Enter the number of clusters \n");
				scanf("%d",&r);
    
    			printf("enter the data points");
    			scanf("%d",&kx);
    			scanf("%d",&ky);
    			printf("enter value of k for knn");
    			scanf("%d",&kk);
				knnc(r,kx,ky,kk);
				 break;
				
				
		case 4: printf("enter the radius");
				scanf("%d",&r);
				dbscanc(r); break;
		
		case 5: 
     			 printf("enter bias\n");
    			scanf("%d",&b);
    			printf("enter x coordinate \n");
    			scanf("%d",&r);
    			linearc(b,r);
		
		case 6: exit(0);
	}
	}
	return 0;
	
}

