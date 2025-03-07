#ifndef MINIMETRO_ADMIN_H
#define MINIMETRO_ADMIN_H
#include<iostream>


void displayAdminMenu();

void logInMenu();

void adminLogIn();

void adminRegister();

void stationManagement();

void commentsManagement();

void userManagement();

void basicManagement();

void changerUserPassword();

void muteUser(const std::string& username);

void unmuteUser(const std::string& username);

extern void (*muteUserPtr)(const std::string&);

extern void (*unmuteUserPtr)(const std::string&);

extern void (*adminChangeUserPtr)();
#endif //MINIMETRO_ADMIN_H
