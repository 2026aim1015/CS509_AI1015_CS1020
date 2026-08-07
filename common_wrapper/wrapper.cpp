#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main()
{
    int assignment_choice;

    while(true)
    {
        cout<<"CS509 COMMON WRAPPER\n";
        cout<<"Available Assignments\n\n";
        cout<<"1. Assignment 01\n";
        cout<<"0. Exit\n\n";

        cout<<"Enter Assignment Number: ";
        cin>>assignment_choice;

        if(assignment_choice == 0)
        {
            cout<<"\nExiting Wrapper...\n";
            break;
        }

        if(assignment_choice != 1)
        {
            cout<<"\nInvalid Assignment!\n";
            continue;
        }

        int option;

        while(true)
        {
            
            cout<<"Assignment 01 : Graph Algorithms\n";
            cout<<"1. Run BFS\n";
            cout<<"2. Run DFS\n";
            cout<<"3. Run SSSP\n";
            cout<<"0. Back\n";

            cout<<"\nEnter Option: ";
            cin>>option;

            if(option == 0)
                break;

            string file;
            int test_no;
            int source;
            string command;

            switch(option)
            {
                case 1:
                {
                    cout<<"\nSelect BFS Test File\n";
                    cout<<"1. bfs_test_01.txt\n";
                    cout<<"2. bfs_test_02.txt\n";
                    cout<<"3. bfs_test_03.txt\n";

                    cout<<"Enter choice: ";
                    cin>>test_no;

                    file = "bfs_test_0" + to_string(test_no) + ".txt";

                    cout<<"Enter source vertex: ";
                    cin>>source;

                    command =
                    "cmd /c \"cd assignment_01 && bfs.exe tests/" +
                    file + " " + to_string(source) + "\"";

                    system(command.c_str());
                    break;
                }

                case 2:
                {
                    cout<<"\nSelect DFS Test File\n";
                    cout<<"1. dfs_test_01.txt\n";
                    cout<<"2. dfs_test_02.txt\n";
                    cout<<"3. dfs_test_03.txt\n";

                    cout<<"Enter choice: ";
                    cin>>test_no;

                    file="dfs_test_0" + to_string(test_no) + ".txt";

                    cout<<"Enter source vertex: ";
                    cin>>source;

                    command ="cmd /c \"cd assignment_01 && dfs.exe tests/" +file + " " + to_string(source) + "\"";

                    system(command.c_str());
                    break;
                }

                case 3:
                {
                    cout<<"\nSelect SSSP Test File\n";
                    cout<<"1. sssp_test_01.txt\n";
                    cout<<"2. sssp_test_02.txt\n";
                    cout<<"3. sssp_test_03.txt\n";

                    cout<<"Enter choice: ";
                    cin>>test_no;

                    file ="sssp_test_0" + to_string(test_no) + ".txt";

                    cout<<"Enter source vertex: ";
                    cin>>source;

                    command ="cmd /c \"cd assignment_01 && sssp.exe tests/" +file + " " + to_string(source) + "\"";

                    system(command.c_str());
                    break;
                }

                default:
                    cout<<"\nInvalid Option!\n";
            }
        }
    }

    return 0;
}