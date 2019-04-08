#include "user.h"

int load_file(LOGIN* list[], char* filename){ 
 //파일이 존재하지 않을때
  int choice;
  int count=0;
  FILE *datafile;
  if(0 == access(filename, F_OK)){
    printf("file exist!\n");
    datafile = fopen(filename, "r");
    while(!feof(datafile)){
      list[count]=(LOGIN*)malloc(sizeof(LOGIN));
      fscanf(datafile,"%s %s",list[count]->id,list[count]->password);
      count++;
    }
    printf("%d records read!\n",count);
  }else{
    //count==0
    printf("%s file not exist! make anyway? (Yes 1, No 2) >> ", filename);
    scanf("%d",&choice);
    if(choice == 1){
      //파일생성
      datafile = fopen(filename, "w");
      printf("> Welcome!!\n");
    }
    count++;
  }
  fclose(datafile);
  return count;
}

void join(LOGIN* list[], int count){
  char id[20], pass[20];
  while(1){
    printf("Enter new user id >> ");
    scanf("%s", id);
    int dup=0;
    for(int i=0;i<count;i++){
      if(strcmp(id, list[i]->id)==0) {
        dup=1; break;
      }
    }
    if(dup==1){
      printf("Already exist!!\n");
    }
    else{
      printf("Enter password >> ");
      scanf("%s", pass);
      list[count] = (LOGIN*)malloc(sizeof(LOGIN));
      strcpy(list[count]->id, id);
      strcpy(list[count]->password, pass);
      printf("New user added!\n");
      break;
    }
  }
}

int login(LOGIN* list[], int count){
  char id[20], pass[20];
  printf("Enter user id >> ");
  scanf("%s", id);
  int dup=0, found;
  for(int i=0;i<count;i++){
    if(strcmp(id, list[i]->id)==0) {
      dup=1;
      found = i;
      break;
    }
  }
  if(dup!=1){
    printf("No such user!!\n");
    return -1;
  }
  else{
    printf("Enter password >> ");
    scanf("%s", pass);
    if(strcmp(list[found]->password, pass)==0){
      printf("Welcome %s!!\n", id);
      return 1;
    }
    else{
      printf("Password incorrect!!\n");
      return 0;
    }
  }
}

void logout(int* is_login){
  *is_login = 0;
  printf("Logout!!\n");
}

void save_file(LOGIN* list[], int count, char* filename){
  FILE *datafile = fopen(filename, "w");
  for(int i=0; i<count; i++){
    fprintf(datafile, "%s %s\n", list[i]->id, list[i]->password);
  }
  printf("%s Saved!\n", filename);
  fclose(datafile);
}
