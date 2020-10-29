#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int participant=0;
int bankrupt=0;
int dead[5]={};
int lead[5];
int winner=0;
char grid[200][200];
typedef struct places{
	int rent;
	int festrent;
	char name[20];
	char stats;
	int owner;
};
places block[29];
typedef struct players{
	char name[8];
	int score;
	int money;
	int asset;
	int loc;
	char sign;
	int tag;
	int festive;
	int travel;
	int angel;
};
typedef struct list{
	players info[7];
};
list lists;
typedef struct Winplayers{
	char Winname[8];
	int Winscore;
};
typedef struct Winlist{
	Winplayers Wininfo[100];
};
Winlist Winlists;
void menu(){
	printf("                      _                        _           _ _   _   __ ___\n                     (_)                      (_)         | (_) | | / // _ \\\n _ __ ___   __ _ _ __ _   _ __ ___   ___ _ __  _  __ _  __| |_  | |/ // /_\\ \\_   _  __ _\n| '_ ` _ \\ / _` | '__| | | '_ ` _ \\ / _ \\ '_ \\| |/ _` |/ _` | | |    \\|  _  | | | |/ _` |\n| | | | | | (_| | |  | | | | | | | |  __/ | | | | (_| | (_| | | | |\\  \\ | | | |_| | (_| |\n|_| |_| |_|\\__,_|_|  |_| |_| |_| |_|\\___|_| |_| |\\__,_|\\__,_|_| \\_| \\_|_| |_/\\__, |\\__,_|\n                                             _/ |                             __/ |\n                                            |__/                             |___/            \n");
	printf("1. Play\n2. See all the winner\n3. Basic Information\n4. Exit\n>>");
	}
