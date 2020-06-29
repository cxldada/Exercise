/**
2. 1501
3. -1547
4. 42031180
1234567^12345678901234567890 % 999999997 = ?

5. 1/2*3*4-5+6-7*8*9
1_2_3_4_5_6_7_8_9=-497

6. 2.19488134060852
x^5 - 2x^4 + 3x^3 - 4x^2 - 5x - 6 = 0

8. 虚拟机
*/
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;

int operatorValue(std::string o, int a, int b, bool &isBreak) {
    isBreak = true;
    if (o == "+")
        return a + b;
    else if (o == "-")
        return a - b;
    else if (o == "*")
        return a * b;
    else if (o == "/") {
        if (b != 0)
            return a / b;
        else
            isBreak = true;
    }
    isBreak = false;
    return 0;
}

bool calc(std::vector<std::string> &vStr) {
    std::stack<int> sNum;
    for(int i = 9;i > 0;--i) {
        sNum.push(i);
    }

    if (sNum.size() > 0){
        for (int i = 1; i < 10; ++i) {
            if(i < 9)
                cout << i << ".0" << vStr[i - 1];
            else
                cout << i << ".0" << endl;
        }
    }

    return true;
}

int main(int argc, char const *argv[]) {
    std::vector<std::string> vOperator;
    std::vector<std::string> vStr = {"+", "-", "*", "/"};

    for (std::string op1 : vStr) {
        vOperator.push_back(op1);

        for (std::string op2 : vStr) {
            vOperator.push_back(op2);

            for (std::string op3 : vStr) {
                vOperator.push_back(op3);

                for (std::string op4 : vStr) {
                    vOperator.push_back(op4);

                    for (std::string op5 : vStr) {
                        vOperator.push_back(op5);

                        for (std::string op6 : vStr) {
                            vOperator.push_back(op6);

                            for (std::string op7 : vStr) {
                                vOperator.push_back(op7);

                                for (std::string op8 : vStr) {
                                    vOperator.push_back(op8);
                                    if (!calc(vOperator)) {
                                        cout << "error" << endl;
                                        return 0;
                                    }
                                    vOperator.erase(vOperator.begin() + 7);
                                }
                                vOperator.erase(vOperator.begin() + 6, vOperator.end());
                            }
                            vOperator.erase(vOperator.begin() + 5, vOperator.end());
                        }
                        vOperator.erase(vOperator.begin() + 4, vOperator.end());
                    }
                    vOperator.erase(vOperator.begin() + 3, vOperator.end());
                }
                vOperator.erase(vOperator.begin() + 2, vOperator.end());
            }
            vOperator.erase(vOperator.begin() + 1, vOperator.end());
        }
        vOperator.clear();
    }

    return 0;
}
