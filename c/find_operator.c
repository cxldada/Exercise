/**
2. 1501
3. -1547
4. 42031180
6. 2.1948813406085
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
}

bool calc(std::vector<std::string> &vStr) {
    std::stack<int> sNum;
    for(int i = 9;i > 0;--i) {
        sNum.push(i);
    }

    for (std::string op : vStr) {
        int a, b, c;
        bool isBreak = false;
        b = sNum.top();
        sNum.pop();
        a = sNum.top();
        sNum.pop();

        c = operatorValue(op, a, b, isBreak);
        if (!isBreak)
            return isBreak;
        sNum.push(c);
    }
    if (sNum.size() > 0){
        for (int i = 1; i < 10; ++i) {
            if(i < 9)
                cout << i << vStr[i - 1];
            else
                cout << i << "=";
        }
        cout << sNum.top() << endl;
        if(sNum.top() == -497){
            return true;
        }
    }

    return false;
}

int main(int argc, char const *argv[]) {
    std::vector<std::string> vOperator;
    std::vector<std::string> vStr = {"+", "-", "*", "/"};
    //std::map<std::string, int> mFlag;

    for (std::string op1 : vStr) {
        vOperator.push_back(op1);
        // mFlag[op1] += 1;

        for (std::string op2 : vStr) {
            vOperator.push_back(op2);
            // mFlag[op2] += 1;

            for (std::string op3 : vStr) {
                vOperator.push_back(op3);
                // mFlag[op3] += 1;

                for (std::string op4 : vStr) {
                    vOperator.push_back(op4);
                    // mFlag[op4] += 1;

                    for (std::string op5 : vStr) {
                        vOperator.push_back(op5);
                        // mFlag[op5] += 1;

                        for (std::string op6 : vStr) {
                            vOperator.push_back(op6);
                            // mFlag[op6] += 1;

                            for (std::string op7 : vStr) {
                                vOperator.push_back(op7);
                                // mFlag[op7] += 1;

                                for (std::string op8 : vStr) {
                                    vOperator.push_back(op8);
                                    // mFlag[op8] += 1;

/*
                                    bool isCalc = true;
                                    for (auto it : mFlag) {
                                        if(it.second == 0){
                                            isCalc = false;
                                            break;
                                        }
                                    }
                                    if(mFlag.size() != 4)
                                        isCalc = false;
*/
                                    if (calc(vOperator)) {
                                        return 0;
                                    }
                                    // mFlag[op8] -= 1;
                                    vOperator.erase(vOperator.end());
                                }
                                // mFlag[op7] -= 1;
                                vOperator.erase(vOperator.begin() + 6, vOperator.end());
                            }
                            // mFlag[op6] -= 1;
                            vOperator.erase(vOperator.begin() + 5, vOperator.end());
                        }
                        // mFlag[op5] -= 1;
                        vOperator.erase(vOperator.begin() + 4, vOperator.end());
                    }
                    // mFlag[op4] -= 1;
                    vOperator.erase(vOperator.begin() + 3, vOperator.end());
                }
                // mFlag[op3] -= 1;
                vOperator.erase(vOperator.begin() + 2, vOperator.end());
            }
            // mFlag[op2] -= 1;
            vOperator.erase(vOperator.begin() + 1, vOperator.end());
        }
        // mFlag[op1] -= 1;
        vOperator.clear();
    }

    return 0;
}