void info(){
	char str[]={"About this game :"};
	for(int i=0;str[i]!='\0';i++){
		printf("%c",str[i]);
		usleep(100000);
	}puts("");
	printf("1. 1000 K money will be given out to all player at the first round.\n2. Whenever you land on a block that no one owns, you can buy island on that block. Once you own the block, other players must pay rent if they landed on your island.\n3. If you land on a Chance Card, you will get the chance to get an angel card-\n4. When you pass Go, you will receive 200 K money from the bank.\n5. Bankruptcy. You are automatically lose if you can't pay the rent.\n6. If one player go bankrupt, the game is done\n7. The winner will be determinated from the leaderboard.\nEnjoy and have fun :)\n");
}
void winners(int a){
	printf("List Winner!\n=================\n\n");
	for(int i=0;i<a;i++){
		printf("%d. %s %d K\n",i+1,Winlists.Wininfo[i].Winname,Winlists.Wininfo[i].Winscore);
	}
}
int pick(){
	int many;
	for(;;){
	printf("Choose how many player to participate in the game [2-4]: ");
	scanf("%d",&many);
	getchar();
	if(many<2||many>4){
		system("CLS");
		continue;
	}else{
		break;
	}}
	for(int i=0;i<many;i++){
		printf("Input player %d name [ must be 3 or 8 characters ]: ",i+1);
		scanf("%s",lists.info[i].name);
		//printf("%s",lists.info[0].name);
		getchar();
		int len=strlen(lists.info[i].name);
		if(len<3||len>8){
			i--;
		}else{
			lists.info[i].score=1000;
			lists.info[i].money=1000;
			lists.info[i].asset=0;
			lists.info[i].loc=0;
			lists.info[i].name[len]='\0';
		}
	}
	printf("This game will be started...\n");
	getchar();
	return many;
}
void secmenu(int secloc,int secpla){
	for(int i=0;i<41;i++){
	printf("%s",&grid[i][0]);
	printf("        ");
	if(i==0){
	printf("LeaderBoard");
	}else if(i==1){
		printf("=============");
	}else if(i==2){
		printf("-------------------------");
	}else if(i-3<participant&&i-3>=0){
		printf("%d. %s P%d %d K ( %d K + %d K )",i-2,lists.info[lead[i-3]].name,lists.info[lead[i-3]].sign-34,lists.info[lead[i-3]].score,lists.info[lead[i-3]].money,lists.info[lead[i-3]].asset);
	}else if(i-3==participant){
		printf("-------------------------");
	}else if(i-3>participant&&i-3-participant==1){
		printf("Block information");
	}else if(i-3>participant&&i-3-participant==2){
		printf("=============");
	}else if(i-3>participant&&i-3-participant==3){
		printf("-------------------------");
	}else if(i-3>participant&&i-3-participant<8){
		if(i-3>participant&&i-3-participant==4){
		printf("Island Name :");}
		if(i-3>participant&&i-3-participant==5){
		printf("%s",block[secloc].name);}
		if(i-3>participant&&i-3-participant==6&&block[secloc].stats=='i'){
			if(block[secloc].owner==-1){
		printf("Fee : %d K",block[secloc].rent);}else{
			printf("Rent : %d K",(3*block[secloc].festrent)/2);
		}
		}if(i-3>participant&&i-3-participant==7){
		printf("Status : ");
		if(block[secloc].stats=='c'){
			if(secloc==0){
				printf("You got 200k from the bank~");
			}else if(secloc==7){
				printf("Wait your turn criminal!");
			}else if(secloc==14){
				printf("Choose an island to be doubled");
			}else if(secloc==21){
				printf("Mr. WorldWide");
			}
			
		}else if(block[secloc].stats=='i'){
			if(block[secloc].rent==block[secloc].festrent){
				printf("Normal");
			}else{
				printf("Price %dX",block[secloc].festrent/block[secloc].rent);
			}
			
		}else{
			if(secloc==8||secloc==16){
			printf("20%% chance to get an angel card!");
		}else if(secloc==26){
			printf("20%% TAX!");
		}}
	}}else if(i-3>participant&&i-3-2*participant==8){
		printf("-------------------------");
	}else if(i-3>participant&&i-3-2*participant==9){
		printf("Current Player");
	}else if(i-3>participant&&i-3-2*participant==10){
		printf("-------------------------");
	}else if(i-3>participant&&i-3-2*participant<14){
		if(i-3>participant&&i-3-2*participant==11){
		printf("%s (%c) P%d",lists.info[secpla].name,lists.info[secpla].sign,secpla+1);}
		if(i-3>participant&&i-3-2*participant==12){
		printf("Money: %d",lists.info[secpla].money);}
		if(i-3>participant&&i-3-2*participant==13){
		printf("Total: %d",lists.info[secpla].score);}
	}else if(i-3>participant&&i-3-2*participant==14){
		printf("=============");
	}else if(i-3>participant&&i-3-2*participant==15){
		printf("-------------------------");
	}
	puts("");
}}
void clearloc(int prevloc){
	if(lists.info[prevloc-35].loc==0){
		grid[37][prevloc-30]=' ';
	}else if(lists.info[prevloc-35].loc==1){
		grid[32][prevloc-30]=' ';		
	}else if(lists.info[prevloc-35].loc==2){
		grid[28][prevloc-30]=' ';		
	}else if(lists.info[prevloc-35].loc==3){
		grid[23][prevloc-30]=' ';		
	}else if(lists.info[prevloc-35].loc==4){
		grid[17][prevloc-30]=' ';		
	}else if(lists.info[prevloc-35].loc==5){
		grid[12][prevloc-30]=' ';		
	}else if(lists.info[prevloc-35].loc==6){
		grid[7][prevloc-30]=' ';		
	}else if(lists.info[prevloc-35].loc==7){
		grid[2][prevloc-28]=' ';		
	}else if(lists.info[prevloc-35].loc==8){
		grid[2][prevloc-13]=' ';		
	}else if(lists.info[prevloc-35].loc==9){
		grid[2][prevloc+2]=' ';		
	}else if(lists.info[prevloc-35].loc==10){
		grid[2][prevloc+15]=' ';		
	}else if(lists.info[prevloc-35].loc==11){
		grid[2][prevloc+30]=' ';		
	}else if(lists.info[prevloc-35].loc==12){
		grid[2][prevloc+43]=' ';		
	}else if(lists.info[prevloc-35].loc==13){
		grid[2][prevloc+58]=' ';		
	}else if(lists.info[prevloc-35].loc==14){
		grid[2][prevloc+72]=' ';
				
	}else if(lists.info[prevloc-35].loc==15){
		grid[7][prevloc+72]=' ';		
	}else if(lists.info[prevloc-35].loc==16){
		grid[12][prevloc+72]=' ';		
	}else if(lists.info[prevloc-35].loc==17){
		grid[17][prevloc+72]=' ';		
	}else if(lists.info[prevloc-35].loc==18){
		grid[23][prevloc+72]=' ';		
	}else if(lists.info[prevloc-35].loc==19){
		grid[28][prevloc+72]=' ';		
	}else if(lists.info[prevloc-35].loc==20){
		grid[32][prevloc+72]=' ';		
	}else if(lists.info[prevloc-35].loc==21){
		grid[37][prevloc+72]=' ';		
		
	}else if(lists.info[prevloc-35].loc==22){
		grid[37][prevloc+58]=' ';		
	}else if(lists.info[prevloc-35].loc==23){
		grid[37][prevloc+43]=' ';		
	}else if(lists.info[prevloc-35].loc==24){
		grid[37][prevloc+30]=' ';		
	}else if(lists.info[prevloc-35].loc==25){
		grid[37][prevloc+13]=' ';		
	}else if(lists.info[prevloc-35].loc==26){
		grid[37][prevloc+2]=' ';		
	}else if(lists.info[prevloc-35].loc==27){
		grid[37][prevloc-13]=' ';		
	}
}

