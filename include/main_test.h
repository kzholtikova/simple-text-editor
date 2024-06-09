#pragma once
#include <iostream>

std::streambuf * redirectCin();
void resetCin(std::streambuf* cinbuf);
std::streambuf* redirectCout();
void resetCout(std::streambuf* coutbuf);
