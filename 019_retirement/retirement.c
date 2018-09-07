#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

double cal_bal(double bal, double rate, double con) {
  bal = bal * rate + bal + con;
  return bal;
}

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  double balance = initial;
  int age = startAge;
  printf("Age %3d month %2d you have $%.02lf\n", age / 12, age % 12, balance);
  for (int i = 1; i <= working.months; i++) {
    balance = cal_bal(balance, working.rate_of_return, working.contribution);
    age = age + 1;
    printf("Age %3d month %2d you have $%.02lf\n", age / 12, age % 12, balance);
  }
  for (int j = 1; j < retired.months; j++) {
    balance = cal_bal(balance, retired.rate_of_return, retired.contribution);
    age = age + 1;
    printf("Age %3d month %2d you have $%.02lf\n", age / 12, age % 12, balance);
  }
}
int main() {
  retire_info_t working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info_t retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return 0;
}
