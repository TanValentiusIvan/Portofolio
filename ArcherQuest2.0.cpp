#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>

struct saves{
	char name[100];
	int level;
	int exp;
	int gold;
	int pHP;
	int pAtk;
	int armorLvl;
	int weaponLvl;
	int hpPotCount;
	int atkPotCount;
};

saves a[10];

// Menu
char text[100][100];
char move;
char secretCode[100];
char yn;
char name[100];
int cursor=1;
int expCheat = 0;
int n = 0;

// Save
char saveText[100][100];
int saveCursor;

// Lobby
int row = 10;
int column = 19;
int y = 7;
int x = 9;	
char map[100][100];

// Shop
int shopInput;
int amount;
char shopText[100][100];
int shopCursor=1;

// Upgrade
int upInput;
char upText[100][100];
int upCursor=1;

// Player
int armorLvl = 1;
int weaponLvl = 1;
int level = 1;
int exp = 0;
int gold = 100;
int pAtk = 10;
int pHP = 100;
int hitChance = 70;
int hpPotCount;
int atkPotCount;

// Enemy
int eAtk;
int eHP; 

// Combat
char batText[100][100];
int batCursor = 1;
char itemText[100][100];
int itemCursor= 1;

// LineCount
int c;
int count;

void menu();
void newGame();
void lobbyMap();
void lobby();
void shop();
void upgrade();
void inventory();
void eStats();
void combat();
void saveGame();

void lineCount(){
	FILE* fp = fopen("AQsave.txt", "r");
	if(fp == NULL){
		fclose(fp);
		fp = fopen("AQsave.txt", "w");
		fclose(fp);
		fp = fopen("AQsave.txt", "r");
	}
   	for (c = getc(fp); c != EOF; c = getc(fp)){
       	if (c == '\n'){
          		count = count + 1;
			}
	}
   	fclose(fp);	
}

int main(){	
	lineCount();
	if(count > 0){
		FILE* fp = fopen("AQsave.txt", "r");
		while(!feof(fp)){
			fscanf(fp, "%[^#]#%d#%d#%d#%d#%d#%d#%d#%d#%d\n", &a[n].name, &a[n].level, &a[n].exp, &a[n].gold, &a[n].pHP, &a[n].pAtk, &a[n].armorLvl, &a[n].weaponLvl, &a[n].hpPotCount, &a[n].atkPotCount);
			n++;
		}		
		fclose(fp);
	}
	menu();
	return 0;	
}

