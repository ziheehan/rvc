#include<stdio.h>

int void main() {
    int obstacle_Location;
    bool dust_Existence;
    bool power_onoff;

    while (1) {
        obstacle_Location = Det_OL();
        dust_Existence = Det_DE();
        power_onoff = Det_P();

        //power off Ű�� ���� ��� -> �ٷ� ���� ���� shut down
        if (power_onoff == false) {
            exit();
        }

        //���濡 ������ �����ϴ� ���
        if(dust_Existence == true){

        }

        //���濡 ��ֹ��� �����ϴ� ��� -> ���� ��ȸ�� ������ ��ȸ���� �켱������ �۵�
        if (obstacle_Location == F) {

        }
        else {  //���濡 ��ֹ��� �������� �ʴ� ���

        }

        wait(1000);
    }


}