void putloc(int nextloc){
	if(lists.info[nextloc-35].loc==0){
		grid[37][nextloc-30]=nextloc;
	}else if(lists.info[nextloc-35].loc==1){
		grid[32][nextloc-30]=nextloc;		
	}else if(lists.info[nextloc-35].loc==2){
		grid[28][nextloc-30]=nextloc;		
	}else if(lists.info[nextloc-35].loc==3){
		grid[23][nextloc-30]=nextloc;		
	}else if(lists.info[nextloc-35].loc==4){
		grid[17][nextloc-30]=nextloc;		
	}else if(lists.info[nextloc-35].loc==5){
		grid[12][nextloc-30]=nextloc;		
	}else if(lists.info[nextloc-35].loc==6){
		grid[7][nextloc-30]=nextloc;		
	}else if(lists.info[nextloc-35].loc==7){
		grid[2][nextloc-28]=nextloc;		
	}else if(lists.info[nextloc-35].loc==8){
		grid[2][nextloc-13]=nextloc;		
	}else if(lists.info[nextloc-35].loc==9){
		grid[2][nextloc+2]=nextloc;		
	}else if(lists.info[nextloc-35].loc==10){
		grid[2][nextloc+15]=nextloc;		
	}else if(lists.info[nextloc-35].loc==11){
		grid[2][nextloc+30]=nextloc;		
	}else if(lists.info[nextloc-35].loc==12){
		grid[2][nextloc+43]=nextloc;		
	}else if(lists.info[nextloc-35].loc==13){
		grid[2][nextloc+58]=nextloc;		
	}else if(lists.info[nextloc-35].loc==14){
		grid[2][nextloc+72]=nextloc;
				
	}else if(lists.info[nextloc-35].loc==15){
		grid[7][nextloc+72]=nextloc;		
	}else if(lists.info[nextloc-35].loc==16){
		grid[12][nextloc+72]=nextloc;		
	}else if(lists.info[nextloc-35].loc==17){
		grid[17][nextloc+72]=nextloc;		
	}else if(lists.info[nextloc-35].loc==18){
		grid[23][nextloc+72]=nextloc;		
	}else if(lists.info[nextloc-35].loc==19){
		grid[28][nextloc+72]=nextloc;		
	}else if(lists.info[nextloc-35].loc==20){
		grid[32][nextloc+72]=nextloc;		
	}else if(lists.info[nextloc-35].loc==21){
		grid[37][nextloc+72]=nextloc;		
		
	}else if(lists.info[nextloc-35].loc==22){
		grid[37][nextloc+58]=nextloc;		
	}else if(lists.info[nextloc-35].loc==23){
		grid[37][nextloc+43]=nextloc;		
	}else if(lists.info[nextloc-35].loc==24){
		grid[37][nextloc+30]=nextloc;		
	}else if(lists.info[nextloc-35].loc==25){
		grid[37][nextloc+13]=nextloc;		
	}else if(lists.info[nextloc-35].loc==26){
		grid[37][nextloc+2]=nextloc;		
	}else if(lists.info[nextloc-35].loc==27){
		grid[37][nextloc-13]=nextloc;		
	}

}
void puthouse(int build,int sign){

if(build==9){
		grid[1][30]='P';
		grid[1][31]='1'+sign;
	}else if(build==10){
		grid[1][45]='P';
		grid[1][46]='1'+sign;
	}else if(build==11){
		grid[1][61]='P';
		grid[1][62]='1'+sign;
	}else if(build==12){
		grid[1][77]='P';
		grid[1][78]='1'+sign;
	}else if(build==13){
		grid[1][93]='P';
		grid[1][94]='1'+sign;
	}else if(build==6){
		grid[6][2]='P';
		grid[6][3]='1'+sign;
	}else if(build==15){
		grid[6][101]='P';
		grid[6][102]='1'+sign;
	}else if(build==5){
		grid[11][2]='P';
		grid[11][3]='1'+sign;
	}else if(build==4){
		grid[16][2]='P';
		grid[16][3]='1'+sign;
	}else if(build==17){
		grid[16][101]='P';
		grid[16][102]='1'+sign;
	}else if(build==3){
		grid[21][2]='P';
		grid[21][3]='1'+sign;
	}else if(build==18){
		grid[21][101]='P';
		grid[21][102]='1'+sign;
	}else if(build==19){
		grid[26][99]='P';
		grid[26][100]='1'+sign;
	}else if(build==1){
		grid[31][2]='P';
		grid[31][3]='1'+sign;
	}else if(build==20){
		grid[31][101]='P';
		grid[31][102]='1'+sign;
	}else if(build==27){
		grid[36][15]='P';
		grid[36][16]='1'+sign;
	}else if(build==25){
		grid[36][45]='P';
		grid[36][46]='1'+sign;
	}else if(build==24){
		grid[36][61]='P';
		grid[36][62]='1'+sign;
	}else if(build==23){
		grid[36][77]='P';
		grid[36][78]='1'+sign;
	}else if(build==22){
		grid[36][93]='P';
		grid[36][94]='1'+sign;
	}
	
}
void clearhouse(int broke){
	if(broke==9){
		grid[1][30]=' ';
		grid[1][31]=' ';
	}else if(broke==10){
		grid[1][45]=' ';
		grid[1][46]=' ';
	}else if(broke==11){
		grid[1][61]=' ';
		grid[1][62]=' ';
	}else if(broke==12){
		grid[1][77]=' ';
		grid[1][78]=' ';
	}else if(broke==13){
		grid[1][93]=' ';
		grid[1][94]=' ';
	}else if(broke==6){
		grid[6][2]=' ';
		grid[6][3]=' ';
	}else if(broke==15){
		grid[6][101]=' ';
		grid[6][102]=' ';
	}else if(broke==5){
		grid[11][2]=' ';
		grid[11][3]=' ';
	}else if(broke==4){
		grid[16][2]=' ';
		grid[16][3]=' ';
	}else if(broke==17){
		grid[16][101]=' ';
		grid[16][102]=' ';
	}else if(broke==3){
		grid[21][2]=' ';
		grid[21][3]=' ';
	}else if(broke==18){
		grid[21][101]=' ';
		grid[21][102]=' ';
	}else if(broke==19){
		grid[26][99]=' ';
		grid[26][100]=' ';
	}else if(broke==1){
		grid[31][2]=' ';
		grid[31][3]=' ';
	}else if(broke==20){
		grid[31][101]=' ';
		grid[31][102]=' ';
	}else if(broke==27){
		grid[36][15]=' ';
		grid[36][16]=' ';
	}else if(broke==25){
		grid[36][45]=' ';
		grid[36][46]=' ';
	}else if(broke==24){
		grid[36][61]=' ';
		grid[36][62]=' ';
	}else if(broke==23){
		grid[36][77]=' ';
		grid[36][78]=' ';
	}else if(broke==22){
		grid[36][93]=' ';
		grid[36][94]=' ';
	}
}
void corner(int keyc){
	if(lists.info[keyc].loc==0){
		lists.info[keyc].score+=200;
		lists.info[keyc].money+=200;
	}else if(lists.info[keyc].loc==7){
		lists.info[keyc].tag=1;
	}else if(lists.info[keyc].loc==14){
		lists.info[keyc].festive=1;
		printf("Pick an island any island!\n");
		int festland;
		for(int i=0;i<28;i++){
			if(block[i].owner==keyc){
				if(block[i].festrent*2<=block[i].rent*8){
				printf("%d. %s | Rent Price %d -> %d",i,block[i].name,(3*block[i].festrent)/2,block[i].festrent*3);
			}else{
				printf("%d. %s | Rent Price %d -> %d",i,block[i].name,(3*block[i].festrent)/2,(3*block[i].festrent)/2);
			}
			puts("");
			}
		}
		printf("0. Cancel\n");
		for(;;){
		scanf("%d",&festland);
		getchar();
		if(block[festland].owner!=keyc||festland==0){
			if(festland==0){
				break;
			}
			printf("Pick your island!\n");
			continue;
		}else{
			if(block[festland].festrent*2<=block[festland].rent*8||festland==0){
			block[festland].festrent*=2;
			printf("Yay! The chosen block rent price has been doubled!\n");
			getchar();
			break;}
		}
		}
		
	}else{
		lists.info[keyc].travel=1;
	}
}
void extra(int keye){
	if(lists.info[keye].loc==8||lists.info[keye].loc==16){
		int cc=rand()%100;
		if(cc>0&&cc<=20){
			lists.info[keye].angel=1;
			printf("Congratulation~ You got an angel card! (^ V ^)/ ");
			getchar();
		}
	}else if(lists.info[keye].loc==26){
		int tax=(lists.info[keye].score*2)/10;
		lists.info[keye].money-=tax;
	}
}
void island(int keyi){
	if(lists.info[keyi].money>=block[lists.info[keyi].loc].rent&&block[lists.info[keyi].loc].owner==-1){
		printf("Do you want to buy the island Y / N ?");
		char ans=getchar();
		getchar();
		if(ans=='Y'){
			lists.info[keyi].money-=block[lists.info[keyi].loc].rent;
			lists.info[keyi].asset+=block[lists.info[keyi].loc].rent;
			block[lists.info[keyi].loc].owner=keyi;
			puthouse(lists.info[keyi].loc,keyi);
		}
	}
}
void winnerwinner(){
	int k=0;
	while(lead[k]==-1){
		k++;
	}
	lead[0]=lead[k];
			strcpy(Winlists.Wininfo[winner].Winname,lists.info[lead[0]].name);
			int len=strlen(Winlists.Wininfo[winner].Winname);
			Winlists.Wininfo[winner].Winname[len]='\0';
			Winlists.Wininfo[winner].Winscore=lists.info[lead[0]].score;
			winner++;
	FILE *fp;
	fp=fopen("winnerlist.txt","w");
	for(int i=0;i<winner;i++){
		fprintf(fp,"%s %d\n",Winlists.Wininfo[i].Winname,Winlists.Wininfo[i].Winscore);
}
	fclose(fp);
	printf("\n%s win the game! ~ Congratulation\n\n",lists.info[lead[0]].name);
	printf("List Assests :\n");
	for(int i=0;i<29;i++){
		if(block[i].owner==lead[0]){
			printf("%d. %s %d\n",i,block[i].name,block[i].rent);
			
		}}
		printf("Total Assets : %d\n",lists.info[lead[0]].asset);
		printf("Money : %d\n",lists.info[lead[0]].money);
		printf("Total : %d\nPress any key to back to main menu...",lists.info[lead[0]].score);
}
void start(){
	int round=0;
	for(int i=0;i<participant;i++){
		lead[i]=i;
	}
	for(int i=35;i<35+participant;i++){
		grid[37][i-30]=i;
		lists.info[i-35].sign=i;
		lead[i-35]=i-35;
	}
	for(int i=35;;i++){
		round++;
		for(int k=participant-1;k>=0;k--){
			for(int l=1;l<=k;l++){
			if(lists.info[lead[l]].score>lists.info[lead[l-1]].score){
				lead[l]+=lead[l-1];
				lead[l-1]=lead[l]-lead[l-1];
				lead[l]=lead[l]-lead[l-1];
			}
		}	
		}
		for(int j=0;j<5;j++){
			if(dead[j]){
				printf("Player %d is bankrupt. The game will be ended",j+1);
				getchar();
				dead[j]=0;
				bankrupt=1;
				for(int i=0;i<5;i++){
					if(lead[i]==j){
						lead[i]=-1;
					}}
				break;
			}
		}
		if(bankrupt){
			bankrupt=0;
			break;
		}
		if(i>=35+participant){i=35;	}
		system("CLS");
		
		secmenu(lists.info[i-35].loc,i-35);
		if(lists.info[i-35].tag==1){
			lists.info[i-35].tag=0;
			printf("1 more turn and you can go out from jail...\nPRESS ENTER CRIMINAL!");
			getchar();
			continue;
		}
		if(lists.info[i-35].travel==1){
		for(;;){
			int num;
		printf("Please enter a location...");
		scanf("%d",&num);
		getchar();
		if(num==lists.info[i-35].loc){
			printf("Can't do that\n");
		}else{
			clearloc(i);
			lists.info[i-35].loc=num;
			putloc(i);
			lists.info[i-35].travel=0;
			break;
		}}
		}else{
		printf("Press enter to roll the dice or Q to give up...");
		char q=getchar();
		if(q=='Q'){
			if(round/participant>=3){
				lead[i-35]=-1;
				printf("Player %d gave up",i-34);
				getchar();
			break;}else{
				printf("Keep playing you coward!\ncan't give up on 1~2 round");
				getchar();
				getchar();
				i--;
				continue;
			}
		}else{
			clearloc(i);
			int steps=rand()%6;
			if(steps){
			lists.info[i-35].loc+=steps;
			printf("You got %d!\n",steps);
			getchar();
			}else{
				lists.info[i-35].loc+=6;
				printf("You got 6!\n");
				getchar();
			}
			lists.info[i-35].loc%=28;
			putloc(i);}
			system("CLS");
			
			secmenu(lists.info[i-35].loc,i-35);
			if(block[lists.info[i-35].loc].stats=='c'){
				corner(i-35);
			}else if(block[lists.info[i-35].loc].stats=='e'){
				extra(i-35);
			}else{
				if(block[lists.info[i-35].loc].owner!=-1&&block[lists.info[i-35].loc].owner!=i-35){
					char card='N';
					if(lists.info[i-35].angel){
						printf("Use Angel Card Y/N ?");
						card=getchar();
						getchar();
						if(card=='Y'){
							lists.info[i-35].angel=0;
						}}if(card=='N'||lists.info[i-35].angel==0){
							if(lists.info[i-35].money>=(3*block[lists.info[i-35].loc].festrent)/2){
								lists.info[i-35].money-=(3*block[lists.info[i-35].loc].festrent)/2;
								lists.info[i-35].score-=(3*block[lists.info[i-35].loc].festrent)/2;
								lists.info[block[lists.info[i-35].loc].owner].money+=(3*block[lists.info[i-35].loc].festrent)/2;
								lists.info[block[lists.info[i-35].loc].owner].score+=(3*block[lists.info[i-35].loc].festrent)/2;
								printf("Pay rent!\nRent: %d K\n\nPress any key to continue...",(3*block[lists.info[i-35].loc].festrent)/2);
								getchar();
								if(block[lists.info[i-35].loc].festrent>block[lists.info[i-35].loc].rent){
									lists.info[block[lists.info[i-35].loc].owner].festive=0;
								block[lists.info[i-35].loc].festrent=block[lists.info[i-35].loc].rent;}
							}else{
								for(;;){
								system("CLS");
								
								secmenu(lists.info[i-35].loc,i-35);
								printf("Your money isn't enough to pay rent!\n1. Sell Island\n2. Bankrupt\nChoose [ 1 | 2 ]:");
								int rupt;
								scanf("%d",&rupt);
								getchar();
								if(rupt==2){
									dead[i-35]=1;
									break;
								}else{
									printf("Choose island that you want to sell:\n");
									for(int j=0;j<28;j++){
										if(block[j].owner==i-35){
											printf("%d. %s - %d\n",j,block[j].name,block[j].festrent);}}
								printf("0. Back\n>>");
								int sell;
								scanf("%d",&sell);
								getchar();
								if(block[sell].owner==i-35){
									clearhouse(sell);
									block[sell].owner=-1;
									lists.info[i-35].asset-=block[sell].rent;
									lists.info[i-35].money+=block[sell].rent;
									
									if(lists.info[i-35].money>=(3*block[lists.info[i-35].loc].festrent)/2){
									lists.info[i-35].money-=(3*block[lists.info[i-35].loc].festrent)/2;
									lists.info[i-35].score-=(3*block[lists.info[i-35].loc].festrent)/2;
									lists.info[block[lists.info[i-35].loc].owner].money+=(3*block[lists.info[i-35].loc].festrent)/2;
									lists.info[block[lists.info[i-35].loc].owner].score+=(3*block[lists.info[i-35].loc].festrent)/2;
										if(block[lists.info[i-35].loc].festrent>block[lists.info[i-35].loc].rent){
									lists.info[block[lists.info[i-35].loc].owner].festive=0;
								block[lists.info[i-35].loc].festrent=block[lists.info[i-35].loc].rent;}
									break;}
									
								}}}}}}
				if(dead[i-35]==0){
				island(i-35);}}}}}
