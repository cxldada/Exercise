#include <math.h>
#include <cstring>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
    /*
    double a,b;
    a = 10.1;
    b = ceil(a);
    cout << a << "  " << b << endl;

    unsigned min, max;
    size_t tokenPos;
    string str = "12|13", maxs, mins;

    if ((tokenPos = str.find("|")) == std::string::npos) {
        return 1;
    }

    mins = str.substr(0, tokenPos);
    maxs = str.substr(tokenPos + 1);

    // min = atoi(mins.c_str());
    max = atoi("111");
    cout << tokenPos << " " << min << " " << max << endl;
    */

    cout << sizeof(time_t) << endl;

    return 0;
}
