#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int main(int argc, char **argv) {
    printf("Starting the program...\n");

    int option;
    srand(time(NULL)); // 난수 생성을 위한 시드 설정

    for (int i = 0; i < 100; i++) {
        option = rand() % 5;

        if (option == 0) {
            printf("Option 0 selected. Processing...\n");
            // 여기에 option 0에 대한 작업 추가
        } else if (option == 1) {
            printf("Option 1 selected. Processing...\n");
            // 여기에 option 1에 대한 작업 추가
        } else if (option == 2) {
            printf("Option 2 selected. Processing...\n");
            // 여기에 option 2에 대한 작업 추가
        } else if (option == 3) {
            printf("Option 3 selected. Processing...\n");
            // 여기에 option 3에 대한 작업 추가
        } else {
            printf("Default option selected. Processing...\n");
            // 여기에 default 작업 추가
        }

        // 임의의 딜레이 추가
        int delay_time = rand() % 1000; // 0부터 999까지의 랜덤한 수
        delay(delay_time); // 딜레이 추가
    }

    printf("Program finished.\n");

    return 0;
}
