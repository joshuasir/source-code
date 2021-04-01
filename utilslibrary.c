#include<stdio.h>

// quick sort
void qsort(int arr[],int L,int R){
	if(L<R){
		int piv=arr[R],k=L,temp;
		for(int i=L;i<=R;i++){
 			if(arr[i]<=piv){
 				temp=arr[k];
  				arr[k++]=arr[i];
  				arr[i]=temp;
			}
		}
 		qsort(arr,L,k-2);
 		qsort(arr,k,R);
	}
}

// mergesort
void merge(int arr[],int L,int R){
	int temp[R-L+1],M=(L+R)/2,k=0,i=L,j=M+1;
	
	while(i<=M&&j<=R){
		temp[k++]= (arr[i]<arr[j]) ? arr[i++]:arr[j++];
	}
	
	while(i<=M){
		temp[k++]=arr[i++];
	}
	
	for(int z=0;z<k;z++){
		arr[z+L]=temp[z];
	}
}
void msort(int arr[],int L,int R){
	if(L<R){
		int M=(L+R)/2;
		msort(arr,M+1,R); msort(arr,L,M); merge(arr,L,R);
	}
}


// sqrtof x division
float qsqrt(float num){
	long i;
	float x2,y;
	x2 = num * 0.5F;
	y = num;
	
	memcpy(&i,&y,sizeof(long)); // convert float jadi long
	// untuk i IEEE 754 dari suatu angka adalah logaritma dari angka itu sendiri
	i= 0x5f3759df - (i >> 1); // 0x5f3759df constanta penggeser logarithm
	
	memcpy(&y,&i,sizeof(float)); // kembali ke float
	
	y=y*(1.5F-(x2*y*y)); //newton raphson iteration cukup sekali sudah sangat mendekati
	//y=y*(1.5F-(x2*y*y));
	
	return y;
}

// random number
uint randi(int key){
	key = (key << 13) ^ key;
	return ((key * (key * key * 15731 + 789221) + 1376312589) & 0x7fffffff);
}

// hashing algorithm
unsigned long djb2(unsigned char *str){
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}


// graph adjency list
int max(int a,int b){
	return (a>b)? a:b;
}

int visited[100005];
struct child{
	int cost,self;
	child *next;
};
struct parent{
	int path;
	child *head,*tail;
};

parent nodes[100005];
void createChild(int a,int b,int c){
	child *toAdd = (child *)malloc(sizeof *toAdd);
	toAdd->next = NULL;
	toAdd->cost = c;
	toAdd->self = b;
	if(nodes[a].head){
		nodes[a].tail->next = toAdd;
		nodes[a].tail = toAdd;
	}else{
		nodes[a].head = nodes[a].tail= toAdd;
	}
}
void traverse(int start){
	child *curr = nodes[start].head,*del;
	while(curr){
		if(!visited[curr->self]){
			nodes[curr->self].path = max(nodes[curr->self].path,nodes[start].path+curr->cost);
			visited[start] += 1;
			traverse(curr->self);
		}
		del = curr;
		curr = curr->next;
		del->next=NULL;
		free(del);
		del = NULL;
	}
	nodes[start].head = nodes[start].tail = NULL;
}


// disjoint sets
struct node{
	int parent;
	int size;
};

node sets[SIZE];

void makeSet(int n){
	sets[n].parent=n;
	sets[n].size=1;
}
void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}
int findParent(int a){
	if(sets[a].parent!=a){
		return sets[a].parent=findParent(sets[a].parent);
	}
	return a;
}
void mergeSet(int a,int b){
	a=findParent(a),b=findParent(b);
	if(a!=b){
		if(sets[a].size<sets[b].size){
			swap(&a,&b);
		}
		sets[b].parent=sets[a].parent;
		sets[a].size+=sets[b].size;
	}
	
}



//struct node{
//	int num,height;
//	node *left,*right;
//};
// AVL tree
int max(int a,int b){
	return (a>b) ? a : b;
}
int getHeight(node *curr){
	return (curr)?curr->height:0;
}
int getNewHeight(node *curr){
	return max(getHeight(curr->left),getHeight(curr->right))+1;
}
int getBalance(node *curr){
	return (curr) ? getHeight(curr->left)-getHeight(curr->right):0;
}
node* rotation(node *curr,const char *flag){
	node *y,*z;
	if(curr){
	if(!strcmp(flag,"left")){
		y=curr->right;
		z=y->left;
		y->left=curr;
		curr->right=z;
	}else{
		y=curr->left;
		z=y->right;
		y->right=curr;
		curr->left=z;
	}}
	curr->height=getNewHeight(curr);
	y->height=getNewHeight(y);
	return y;
}
node *AVL(node *curr){
	int currBalance=getBalance(curr),leftBalance=getBalance(curr->left),rightBalance=getBalance(curr->right);
	if(currBalance>1&&leftBalance>=0){
		return rotation(curr,"right");
	}else if(currBalance<-1&&rightBalance<=0){
		return rotation(curr,"left");
	}else if(currBalance>1){
		curr->left=rotation(curr->left,"left");
		return rotation(curr,"right");
	}else if(currBalance<-1){
		curr->right=rotation(curr->right,"right");
		return rotation(curr,"left");
	}
	return curr;
	
}
node *createNode(int num){
	node *toAdd=(node *)malloc(sizeof(node));
	toAdd->num=num;
	toAdd->left=toAdd->right=NULL;
	toAdd->height=1;
	return toAdd;
}
node *pushNode(int num,node *curr){
	if(!curr){
		return createNode(num);
	}
	
	if(curr->num>num){
		curr->left=pushNode(num,curr->left);
	}else if(curr->num<num){
		curr->right=pushNode(num,curr->right);		
	}
	curr->height=getNewHeight(curr);
	return AVL(curr);
}
node *deleteNode(int num,node *curr){
	if(!curr){
		return NULL;
	}
	
	if(num>curr->num){
		curr->right=deleteNode(num,curr->right);
	}else if(num<curr->num){
		curr->left=deleteNode(num,curr->left);
	}else{
		node *temp=NULL;
		if(!curr->left){
			temp=curr->right;
			free(curr);
			curr=NULL;
			return temp;
		}else if(!curr->right){
			temp=curr->left;
			free(curr);
			curr=NULL;
			return temp;
		}
		
			node *trav=curr->left;
			while(trav->right){
				trav=trav->right;
			}
			curr->num=trav->num;
			curr->left=deleteNode(trav->num,curr->left);
	}
	curr->height=getNewHeight(curr);
	return AVL(curr);
}

// max-heap
int size = 0;

int getParent(int maxHeap[], int i) {
    if (size == 0 || size == 1) {

    }
    else {
        return maxHeap[(i - 1) / 2];
    }
}

void heapify(int maxHeap[], int i) {
    if (i == 0) {
        return;
    }
    else {
        int parent = getParent(maxHeap, i);
        if (maxHeap[i] > parent) {
            swap(&maxHeap[i], &maxHeap[(i - 1) / 2]);
            heapify(maxHeap, (i - 1) / 2);
        }
    }
}

void insertHeap(int maxHeap[], int key) {
    maxHeap[size++] = key;

    if (size > 1) {
        heapify(maxHeap, size - 1);
    }
}


// library of Joshua Sirusstara