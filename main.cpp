#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// all inputs combinations
bool truthTable[8][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
};
void substituteVariables(string& expression, bool A, bool B, bool C) {
    for (char& ch : expression) {
        if (ch == 'A') {
            ch = A ? '1' : '0';
        }
        else if (ch == 'B') {
            ch = B ? '1' : '0';
        }
        else if (ch == 'C') {
            ch = C ? '1' : '0';
        }
    }
}
char evaluateOperation(char operand1, char operand2, char operation) {
    if (operation == '&') {
        return (operand1 == '1' && operand2 == '1') ? '1' : '0';
    }
    else if (operation == '|') {
        return (operand1 == '1' || operand2 == '1') ? '1' : '0';
    }
}
char NOT(char operand)
{
    return operand == '1' ? '0' : '1';

}
bool evaluateBooleanExpression(string expression) {
    stack<char> values;
    stack<char> ops;

    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') continue;

        if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        else if (expression[i] == '0' || expression[i] == '1') {
            values.push(expression[i]);
        }
        else if (expression[i] == '!') {
            ops.push(expression[i]);
        }
        else if (expression[i] == '&' || expression[i] == '|') {
            ops.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                char op = ops.top();
                ops.pop();

                if (op == '!') {
                    char val = values.top();
                    values.pop();
                    values.push(NOT(val));
                }
                else if (op == '&' || op == '|') {
                    char val2 = values.top();
                    values.pop();
                    char val1 = values.top();
                    values.pop();
                    values.push(evaluateOperation(val1, val2, op));
                }
            }
            if (!ops.empty()) ops.pop(); // Remove '('
        }
    }

    return values.top() == '1';
}
void printTruthTable(bool circuitoutput[8], string circuitName)
{
    cout << "Truth Table for " << circuitName << ":" << "\n";
    for (int i = 0; i < 8; ++i)
    {
        cout << truthTable[i][0] << " " << truthTable[i][1] << " " << truthTable[i][2] << " : " << circuitoutput[i] << "\n";
    }
}

bool check_equivalance(string OriginalcircuitExpression, string SimplifiedcircuitExpression)
{
    cout << "checking equivalance:-\n";
    bool A, B, C;                      // circuit inputs
    bool Original_Circuit_output[8];   // outputs of Original Circuit
    bool Simplified_Circuit_output[8]; // outputs of Simplified Circuit
    bool not_equivalent = false; // outputs of Simplified Circuit
    string temp1, temp2;
    // evaluating output of original and simplified circuit
    for (int i = 0; i < 8; ++i)
    {
        A = truthTable[i][0];
        B = truthTable[i][1];
        C = truthTable[i][2];
        temp1 = OriginalcircuitExpression;
        temp2 = SimplifiedcircuitExpression;
        substituteVariables(temp1, A, B, C);
        substituteVariables(temp2, A, B, C);
        Original_Circuit_output[i] = evaluateBooleanExpression(temp1);
        Simplified_Circuit_output[i] = evaluateBooleanExpression(temp2);
        if (Original_Circuit_output[i] != Simplified_Circuit_output[i])
        {
            not_equivalent = true;
        }
    }
    printTruthTable(Original_Circuit_output, "Original Circuit");
    printTruthTable(Simplified_Circuit_output, "Simplified Circuit");

    if (not_equivalent)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool check_Satisfiability(string OriginalcircuitExpression, string SimplifiedcircuitExpression)
{
    cout << "checking Satisfiability:-\n";
    bool A, B, C;                      // circuit inputs
    bool Original_Circuit_output[8];   // outputs of Original Circuit
    bool Simplified_Circuit_output[8]; // outputs of Simplified Circuit
    bool first_time = true;
    string temp1, temp2;
    // evaluating output of original and simplified circuit
    for (int i = 0; i < 8; ++i)
    {
        A = truthTable[i][0];
        B = truthTable[i][1];
        C = truthTable[i][2];
        temp1 = OriginalcircuitExpression;
        temp2 = SimplifiedcircuitExpression;
        substituteVariables(temp1, A, B, C);
        substituteVariables(temp2, A, B, C);
        Original_Circuit_output[i] = evaluateBooleanExpression(temp1);
        Simplified_Circuit_output[i] = evaluateBooleanExpression(temp2);

        if (Original_Circuit_output[i] == true && Simplified_Circuit_output[i] == true)
        {
            if (first_time)
            {
                cout << "Expressions are Satisfiable.\nSatisfiable inputs:-\nA B C\n";
                first_time = false;
            }
            cout << A << " " << B << " " << C << "\n";
        }
    }
    if (first_time)
    {
        cout << "Expressions are not Satisfiable\n";
        return false;
    }
    else
    {
        return true;
    }
}
bool check_tautology(string OriginalcircuitExpression, string SimplifiedcircuitExpression)
{
    cout << "checking tautology:-\n";
    bool A, B, C;                      // circuit inputs
    bool Original_Circuit_output[8];   // outputs of Original Circuit
    bool Simplified_Circuit_output[8]; // outputs of Simplified Circuit
    bool tautology = true;
    string temp1, temp2;
    // evaluating output of original and simplified circuit
    for (int i = 0; i < 8; ++i)
    {
        A = truthTable[i][0];
        B = truthTable[i][1];
        C = truthTable[i][2];
        temp1 = OriginalcircuitExpression;
        temp2 = SimplifiedcircuitExpression;
        substituteVariables(temp1, A, B, C);
        substituteVariables(temp2, A, B, C);
        Original_Circuit_output[i] = evaluateBooleanExpression(temp1);
        Simplified_Circuit_output[i] = evaluateBooleanExpression(temp2);

        if (!(Original_Circuit_output[i] == true && Simplified_Circuit_output[i] == true))
        {
            tautology = false;
        }
    }
    return tautology;
}
int main() {
    string OriginalcircuitExpression;
    string SimplifiedcircuitExpression;
    bool A, B, C;
    bool changed = false;
    cout << "Enter the Original circuit expression(e.g., ((!((A|!(B)))&(A&B))&C)):";
    getline(cin, OriginalcircuitExpression);
    cout << "Enter the Simplified circuit expression(e.g., (((!(A)&A)&B)&C)): ";
    getline(cin, SimplifiedcircuitExpression);
    if (check_equivalance(OriginalcircuitExpression, SimplifiedcircuitExpression))
    {
        cout << "Expressions are equivalent.\n";
    }
    else
    {
        cout << "Expressions are not equivalent.\n";
    }
    cout << "\n";

    //checking tautology
    if (check_tautology(OriginalcircuitExpression, SimplifiedcircuitExpression))
    {
        cout << "Expressions are tautology.\n";
    }
    else
    {
        cout << "Expressions are not tautology.\n";
    }
    cout << "\n";
    // ask user to change gate in circuit until reach satisfiable one
    while (!check_Satisfiability(OriginalcircuitExpression, SimplifiedcircuitExpression))
    {
        cout << "\nmodify a gate in the circuit please :-\n\n";
        cout << "Enter the Original modified circuit expression(e.g., ((!((A|!(B)))|(A&B))&C)  ):";
        getline(cin, OriginalcircuitExpression);
        cout << "Enter the Simplified modified circuit expression(e.g., (B&C) ): ";
        getline(cin, SimplifiedcircuitExpression);
        changed = true;
    }
    if (changed) {
        if (check_equivalance(OriginalcircuitExpression, SimplifiedcircuitExpression))
        {
            cout << "Expressions are equivalent.\n";
        }
        else
        {
            cout << "Expressions are not equivalent.\n";
        }
    }

    return 0;
}
