#ifndef RUNNER_H
#define RUNNER_H

#include <iostream>
#include <vector>
#include <string>

#include "constants.h"

using namespace std;

bool check_correct_data(package data);
bool check_correct_time(long seconds);
int get_step_day(int steps);
double get_distance(int steps);
double get_calories_burned(double dist, times current_time);
string get_achievement(double dist);
string get_message_rhythm (int rhythm); //NUEVA FUNCION DE RITMO
vector<package> accept_package(package data);
times get_time_hms (long seconds);
string format_time (times t);
void show_message (times t, int steps, double dist, double calories, string achievement, string rhythm);


// TODO: Implemente los protitopis de funciones restantes:
//       show_message
//       get_time_hms
//       format_time

#endif