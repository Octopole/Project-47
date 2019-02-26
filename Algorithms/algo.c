#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
#include<time.h>
#define DIRCOEF 2
#define RESCOEF 0.001

int init_number=0;
double dir_coef=DIRCOEF, res_coef=RESCOEF;

int frame_calculate(double posi_table[init_number][4]){
    double new_table[init_number][4];
    for(int i=0; i<init_number; i++){
        double force_x=0, force_y=0, a_force_x=0, a_force_y=0;
        for(int j=0; j<init_number; j++){
            if(i!=j){
                //printf("%f, %f, %f, %f\n",posi_table[i][0], posi_table[j][0], posi_table[i][1], posi_table[j][1]);
                a_force_x = dir_coef*fabs(1/((posi_table[i][0]-posi_table[j][0]) * (posi_table[i][0]-posi_table[j][0]))-1/((360-(posi_table[i][0]-posi_table[j][0])) * (360-(posi_table[i][0]-posi_table[j][0]))));
                if((((posi_table[j][0]-posi_table[i][0])>0 && (posi_table[j][0]-posi_table[i][0])<180)) || (((posi_table[j][0]-posi_table[i][0])>-360 && (posi_table[j][0]-posi_table[i][0])<-180))){
                    a_force_x = -a_force_x;
                }
                a_force_y = dir_coef*fabs(1/((posi_table[i][1]-posi_table[j][1]) * (posi_table[i][1]-posi_table[j][1]))-1/((360-(posi_table[i][1]-posi_table[j][1])) * (360-(posi_table[i][1]-posi_table[j][1]))));
                if((((posi_table[j][1]-posi_table[i][1])>0 && (posi_table[j][1]-posi_table[i][1])<180)) || (((posi_table[j][1]-posi_table[i][1])>-360 && (posi_table[j][1]-posi_table[i][1])<-180))){
                    a_force_y = -a_force_y;
                }
                //printf("%d-%d fx: %f  fy: %f\n", i, j ,a_force_x, a_force_y);
                force_x = force_x + a_force_x;
                force_y = force_y + a_force_y;
            }
        }
        if(force_x<=res_coef && force_x>=-res_coef){
            force_x=0;
        }
        else if(force_x>res_coef){
            force_x-=res_coef;
        }
        else if(force_x<-res_coef){
            force_x+=res_coef;
        }
        if(force_y<=res_coef && force_y>=-res_coef){
            force_y=0;
        }
        else if(force_y>res_coef){
            force_y-=res_coef;
        }
        else if(force_y<-res_coef){
            force_y+=res_coef;
        }
        new_table[i][2]=posi_table[i][2]+force_x;
        new_table[i][3]=posi_table[i][3]+force_y;
        new_table[i][0]=posi_table[i][0]+new_table[i][2];
        new_table[i][1]=posi_table[i][1]+new_table[i][3];
        //printf("%f %f %f %f\n", new_table[i][0], new_table[i][1], new_table[i][2], new_table[i][3]);
    }
    for(int i=0; i<init_number; i++){
        while(new_table[i][0]<0){
            new_table[i][0]=360+new_table[i][0];
        }
        while(new_table[i][0]>=360){
            new_table[i][0]=new_table[i][0]-360;
        }
        while(new_table[i][1]<0){
            new_table[i][1]=360+new_table[i][1];
        }
        while(new_table[i][1]>=360){
            new_table[i][1]=new_table[i][1]-360;
        }
    }
    int flag=1;
    for(int i=0; i<init_number; i++){
        for(int j=2; j<4; j++){
            if(new_table[i][j]!=posi_table[i][j]){
                flag=0;
            }
        }
    }
    //printf("!!!\n");
    if(flag){
        return 1;
    }
    for(int i=0; i<init_number; i++){
        for(int j=0; j<4; j++){
            posi_table[i][j]=new_table[i][j];
        }
    }
    return 0;
}

int main(){
    printf("Enter the number of points: ");
    scanf("%d", &init_number);
    int counter=0;
    srand(time(NULL));
    double posi_table[init_number][4];
    for(int i=0; i<init_number; i++){
        posi_table[i][0]=rand()%359;
        posi_table[i][1]=rand()%359;
        posi_table[i][2]=0;
        posi_table[i][3]=0;
    }
    for(int i=0; i<init_number; i++){
        printf("(%f,%f) ", posi_table[i][0], posi_table[i][1]);
    }
    printf("\n");
    int con = 0;
    while(!con){
        //printf("!");
        con=frame_calculate(posi_table);
        counter++;
    }
    printf("Taken %d steps to calculate\n", counter);
    printf("Points' positions:\n");
    for(int i=0; i<init_number; i++){
        printf("(%f, %f) ", posi_table[i][0], posi_table[i][1]);
    }
    return 0;
}
