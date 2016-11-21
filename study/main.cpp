#include <iostream>

#include "src_study/analyzer.h"
#include "src_study/test_plan.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc >= 3)
    {
        TestPlan plan(argv[1]);

        Analyzer analyzer(plan);

        cout << "Input read" << endl;

        analyzer.Analyze();

        cout << "Analyzing" << endl;

        analyzer.OutputToFile(argv[2]);

        cout << "Write to file" << endl << "Finished";
    }
    else
        if (argc == 2)
            cout << "Specify output file path" << endl;
        else
            cout << "Specify input file path" << endl;


    return 0;
}
