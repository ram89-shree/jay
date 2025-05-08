#include<iostream>
#include<omp.h>
using namespace std;
void BubbleSort(int arr[],int n){
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]){
				swap(arr[j],arr[j+1]);
			}
		}
	}
}

void pBubble(int arr[],int n){
	for(int i=0;i<n;i++){
		#pragma omp for
		for(int j=1;j<n;j+=2){
			if(arr[j]<arr[j-1]){
				swap(arr[j],arr[j-1]);
			}
		}
		
		#pragma omp barrrier
		
		//even phase
		
		#pragma omp for
		for(int j=2;j<n;j+=2){
			if(arr[j]<arr[j-1]){
				swap(arr[j],arr[j-1]);
			}
		}
		#pragma omp barrier
	}
}

void print(int arr[],int n){
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
int main(){
	int n=10;
	int arr[]={5,4,6,8,7,3,10,2,19};
	double start_time,end_time;
	
	for(int i=0,j=n;i<n;i++,j--){
		arr[i]=j;
	}
	
	start_time=omp_get_wtime();
	BubbleSort(arr,n);
	end_time=omp_get_wtime();
	cout<<"Sequential bubble sort took : "<<end_time-start_time<<" seconds \n";
	print(arr,n);
	
	for(int i=0,j=n;i<n;i++,j--){
		arr[i]=j;
	}
	
	start_time=omp_get_wtime();
	#pragma omp parallel
	{
		pBubble(arr,n);
	}
	end_time=omp_get_wtime();
	cout<<"Parallel bubble sort took : "<<end_time-start_time<<" seconds \n";
	print(arr,n);
}
