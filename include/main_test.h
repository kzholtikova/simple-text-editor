#pragma once
#include <iostream>

std::streambuf* redirectCout();
void resetCout(std::streambuf* coutbuf);
