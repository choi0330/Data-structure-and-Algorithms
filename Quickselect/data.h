#pragma once
#include <vector>


// input data, three formats possible
// (a) data <n:int> {int:n} <k>
// (b) file <filename:string> <k>
// (c) random <n:int> <k>
std::vector<int> getData();
