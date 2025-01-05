//
// Created by 29588 on 2024/12/17.
//

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <map>

class User {
public:
    std::string account;
    std::string password;
    bool isMuted;
};

extern std::map<std::string, User> accountsUser;

void displayUserMenu();

void userLoginMenu();

void userLogin();

void userRegister();

void userChange();

void commentMenu();

void muteUser(const std::string& username);

void unmuteUser(const std::string& username);
#endif //USER_H
