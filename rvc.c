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
    struct RVC rvc = { true, false, false, false, false, false, true, 0, 0 }; // RVC 전원을 킴
    while (1) {

        dust_Existence = Det_DE(&rvc);
        power_onoff = rvc.power_onoff;

        //power off 키가 눌린 경우 -> 바로 전원 끄고 shut down
        if (power_onoff == false) {
            printf("RVC의 전원이 꺼졌습니다\n");
            exit(1);
        }

        //전방에 먼지가 존재하는 경우
        if (dust_Existence == true) {
            printf("먼지가 있습니다, 청소를 시작합니다\n");
            rvc.move_forward = false;
            rvc.cleaner_command = POWER_UP;
            Sleep(10 * TICK);
            rvc.elapsed_time += 10 * TICK;
            printf("깨끗하게 청소를 했습니다.\n");
            rvc.cleaner_command = POWER_UP;
            rvc.move_forward = true;
        }

        obstacle_Location = Det_OL(&rvc);
        //전방에 장애물이 존재하는 경우 -> 왼쪽 우회가 오른쪽 우회보다 우선순위로 작동
        if (obstacle_Location == TURN_LEFT) {
            rvc.move_forward = false;
            rvc.cleaner_command = TURN_OFF;
            Turn_Left();
            Sleep(5 * TICK); // RVC가 왼쪽으로 회전하는 시간
            rvc.elapsed_time += 5 * TICK;
            rvc.move_forward = true;
            rvc.cleaner_command = TURN_ON;
        }
        else if (obstacle_Location == TURN_RIGHT) {
            rvc.move_forward = false;
            rvc.cleaner_command = TURN_OFF;
            Turn_Right();
            Sleep(5 * TICK); // RVC가 오른쪽으로 회전하는 시간
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
                Sleep(5 * TICK); // RVC가 뒤로 움직이는 시간
                rvc.elapsed_time += 5 * TICK;
                obstacle_Location = Det_OL(&rvc);
                if (obstacle_Location == TURN_LEFT) {
                    rvc.move_backward = false;
                    Turn_Left();
                    Sleep(5 * TICK); // RVC가 왼쪽으로 회전하는 시간
                    rvc.elapsed_time += 5 * TICK;
                    rvc.move_forward = true;
                    rvc.cleaner_command = TURN_ON;
                }
                else if (obstacle_Location == TURN_RIGHT) {
                    rvc.move_backward = false;
                    Turn_Right();
                    Sleep(5 * TICK); // RVC가 오른쪽으로 회전하는 시간
                    rvc.elapsed_time += 5 * TICK;
                    rvc.move_forward = true;
                    rvc.cleaner_command = TURN_ON;
                }
            }
        }
        else {  //전방에 장애물이 존재하지 않는 경우
            Move_Forward();

            Sleep(1 * TICK); // RVC가 앞으로 움직이는 시간
            rvc.elapsed_time += 1 * TICK;
        }
        if (rvc.elapsed_time >= 36 * TICK) { // 60분 경과시 자동으로 전원꺼짐
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
    // RVC가 왼쪽으로 90도 회전한다
    printf("왼쪽으로 회전\n");
}

void Turn_Right() {
    // RVC가 오른쪽으로 90도 회전한다
    printf("오른쪽으로 회전\n");
}

void Move_Forward() {
    // RVC가 앞으로 움직인다
    printf("전진\n");
}
void Move_Backward() {
    // RVC가 뒤로 움직인다
    printf("후진\n");
}