void menu(){
		system("cls");
		strcpy(text[1], " NEW GAME          <  ");
		strcpy(text[2], " LOAD GAME            ");
		strcpy(text[3], " CONTROLS             ");
		strcpy(text[4], " SECRET MENU          ");
		strcpy(text[5], " EXIT                 ");
		cursor = 1;
		
	while(true){
		system("cls");
		
		printf("--ARCHER QUEST--\n\n");
		for(int i=1;i<6;i++){
			printf("%s\n", text[i]);
		}
		
		move=getch();
		switch(move){
			case 'w':
				text[cursor][19]=' ';
				(cursor<=1)?cursor:cursor--;
				text[cursor][19]='<';
				break;

			case 's':
				text[cursor][19]=' ';
				(cursor>=5)?cursor:cursor++;
				text[cursor][19]='<';
				break;
			
			case ' ':
				if(cursor==1){
					newGame();
					lobby();
				}else if(cursor==2){
					system("cls");
					strcpy(saveText[1], "     <  ");
					strcpy(saveText[2], "        ");
					strcpy(saveText[3], "        ");
					strcpy(saveText[4], "        ");
					strcpy(saveText[5], "        ");
					strcpy(saveText[6], "        ");
					strcpy(saveText[7], "        ");
					strcpy(saveText[8], "        ");
					strcpy(saveText[9], "        ");
					strcpy(saveText[10],"        ");
					strcpy(saveText[11],"        ");														
					saveCursor = 1;
					
					while(true){
						system("cls");
						if(n<0){
							printf("No Save Data\n");
							printf("\nPress [ENTER] to Continue..");
							scanf("%c");
							getchar();
						}else{
							printf(" --Save Data--\n\n");
							for(int i=0; i<=n; i++){
								if(i==n){
									printf("[Back]                        %s\n", saveText[i+1]);								
								}else{
									printf("[%d] %-15s [Level %d] %s\n", i+1, a[i].name, a[i].level, saveText[i+1]);
								}
							}
						
							move=getch();
							switch(move){
								case 'w':
									saveText[saveCursor][5]=' ';
									(saveCursor<=1)?saveCursor:saveCursor--;
									saveText[saveCursor][5]='<';
									break;

								case 's':
									saveText[saveCursor][5]=' ';
									(saveCursor>=n+1)?saveCursor:saveCursor++;
									saveText[saveCursor][5]='<';
									break;	
									
								case ' ':
									if(saveCursor==n+1){
										menu();
									}else{
										strcpy(name, a[saveCursor-1].name);
										level = a[saveCursor-1].level;
										exp = a[saveCursor-1].exp;
										gold = a[saveCursor-1].gold;
										pHP = a[saveCursor-1].pHP;
										pAtk = a[saveCursor-1].pAtk;
										armorLvl = a[saveCursor-1].armorLvl;
										weaponLvl = a[saveCursor-1].weaponLvl;
										hpPotCount = a[saveCursor-1].hpPotCount;
										atkPotCount = a[saveCursor-1].atkPotCount;	
										saveCursor=1;
										n -= 1;
										lobby();								
									}	
							}
						}
					}
				}else if(cursor==3){
					system("cls");
					printf(" --CONTROLS--\n\n");
					printf("-Lobby-\n");
					printf("W - Up\n");
					printf("A - Left\n");
					printf("S - Down\n");
					printf("D - Right\n");
					printf("I - Open Inventory\n");
					printf("SPACE - Interact\n\n");
					printf("-Game-\n");
					printf("W - Move Cursor Up\n");
					printf("S - Move Cursor Down\n");
					printf("SPACE - Select Option\n\n");
					printf("Press Enter to Continue...");
					scanf("%c");
					cursor=1;
					menu();
				}else if(cursor==4){
					system("cls");
					printf(" --SECRET MENU--\n\n");
					printf(" Enter Code: ");
					scanf("%[^\n]", secretCode);
					if(strcmpi(secretCode, "I love you") == 0){
						printf("\n	<3");
						scanf("%c"); getchar();
					}else if(strcmpi(secretCode, "$$$") == 0){
						printf("\n Money Cheat Activated");
						gold = 1000000000;
						scanf("%c"); getchar();
					}else if(strcmpi(secretCode, "Zoomers") == 0){
						printf("\n Double EXP Gain");
						expCheat = 1;
						scanf("%c"); getchar();
					}else{
						printf("\n Nothing here..");
						scanf("%c"); getchar();
					}
					cursor=1;
					menu();
				}else if(cursor==5){
					system("cls");
					printf("Thank you for playing!\n");
					exit(0);
				}
		}
	}
}

void newGame(){
	int verify;
	do{
		verify = 0;
		system("cls");
		printf("\n Insert Your Name: ");
		scanf("%s", &name);
		for(int i=0; i<n; i++){
			if(strcmp(a[i].name, name) == 0){
				printf("\n Name Already Exists!");
				scanf("%c");
				getchar();
				verify = 1;
			}
		}
	}while(verify == 1);
}

void lobbyMap(){
	for(int i=0; i<row; i++){
		for(int j=0; j<column; j++){
			if(j==0 || i==row-1 || j==column-1){				//outer box
				map[i][j] = '#';
			}else{
				map[i][j] = ' ';
			}
			
			if(i==0 && j<8 || i==0 && j>10){					//gate				
				map[i][j] = '#';
			}else if(i==0 && j>8 || i==0 && j<10){
				map[i][j] = '=';
			}
			
			if(i==7 && j==8 || i==7 && j==10){					//spawn
				map[i][j] = '=';
			}
			
			if(i==7 && j==4){									//save
				map[i][j] = '+';
			}
			
			if(i==3 && j==4){									//shop
				map[i][j] = 'S';
			}else if(i==2 && j==4 || i==2 && j==3 || i==4 && j==4 || i==4 && j==3){
				map[i][j] = '=';
			}else if(i==2 && j==5 || i==4 && j==5){
				map[i][j] = '-';
			}else if(i==3 && j==3){
				map[i][j] = '|';	
			}
			
			if(i==3 && j==14){
				map[i][j] = 'U';
			}else if(i==2 && j==15 || i==2 && j==14 || i==4 && j==15 || i==4 && j==14){
				map[i][j] = '=';
			}else if(i==2 && j==13 || i==4 && j==13){
				map[i][j] = '-';
			}else if(i==3 && j==15){
				map[i][j] = '|';	
			}
		}
	}
}

