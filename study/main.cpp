#include <iostream>

#include "src_study/analyzer.h"
#include "src_study/test_plan.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        TestPlan plan(argv[1]);

        Analyzer analyzer(plan);

        analyzer.Analyze();
    }
    else
        cout << "Specify test plan file path" << endl;


    return 0;
}
