#include <bits/stdc++.h>


using namespace std;

class Process {
private:
    string name;
    int pid;
    double memoryUsage;

public:
    Process(string name, int pid, double memoryUsage) {
        this->name = name;
        this->pid = pid;
        this->memoryUsage = memoryUsage;
    }

    // Getter functions
    string getName() const { return name; }
    int getPid() const { return pid; }
    double getMemoryUsage() const { return memoryUsage; }
};

class Processes {
private:
    vector<Process> processes;

public:
    // Load processes by executing tasklist and parsing the output
    void loadProcesses() {
        // Run the tasklist command and output to a text file
        system("tasklist > usedfile.txt");

        ifstream file("usedfile.txt");
        if (!file.is_open()) {
            cerr << "Failed to open usedfile.txt" << endl;
            return;
        }

        string line;
        bool skipHeader = true;

        // Read the file line by line
        while (getline(file, line)) {
            // Skip the header line
            if (skipHeader) {
                if (line.find("Image Name") != string::npos) {
                    skipHeader = false; // Start reading process data
                }
                continue;
            }

            // Parse the line for process details (name, pid, memory usage)
            istringstream iss(line);
            string name, sessionName, memUsageStr;
            int pid, sessionNumber;

            if (!(iss >> name >> pid >> sessionName >> sessionNumber >> memUsageStr)) {
                continue; // Skip invalid lines
            }

            // Remove commas and 'K' from the memory usage string, then convert to double
            memUsageStr.erase(remove(memUsageStr.begin(), memUsageStr.end(), ','), memUsageStr.end());
            memUsageStr.pop_back(); // Remove 'K'
            double memUsage = stod(memUsageStr); // Convert KB to MB

            // Create a Process object and add it to the vector
            processes.emplace_back(name, pid, memUsage);
        }

        file.close();
    }

    // Display all processes
    void displayProcesses() {
        // Print header in the format of the tasklist command
        cout << left << setw(30) << "Image Name"
             << setw(10) << "PID"
             << setw(20) << "Session Name"
             << setw(10) << "Session#"
             << setw(15) << "Mem Usage" << endl;

        cout << "============================== ======== ==================== ======== ==============" << endl;

        // Print each process in the same format
        for (const auto& process : processes) {
            string memUsageStr = to_string(static_cast<int>(process.getMemoryUsage()*11));
            if(memUsageStr.length()>3) {
                memUsageStr.insert(memUsageStr.length() - 3, ",");
                if (memUsageStr.length()==8) {
                    memUsageStr.insert(memUsageStr.length() - 7, ","); // Add commas for readability
                }

            }
            else {
                memUsageStr.insert(memUsageStr.length() - 2, ",");
                memUsageStr.insert(memUsageStr.length() , "0");
            }
            // Print process details
            cout << left << setw(30) << process.getName()
                 << setw(10) << process.getPid()
                 << setw(20) << "Console"  // Assuming "Console" for session name
                 << setw(10) << 1        // Assuming session# is 1
                 << setw(15) << memUsageStr + " K" << endl;
        }
    }

    // Sort processes by name
    void sortByName() {
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            return a.getName() < b.getName();
        });
    }

    // Sort processes by PID
    void sortByPid() {
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            return a.getPid() < b.getPid();
        });
    }

    // Sort processes by memory usage
    void sortByMemoryUsage() {
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            return a.getMemoryUsage() < b.getMemoryUsage();
        });
    }
};

int main() {
    while (true) {
        string choice, choice2;
        cout << "\n1) Sort by name\n2) Sort by PID\n3) Sort by Memusage\n4) Exit" << endl;
        cout << "Enter choice:";
        cin >> choice;
        Processes processes;
        processes.loadProcesses();
        if (choice == "1") {
            processes.sortByName();
            processes.displayProcesses();

        } else if (choice == "2") {
            processes.sortByPid();
            processes.displayProcesses();

        } else if (choice == "3") {
            processes.sortByMemoryUsage();
            processes.displayProcesses();
        } else if (choice == "4") {
            return 0;
        }
        cout<<"\nEnter any key to try Again\nor\nEnter 2 to Exit\n";
        cin >> choice2;
        if (choice == "2") {
            return 0;
        }

    }
    return 0;
}
