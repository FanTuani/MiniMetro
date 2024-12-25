#include <iostream>
#include <map>
#include <vector>
#include "user.h"
#include "station.h"
#include "utils.h"
#include "display.h"
#include "set"

using namespace std;

bool isUserLoggedIn = false;
string UserLoginAcc;
const map<string, string> preAcc = {{"wjr", "123"}};
class User {
public:
    std::string account;
    std::string password;
    bool isMuted;
};

std::map<std::string, User> accountsUser;

void displayUserMenu() {
    userLoginMenu();
    if (!isUserLoggedIn) {
        return;
    }
    clear_screen();
    cout << "User Management\n";
    cout << "1. Navigation\n";
    cout << "2. Show existing lines\n";
    cout << "3. Search station info\n";
    cout << "4. Comments manage\n";
    cout << "5. Exit\n";
    int op;
    cin >> op;
    switch (op) {
        case 1:
            displayNavigation();
        break;
        case 2:
            showLines();
        break;
        case 3:
            displayStationInfo();
        break;
        case 4:
            commentsManagement();
        break;
        default:
            return;
    }
}
void userLoginMenu() {
    clear_screen();
    cout << "User Login Menu\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Change password\n";
    cout << "4. Logout\n";
    cout << "5. return\n";
    cout << "6. Exit\n";
    char op;
    cin >> op;
    getchar();
    switch (op) {
        case '1':
            userLogin();
        break;
        case '2':
            userRegister();
        break;
        case '3':
            userChange();
        break;
        case '4':
            clear_screen();
        if (!isUserLoggedIn) {
            cout << "You have not logged in!\n";
        } else {
            isUserLoggedIn = false;
            cout << "Log out successfully\n";
        }
        getchar();
            userLoginMenu();
        break;
        case '6':
            exit(0);
        default:
            return;
    }
}
void userLogin() {
    clear_screen();
    if (isUserLoggedIn) {
        cout << "You have logged in!\n";
        cout << "Account: " << UserLoginAcc << '\n';
        getchar();
        return;
    }
    cout << "Log in your account\n";
    string account, password;
    cout << "Account: ";
    cin >> account;
    cout << "Password: ";
    cin >> password;
    getchar();
    if (accountsUser.find(account) != accountsUser.end() && accountsUser[account].password == password) {
        cout << "Login successfully!\n";
        UserLoginAcc = account;
        isUserLoggedIn = true;
        getchar();
        return;
    }
    cout << "LOGIN FAILED, NO SUCH ACCOUNT\n";
    getchar();
}

void userRegister() {
    clear_screen();
    string account, password, rep;
    cout << "New Account: ";
    cin >> account;
    cout << "Password: ";
    cin >> password;
    cout << "Password again: ";
    cin >> rep;
    getchar();
    if (password != rep || accountsUser.find(account) != accountsUser.end()) {
        cout << "REGISTER FAILED, DIFFERENT PASSWORD OR ACCOUNT ALREADY EXISTS\n";
        getchar();
        return;
    }
    accountsUser[account].password = password;
    cout << "Registered successfully\n";
    getchar();
}

void userChange() {
    clear_screen();
    string account, currentPassword, newpassword, rep;
    cout << "Enter your account: ";
    cin >> account;
    cout << "Enter your current password: ";
    cin >> currentPassword;
    cout << "Enter your new password: ";
    cin >> newpassword;
    cout << "Enter your new password again: ";
    cin >> rep;
    getchar();
    if (newpassword != rep) {
        cout << "PASSWORD CHANGE FAILED, DIFFERENT PASSWORDS ENTERED\n";
        getchar();
        return;
    }
    // 检查当前密码是否正确
    if (accountsUser.find(account) != accountsUser.end() && accountsUser[account].password == currentPassword) {
        // 更新密码
        accountsUser[account].password = newpassword;
        cout << "Password change successfully\n";
    } else {
        cout << "PASSWORD CHANGE FAILED, INCORRECT CURRENT PASSWORD\n";
    }
    getchar();
}
void commentsManagement() {
    clear_screen();

    cout << "Station name: ";
    string name;
    cin >> name;
    getchar();
    if (stations.find(name) == stations.end()) {
        cout << "INVALID STATION NAME\n";
        getchar();
        return;
    }
    Station &station = stations[name];
    clear_screen();
    station.showInfo();

    if (accountsUser[UserLoginAcc].isMuted) {
        cout << "You have been muted and cannot use comment features.\n";
        return;
    }

    cout << "\n----- Management menu -----\n";
    cout << "1. Add comment\n";
    cout << "2. Return\n";
    char op;
    cin >> op;
    getchar();

    switch (op) {
        case '1': displayCommentInteraction(name);
        break;
        case '2': deleteComment();
        break;
        case '3': return;
    }

}

