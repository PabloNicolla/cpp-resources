#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string_view>
#include <string>

void sharedAddOperation(int& toAdd1, int& toAdd2, int& toAdd3);
void sharedPrintOpearation(std::string_view sv);
void testMutex();
