//
// Created by 29588 on 2024/12/17.
//

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <map>
using namespace std;
class User {
public:
    string account;
    string password;
    bool isMuted;
};

extern map<string, User> accountsUser;

void displayUserMenu();

void userLoginMenu();

void userLogin();

void userRegister();

void userChange();

void commentMenu();

void muteUser(const string& username);

void unmuteUser(const string& username);
#endif //USER_H
