// impl.cpp
// Module implementation unit
// Module implementation unit files should use .cpp as a file extension.

module;

#ifdef PLAY_HAS_IMPORT_STD
import std;
#else
# include <iostream>
#endif

module M;
void Hello() {
    std::cout << "Hello ";
}