void lobby(){
	system("cls");
	
	lobbyMap();
	map[y][x] = 'A';
	
	while(true){
		system("cls");
		
		for(int i=0; i<row; i++){
			for(int j=0; j<column; j++){
				printf("%c", map[i][j]);
			}
			printf("\n");
		}
		
		printf("\n<%s>\n", &name);
		printf("------------\n");
		printf("Level : %d\n", level);
		printf("EXP   : %d\n", exp);
		printf("Gold  : %d\n", gold);
		
		if(y==1 && x==9 || y==1 && x==8 || y== 1 && x==10 || y == 3 && x== 5 || y == 3 && x == 13) printf("\nPress [SPACE] to Interact");
		if(y==7 && x==3 || y==7 && x==5 || y==6 && x==4 || y==8 && x==4) printf("\nPress [SPACE] to Interact");
		
		move=getch();
		fflush(stdin);
		if(y==3 && x==5){
			if(move == ' '){
				printf("\n\nHello! This is the shop. Do you want to buy anything?\n");
				printf("[Y/N] > ");
				scanf("%c", &yn);
				if(yn == 'Y' || yn == 'y'){
					shop();
				}else{
					continue;
				}
			}
		}
		
		if(y==3 && x==13){
			if(move == ' '){
				printf("\n\nWelcome to the upgrade station! Anything you want to upgrade?\n");
				printf("[Y/N] > ");
				scanf("%c", &yn);
				if(yn == 'Y' || yn == 'y'){
					upgrade();
				}else{
					continue;
				}
			}
		}
		
		if(y==1 && x==9 || y==1 && x==8 || y==1 && x==10){
			if(move == ' '){
				printf("\n\nDo you want to head out?\n");
				printf("[Y/N] > ");
				scanf("%c", &yn);
				if(yn == 'Y' || yn == 'y'){
					combat();
				}else{
					continue;
				}
			}
		}
		
		if(y==7 && x==3 || y==7 && x==5 || y==6 && x==4 || y==8 && x==4){
			if(move == ' '){
				printf("\n\nSave Game?\n");
				printf("[Y/N] > ");
				scanf("%c", &yn);
				if(yn == 'Y' || yn == 'y'){
					saveGame();
				}else{
					continue;
				}
			}
		}		
		
		switch(move){
			case 'w':
				map[y][x]=' ';
				(map[y-1][x]!=' ')?y:y--;
				map[y][x]='A';
				break;
			
			case 'a':
				map[y][x]=' ';
				(map[y][x-1]!=' ')?x:x--;
				map[y][x]='A';
				break;
			
			case 's':
				map[y][x]=' ';
				(map[y+1][x]!=' ')?y:y++;
				map[y][x]='A';
				break;
			
			case 'd':
				map[y][x]=' ';
				(map[y][x+1]!=' ')?x:x++;
				map[y][x]='A';
				break;
				
			case 'i':
				inventory();	
				break;
		}
	}
}

void shop(){
	system("cls");
	int shop = 0;
	strcpy(shopText[1], " [1] Health Potion - 10G   <  ");
	strcpy(shopText[2], " [2] Attack Potion - 15G      ");
	strcpy(shopText[3], " [LEAVE SHOP]                 ");
	shopCursor = 1;
	
	do{
		system("cls");
		printf("--SHOP--\n\n");
		printf("Your Gold: %d\n\n", gold);
		for(int i=1;i<4;i++){
			printf("%s\n", shopText[i]);
		}	
		
		move=getch();
		fflush(stdin);
		switch(move){
			case 'w':
				shopText[shopCursor][27]=' ';
				(shopCursor<=1)?shopCursor:shopCursor--;
				shopText[shopCursor][27]='<';
				break;

			case 's':
				shopText[shopCursor][27]=' ';
				(shopCursor>=3)?shopCursor:shopCursor++;
				shopText[shopCursor][27]='<';
				break;
			
			case ' ':
				if(shopCursor == 1){
					printf("\nHow many health potions do you want to buy?\n");
					printf("> ");
					scanf("%d", &amount);
					if(gold < amount*10){
						printf("\nYou don't have enough money!\n");
						printf("Press [Enter] to Continue");
						scanf("%c");
						getchar();
					}else if(gold >= amount*10){
						printf("\nYou bought %d health potion(s)!\n", amount);
						gold -= amount*10;
						hpPotCount += amount;
						printf("Press [Enter] to Continue");
						scanf("%c");
						getchar();
					}
				}else if(shopCursor == 2){
					printf("\nHow many attack potions do you want to buy?\n");
					printf("> ");
					scanf("%d", &amount);
					if(gold < amount*15){
						printf("\nYou don't have enough money!\n");
						printf("Press [Enter] to Continue");
						scanf("%c");
						getchar();
					}else if(gold >= amount*15){
						printf("\nYou bought %d attack potion(s)!\n", amount);
						gold -= amount*10;
						atkPotCount += amount;						
						printf("Press [Enter] to Continue");
						scanf("%c");
						getchar();
					}			
				}else if(shopCursor == 3){
					shopCursor = 1;
					shop = 1;
					break;
				}
		}
	}while(shop != 1);
}

