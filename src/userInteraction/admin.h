#ifndef MINIMETRO_ADMIN_H
#define MINIMETRO_ADMIN_H

void displayAdminMenu();

void logInMenu();

void adminLogIn();

void adminRegister();

void stationManagement();

void commentsManageDelete();

void basicManagement();

void changerUserPassword();

void muteUser(const std::string& username);

void unmuteUser(const std::string& username);

#endif //MINIMETRO_ADMIN_H
