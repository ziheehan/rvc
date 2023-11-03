#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<Windows.h>

#define TICK 1000
// Motor Command
#define MOVE_FORWARD 1
#define TURN_LEFT 2
#define TURN_RIGHT 3
#define MOVE_BACKWARD 4
// Cleaner Command
#define TURN_OFF 0
#define TURN_ON 1
#define POWER_UP 2

bool Det_DE(struct RVC* rvc);
int Det_OL(struct RVC* rvc);

void Turn_Left();
void Turn_Right();
void Move_Forward();
void Move_Backward();

struct RVC {
    bool move_forward;
    bool move_backward;
    bool is_dust;
    bool is_front_obs;
    bool is_left_obs;
    bool is_right_obs;
    bool power_onoff; // = STOP
    int cleaner_command;
    int elapsed_time;
};

int main(void) {
    int obstacle_Location;
    bool dust_Existence;
    bool power_onoff;
    struct RVC rvc = { true, false, false, false, false, false, true, 0, 0 }; // RVC ������ Ŵ
    while (1) {

        dust_Existence = Det_DE(&rvc);
        power_onoff = rvc.power_onoff;

        //power off Ű�� ���� ��� -> �ٷ� ���� ���� shut down
        if (power_onoff == false) {
            printf("RVC�� ������ �������ϴ�\n");
            exit(1);
        }

        //���濡 ������ �����ϴ� ���
        if (dust_Existence == true) {
            printf("������ �ֽ��ϴ�, û�Ҹ� �����մϴ�\n");
            rvc.move_forward = false;
            rvc.cleaner_command = POWER_UP;
            Sleep(10 * TICK);
            rvc.elapsed_time += 10 * TICK;
            printf("�����ϰ� û�Ҹ� �߽��ϴ�.\n");
            rvc.cleaner_command = POWER_UP;
            rvc.move_forward = true;
        }

        obstacle_Location = Det_OL(&rvc);
        //���濡 ��ֹ��� �����ϴ� ��� -> ���� ��ȸ�� ������ ��ȸ���� �켱������ �۵�
        if (obstacle_Location == TURN_LEFT) {
            rvc.move_forward = false;
            rvc.cleaner_command = TURN_OFF;
            Turn_Left();
            Sleep(5 * TICK); // RVC�� �������� ȸ���ϴ� �ð�
            rvc.elapsed_time += 5 * TICK;
            rvc.move_forward = true;
            rvc.cleaner_command = TURN_ON;
        }
        else if (obstacle_Location == TURN_RIGHT) {
            rvc.move_forward = false;
            rvc.cleaner_command = TURN_OFF;
            Turn_Right();
            Sleep(5 * TICK); // RVC�� ���������� ȸ���ϴ� �ð�
            rvc.elapsed_time += 5 * TICK;
            rvc.move_forward = true;
            rvc.cleaner_command = TURN_ON;
        }
        else if (obstacle_Location == MOVE_BACKWARD) {
            rvc.move_forward = false;
            rvc.cleaner_command = TURN_OFF;
            rvc.move_backward = true;
            while (rvc.move_backward) {
                Move_Backward();
                Sleep(5 * TICK); // RVC�� �ڷ� �����̴� �ð�
                rvc.elapsed_time += 5 * TICK;
                obstacle_Location = Det_OL(&rvc);
                if (obstacle_Location == TURN_LEFT) {
                    rvc.move_backward = false;
                    Turn_Left();
                    Sleep(5 * TICK); // RVC�� �������� ȸ���ϴ� �ð�
                    rvc.elapsed_time += 5 * TICK;
                    rvc.move_forward = true;
                    rvc.cleaner_command = TURN_ON;
                }
                else if (obstacle_Location == TURN_RIGHT) {
                    rvc.move_backward = false;
                    Turn_Right();
                    Sleep(5 * TICK); // RVC�� ���������� ȸ���ϴ� �ð�
                    rvc.elapsed_time += 5 * TICK;
                    rvc.move_forward = true;
                    rvc.cleaner_command = TURN_ON;
                }
            }
        }
        else {  //���濡 ��ֹ��� �������� �ʴ� ���
            Move_Forward();

            Sleep(1 * TICK); // RVC�� ������ �����̴� �ð�
            rvc.elapsed_time += 1 * TICK;
        }
        if (rvc.elapsed_time >= 36 * TICK) { // 60�� ����� �ڵ����� ��������
            rvc.power_onoff = false;
        }
    }
    return 0;
}

bool Det_DE(struct RVC* rvc) {
    return rvc->is_dust;
}

int Det_OL(struct RVC* rvc) {
    if (rvc->is_front_obs && !rvc->is_left_obs) {
        return TURN_LEFT;
    }
    else if (rvc->is_front_obs && rvc->is_left_obs && !rvc->is_right_obs) {
        return TURN_RIGHT;
    }
    else if (rvc->is_front_obs && rvc->is_left_obs && rvc->is_right_obs) {
        return MOVE_BACKWARD;
    }
    return MOVE_FORWARD;
}

void Turn_Left() {
    // RVC�� �������� 90�� ȸ���Ѵ�
    printf("�������� ȸ��\n");
}

void Turn_Right() {
    // RVC�� ���������� 90�� ȸ���Ѵ�
    printf("���������� ȸ��\n");
}

void Move_Forward() {
    // RVC�� ������ �����δ�
    printf("����\n");
}
void Move_Backward() {
    // RVC�� �ڷ� �����δ�
    printf("����\n");
}