void upgrade(){
	system("cls");
	int upgrade = 0;
	int cost;
	strcpy(upText[1], " [1] Armor Upgrade         <  ");
	strcpy(upText[2], " [2] Weapon Upgrade           ");
	strcpy(upText[3], " [LEAVE UPGRADE]              ");
	upCursor = 1; 
	
	do{
		system("cls");
		printf("--UPGRADE STATION--\n\n");
		printf("Your Gold: %d\n\n", gold);
		for(int i=1;i<4;i++){
			printf("%s\n", upText[i]);
		}	
		
		move=getch();
		fflush(stdin);
		switch(move){
			case 'w':
				upText[upCursor][27]=' ';
				(upCursor<=1)?upCursor:upCursor--;
				upText[upCursor][27]='<';
				break;

			case 's':
				upText[upCursor][27]=' ';
				(upCursor>=3)?upCursor:upCursor++;
				upText[upCursor][27]='<';
				break;
			
			case ' ':
				if(upCursor == 1){
					if(armorLvl == 10){
						printf("\nYour Armor is Fully Upgraded!\n");
						printf("\nPress [Enter] to Continue");
						scanf("%c");
						continue;
					}
					printf("\nArmor Level %d -> Armor Level %d\n", armorLvl, armorLvl+1);
					cost = (armorLvl+1)*50;
					printf("Cost: %d\n", cost);
					printf("\nProceed with Upgrade?\n");
					printf("[Y/N] > ");
					scanf("%c", &yn);
					if(yn == 'Y' || yn == 'y'){
						if(gold < cost){
							printf("\nYou don't have enough money!\n");
							printf("Press [Enter] to Continue");
							scanf("%c");
							getchar();
						}else if(gold >= cost){
							printf("\nSuccessfully Upgraded Armor!\n");
							printf("HP Increase: %d -> %d\n\n", pHP, pHP+(10*(armorLvl+1)));
							pHP = pHP+(10*(armorLvl+1));
							gold -= cost;
							armorLvl++;
							printf("Press [Enter] to Continue");
							scanf("%c");
							getchar();
						}
					}else{
						continue;
					}
				}else if(upCursor == 2){
					if(weaponLvl == 10){
						printf("\nYour Weapon is Fully Upgraded!\n");
						printf("\nPress [Enter] to Continue");
						scanf("%c");
						continue;
					}						
					printf("\nWeapon Level %d -> Weapon Level %d\n", weaponLvl, weaponLvl+1);
					cost = (weaponLvl+1)*50;
					printf("Cost: %d\n", cost);
					printf("\nProceed with Upgrade?\n");
					printf("[Y/N] > ");
					scanf("%c", &yn);
					if(yn == 'Y' || yn == 'y'){
						if(gold < cost){
							printf("\nYou don't have enough money!\n");
							printf("Press [Enter] to Continue");
							scanf("%c");
							getchar();
						}else if(gold >= cost){
							printf("\nSuccessfully Upgraded Weapon!\n");
							printf("ATK Increase: %d -> %d\n", pAtk, pAtk+(2*(weaponLvl+1)));
							printf("Increased Hit Chance by 5%\n\n");
							pAtk = pAtk+(2*(weaponLvl+1));
							hitChance = 70+(5*weaponLvl);
							gold -= cost;
							weaponLvl++;
							printf("Press [Enter] to Continue");
							scanf("%c");
							getchar();
						}
					}else{
						continue;
					}
				}else if(upCursor == 3){
					upCursor = 1;
					upgrade = 1;
					break;
				}
		}
	}while(upgrade != 1);	
}