void initialize(){
	FILE* fp= fopen("block_information.txt","r");
	int dex=0;
	while(!feof(fp)){
		fscanf(fp,"%[^#]#%d#%c%*[^\n]\n",block[dex].name,&block[dex].rent,&block[dex].stats);
		block[dex].festrent=block[dex].rent;
		dex++;
	}
	fclose(fp);
	FILE* fmap= fopen("map.txt","r");
	dex=0;
	while(!feof(fmap)){
		fscanf(fmap,"%[^\n]\n",grid[dex]);
		dex++;
	}
	fclose(fmap);
	FILE* fwinner= fopen("winnerlist.txt","r");
	dex=0;
	while(!feof(fwinner)){
		fscanf(fwinner,"%s %d\n",Winlists.Wininfo[dex].Winname,&Winlists.Wininfo[dex].Winscore);
		dex++;
		winner++;
	}
	fclose(fwinner);
}
int main(){
	int pickmenu;
	for(;;){
	winner=0;
	initialize();
	//winner=0;
	int exit=0;
	menu();
	scanf("%d",&pickmenu);
	getchar();
	switch(pickmenu){
		case 1:
			for(int i=0;i<29;i++){
				block[i].owner=-1;
			}
			system("CLS");
			
			participant=pick();
			start();
			winnerwinner();
			break;
		case 2:
			system("CLS");
			
			winners(winner);
			break;
		case 3:
			system("CLS");
			
			info();
			break;
		default:
			exit=1;
			break;
	}
	if(exit){
		break;
	}
	getchar();
	system("CLS");
	
	}
	return 0;
}
