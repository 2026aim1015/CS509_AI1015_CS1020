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
        cout<<"2. Assignment 02\n";
        cout<<"0. Exit\n\n";

        cout<<"Enter Assignment Number: ";
        cin>>assignment_choice;

        if(assignment_choice == 0)
        {
            cout<<"\nExiting Wrapper...\n";
            break;
        }

        if(assignment_choice != 1 && assignment_choice != 2)
        {
            cout<<"\nInvalid Assignment!\n";
            continue;
        }

        int option;
        if(assignment_choice==1)
        {
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
    if(assignment_choice == 2)
        {
            int option;

            while(true)
            {
                cout << "\nAssignment 02 : Graph Algorithms\n";
                cout << "1. Triangle Counting\n";
                cout << "2. Betweenness Centrality\n";
                cout << "3. Connected Components\n";
                cout << "0. Back\n";

                cout << "\nEnter Option: ";
                cin >> option;

                if(option == 0)
                    break;

                int test_no;
                string file;
                string command;

                switch(option)
                {
                    case 1:
                    {
                        cout << "\nSelect Triangle Test File\n";
                        cout << "1. tc_10.txt\n";
                        cout << "2. tc_100.txt\n";
                        cout << "3. tc_10000.txt\n";
                        cout << "4. tc_50000.txt\n";
                        cout << "5. tc_100000.txt\n";

                        cout << "Enter choice: ";
                        cin >> test_no;

                        if(test_no < 1 || test_no > 5)
                        {
                            cout << "Invalid test number!\n";
                            break;
                        }

                        string tests[] =
                        {
                            "tc_10.txt",
                            "tc_100.txt",
                            "tc_10000.txt",
                            "tc_50000.txt",
                            "tc_100000.txt"
                        };

                        file = tests[test_no - 1];

                        command =
                            "cmd /c \"cd assignment_02 && triangle_test tests/triangle/" +
                            file + "\"";

                        system(command.c_str());
                        break;
                    }

                    case 2:
                    {
                        cout << "\nSelect Betweenness Centrality Test File\n";
                        cout << "1. bc_10.txt\n";
                        cout << "2. bc_100.txt\n";
                        cout << "3. bc_1000.txt\n";
                        cout << "4. bc_5000.txt\n";
                        cout << "5. bc_10000.txt\n";

                        cout << "Enter choice: ";
                        cin >> test_no;

                        if(test_no < 1 || test_no > 5)
                        {
                            cout << "Invalid test number!\n";
                            break;
                        }

                        string tests[] =
                        {
                            "bc_10.txt",
                            "bc_100.txt",
                            "bc_1000.txt",
                            "bc_5000.txt",
                            "bc_10000.txt"
                        };

                        file = tests[test_no - 1];

                        command =
                            "cmd /c \"cd assignment_02 && bc_test tests/betweenness_centrality/" +
                            file + "\"";

                        system(command.c_str());
                        break;
                    }

                    case 3:
                    {
                        cout << "\nSelect Connected Components Test File\n";
                        cout << "1. cc_10.txt\n";
                        cout << "2. cc_100.txt\n";
                        cout << "3. cc_10000.txt\n";
                        cout << "4. cc_50000.txt\n";
                        cout << "5. cc_100000.txt\n";

                        cout << "Enter choice: ";
                        cin >> test_no;

                        if(test_no < 1 || test_no > 5)
                        {
                            cout << "Invalid test number!\n";
                            break;
                        }

                        string tests[] =
                        {
                            "cc_10.txt",
                            "cc_100.txt",
                            "cc_10000.txt",
                            "cc_50000.txt",
                            "cc_100000.txt"
                        };

                        file = tests[test_no - 1];

                        command =
                            "cmd /c \"cd assignment_02 && cc_test tests/connected_components/" +
                            file + "\"";

                        system(command.c_str());
                        break;
                    }

                    default:
                        cout << "\nInvalid Option!\n";
                }
            }
        }
    }

    return 0;
}