void inventory(){
	system("cls");
	printf("--INVENTORY--\n\n");
	printf("Health : %d\n", pHP);
	printf("Attack : %d\n", pAtk);
	printf("Armor Level %d\n", armorLvl);
	printf("Weapon Level %d\n\n", weaponLvl);
	
	printf("Health Potion(s) - %d\n", hpPotCount);
	printf("Attack Potion(s) - %d\n\n", atkPotCount);
	printf("Press [Enter] to Continue");
	scanf("%c");
}

void eStats(){
	srand(time(0));
	eAtk = pAtk/2+rand()%pAtk;
	eHP = pHP/2+rand()%pHP;
}

void combat(){
	system("cls");
	eStats();
	int tempHP = pHP;
	int tempAtk = pAtk;
	int turn = 0;

	strcpy(batText[1], " [ Attack ]   <  ");
	strcpy(batText[2], " [ Items  ]      ");
	strcpy(batText[3], " [  Run   ]      ");
	batCursor = 1;
	
	strcpy(itemText[1], " Health Potion   <  ");
	strcpy(itemText[2], " Attack Potion      ");
	strcpy(itemText[3], " [Back]             ");
	itemCursor = 1;
	
	while(eHP > 0 || tempHP > 0){
		system("cls");
		printf("--Enemy--\n");
		printf("HP  : %d\n", eHP);
		printf("ATK : %d\n\n", eAtk);
		printf("--%s--\n", name);
		printf("HP  : %d\n", tempHP);
		printf("ATK : %d\n\n", tempAtk);
		if(turn == 0){
			printf(" [--Your Turn--]\n\n");
			for(int i=1;i<4;i++){
				printf("%s\n", batText[i]);
			}	
			
			move=getch();
			fflush(stdin);
			switch(move){
				case 'w':
					batText[batCursor][14]=' ';
					(batCursor<=1)?batCursor:batCursor--;
					batText[batCursor][14]='<';
					break;

				case 's':
					batText[batCursor][14]=' ';
					(batCursor>=3)?batCursor:batCursor++;
					batText[batCursor][14]='<';
					break;
			
				case ' ':
					if(batCursor == 1){
						int hit = 0+rand()%100;
						if(hit <= hitChance){
							printf("\nYou dealt %d damage to enemy!\n\n", pAtk);
							eHP -= pAtk;
							if(eHP <= 0){
								printf("\nDefeated Enemy!");
								int expGain = 10*level+rand()%eAtk;
								if(expCheat == 1){
									expGain *= 2;
								}
								printf("\nYou Won %d gold and %d EXP\n", eAtk, expGain);
								gold += eAtk;
								exp += expGain;
								int reqEXP = level*100;
								if(exp >= reqEXP){
									exp -= reqEXP;
									level++;
									printf("\nYou Leveled Up!\n");
									printf("Level %d -> Level %d\n\n", level-1, level);
									printf("Health Increase: %d -> %d\n", pHP, pHP+(5*level));
									printf("Attack Increase: %d -> %d\n", pAtk, pAtk+(2*level));
									pHP += 5*level;
									pAtk += 2*level;
								}
								printf("\nPress [Enter] to Continue");
								scanf("%c");
								lobby();
							}	
							printf("Press [Enter] to Continue");
							scanf("%c");
							turn = 1;						
							break;
						}else{
							printf("\nYou missed...\n\n");
							printf("Press [Enter] to Continue");
							scanf("%c");		
							turn = 1;					
							break;							
						}
					}else if(batCursor == 2){
						int flag = 0;
						while(flag == 0){
							system("cls");
							printf("\n");
							for(int i=1;i<4;i++){
								printf("%s\n", itemText[i]);
							}							
						
							move=getch();
							fflush(stdin);
							switch(move){
								case 'w':
									itemText[itemCursor][17]=' ';
									(itemCursor<=1)?itemCursor:itemCursor--;
									itemText[itemCursor][17]='<';
									break;

								case 's':
									itemText[itemCursor][17]=' ';
									(itemCursor>=3)?itemCursor:itemCursor++;
									itemText[itemCursor][17]='<';
									break;
			
								case ' ':
									if(itemCursor == 1){
										printf("\n\nYou have %d health potion(s)\n", hpPotCount);
										if(hpPotCount == 0){
											printf("Press [Enter] to Continue");
											scanf("%c");	
											continue;
										}else if(tempHP == pHP){
											printf("You have full health\n\n");
											printf("Press [Enter] to Continue");
											scanf("%c");	
											continue;
										}else{
											printf("Use health potion? [Y/N] > ");
											scanf("%c", &yn);
											if(yn == 'Y' || yn == 'y'){
												printf("\nUsed a health potion!\n");
												int recover = tempHP+20;
												if(recover > pHP){
													recover = pHP;
												}
												printf("Health Recovered: %d -> %d\n\n", tempHP, recover);
												tempHP = recover;
												hpPotCount--;
												printf("Press [Enter] to Continue");
												scanf("%c");
												getchar();
												flag = 1;
												turn = 1;		
												continue;											
											}
										}
									}else if(itemCursor == 2){
										printf("\n\nYou have %d attack potion(s)\n", atkPotCount);
											if(atkPotCount == 0){
												printf("Press [Enter] to Continue");
												scanf("%c");	
												continue;
											}else{
												printf("Use attack potion? [Y/N] > ");
												scanf("%c", &yn);
												if(yn == 'Y' || yn == 'y'){
													printf("\nUsed an attack potion!\n");
													printf("Attack Increase: %d -> %d\n\n", tempAtk, tempAtk+5);
													tempAtk += 5;
													atkPotCount--;
													printf("Press [Enter] to Continue");
													scanf("%c");
													getchar();
													flag = 1;
													turn = 1;		
													continue;											
												}
											}																	
									}else if(itemCursor == 3){
										flag = 1;
										continue;
									}
								}
							}
					}else if(batCursor == 3){
						printf("\nAre you sure you want to run? [Y/N] > ");
						scanf("%c", &yn);
						if(yn == 'Y' || yn == 'y'){
							printf("Successfully ran away...\n");
							printf("You lost %d gold", eAtk);
							printf("\n\nPress [Enter] to Continue");
							scanf("%c");
							getchar();							
							gold -= eAtk;
							lobby();
						}
					}
				}			
		}else if(turn == 1){
			if(eHP <= 0){
				break;
			}
			printf(" [--Enemy's Turn--]\n\n");
			int hit = 0+rand()%100;
			if(hit <= 60){
				printf("You took %d damage!\n\n", eAtk);
				tempHP -= eAtk;
				if(tempHP <= 0){
					printf("\nYou Got Defeated..");
					printf("\nYou Lost %d gold\n\n", eAtk);
					gold -= eAtk;
					printf("Press [Enter] to Continue");
					scanf("%c");	
					break;
				}				
				printf("Press [Enter] to Continue");
				scanf("%c");
				turn = 0;						
				continue;
			}else{
				printf("Enemy missed...\n\n");
				printf("Press [Enter] to Continue");
				scanf("%c");
				turn = 0;						
				continue;			
			}
		}
	}
	
	lobby();
}

