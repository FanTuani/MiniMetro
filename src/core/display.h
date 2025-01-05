#ifndef MINIMETRO_DISPLAY_H
#define MINIMETRO_DISPLAY_H

#include <string>

void displayMenu();

void displayNavigation();

void displayStationInfo();

void displayCommentInteraction(std::string &, int flag);

void showLines();

void deleteComment();

#endif //MINIMETRO_DISPLAY_H
