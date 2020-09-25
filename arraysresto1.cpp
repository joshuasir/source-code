#include<stdio.h>

int main(){
	int t;
	scanf("%d",&t);
	getchar();
	while(t--){
	int n,x,y;
	scanf("%d %d %d",&n,&x,&y);
	getchar();
	int range=y-x,index;
	for(int i=1;i<=range;i++){
		if(range%i==0){
			if((range/i)<=n-1){
				index=i;
				break;
			}
		}
	
	}
	int ctr=0;
	for(int i=x;i<=y;i+=index){
		printf("%d ",i);
		ctr++;
		}
	//puts("");
	//printf("%d ",index);
	if(ctr<n){
		int j=x;
		while(ctr<n&&j>0){
			j-=index;
			if(ctr>=n||j<=0){
				break;
			}
			printf("%d ",j);
			ctr++;
		}
		j=y;
			while(ctr<n){
			if(ctr>=n||j<=0){
			break;
			}
			j+=index;
			printf("%d ",j);
			ctr++;
		}
		
	}
	puts("");
	}
}