void saveGame(){		
	int flag = 0;
	for(int i=0; i<n; i++){
		if(strcmp(name, a[i].name) == 0){
			strcpy(a[i].name, name);
			a[i].level = level;
			a[i].exp = exp;			
			a[i].gold = gold;
			a[i].pHP = pHP;
			a[i].pAtk = pAtk;
			a[i].armorLvl = armorLvl;
			a[i].weaponLvl = weaponLvl;
			a[i].hpPotCount = hpPotCount;
			a[i].atkPotCount = atkPotCount;
			flag = 1;
			break;														
		}
	}
	if(flag == 0){
		strcpy(a[n].name, name);
		a[n].level = level;
		a[n].exp = exp;			
		a[n].gold = gold;
		a[n].pHP = pHP;
		a[n].pAtk = pAtk;
		a[n].armorLvl = armorLvl;
		a[n].weaponLvl = weaponLvl;
		a[n].hpPotCount = hpPotCount;
		a[n].atkPotCount = atkPotCount;		
	}
	
	FILE* fp = fopen("AQsave.txt", "w");
	for(int i=0; i<=n; i++){	
		fprintf(fp, "%s#%d#%d#%d#%d#%d#%d#%d#%d#%d\n", a[i].name, a[i].level, a[i].exp, a[i].gold, a[i].pHP, a[i].pAtk, a[i].armorLvl, a[i].weaponLvl, a[i].hpPotCount, a[i].atkPotCount);		
	}
	fclose(fp);
	
	printf("\nSuccessfully Saved Game!");
	printf("\nPress [Enter] to Continue");
	scanf("%c");
	getchar();	
}
