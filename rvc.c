#include<stdio.h>

int void main() {
    int obstacle_Location;
    bool dust_Existence;
    bool power_onoff;

    while (1) {
        obstacle_Location = Det_OL();
        dust_Existence = Det_DE();
        power_onoff = Det_P();

        //power off 키가 눌린 경우 -> 바로 전원 끄고 shut down
        if (power_onoff == false) {
            exit();
        }

        //전방에 먼지가 존재하는 경우
        if(dust_Existence == true){

        }

        //전방에 장애물이 존재하는 경우 -> 왼쪽 우회가 오른쪽 우회보다 우선순위로 작동
        if (obstacle_Location == F) {

        }
        else {  //전방에 장애물이 존재하지 않는 경우

        }

        wait(1000);
    }


}