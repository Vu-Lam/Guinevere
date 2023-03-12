#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "main.h"
#include <math.h>
#define MAX 100
#define MaxHP 999
#define Max_level 10
#define Max_remedy 99
#define Max_maidenkiss 99
#define Max_phoenixdown 99
#define baseDamage_MadBear 1
#define baseDamage_Bandit 1.5
#define baseDamage_LordLupin 4.5
#define baseDamage_Elf 7.5
#define baseDamage_Troll 9.5
struct knight
{
    int HP;
    int level;
    int remdedy;
    int maidenkiss;
    int phoenixdown;
    int max_HP;
    int rescue;
};
void convIntArr(string line, int a[]);
bool lose(knight &hero);
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue);
void update(knight hero, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue);
void event_0(knight &hero);
void event_15(knight &hero, int index, int event);
void event_6(knight &hero, int index, bool &isTiny);
bool endTiny(knight &hero, int index, int check_event6_end, bool isTiny);
void event_7(knight &hero, int index);
void becomeFrog(knight &hero);
void event_11(knight &hero);
bool isPrime(int n);
void event_12(knight &hero);
bool isFibonacci(int n);
void event_13(knight &hero, int mush_type, string file_mush_ghost);
int find_mini(int arr[], int n);
int find_maxi(int arr[], int n);
int find_mini2(int arr[], int n);
int find_maxi2(int arr[], int n);
bool isMountainArray(int *arr, int n, int &mtx, int &mti);
void event_18(knight &hero, string file_merlin_pack);
bool isCharacter(char check_char, char in_put);
bool isLancelot(knight &hero);
bool isArthur(knight &hero);
#endif // __KNIGHT_H__