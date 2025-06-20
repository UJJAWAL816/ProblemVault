#include "CPProblemManager.h"
#include "Problem.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <limits>
#include <map>
#include <set>

string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

CPProblemManager::CPProblemManager() {
    nextId = 1;
}

void CPProblemManager::runCLI() {
    loadFromFile("problems.txt"); 
    cout << "=== CP Problem Manager ===\n";
    while (true) {
        cout << "=== CP Problem Manager ===\n";
        cout << "Available commands:\n";
        cout << "1.  add       (Add a new problem)\n";
        cout << "2.  list      (List all problems)\n";
        cout << "3.  mark      (Mark problem as solved/unsolved)\n";
        cout << "4.  update    (Update a problem by ID)\n";
        cout << "5.  search    (Search problems by title/platform/tag)\n";
        cout << "6.  delete    (Delete a problem by title)\n";
        cout << "7.  progress  (Show solved/unsolved stats)\n";
        cout << "8.  stats     (Detailed platform-wise stats)\n";
        cout << "9.  sort      (Sort problems by title/platform/status)\n";
        cout << "10. exit      (Save and exit)\n";

        cout << "\n> ";
        string command;
        getline(cin, command);

        if (command == "add") {
            addProblem();
        } else if (command == "list") {
            listProblems();
        } else if (command == "mark") {
            string input;
            int id;
            string status;

            cout << "Enter Problem ID to mark: ";
            getline(cin, input);
            istringstream(input) >> id;

            cout << "Enter new status (solved/unsolved): ";
            getline(cin, status);

            markProblem(id, status);
        } else if (command == "search") {
            string type, keyword;

            cout << "Search by (title/platform/tag): ";
            getline(cin, type);

            cout << "Enter keyword: ";
            getline(cin, keyword);

            searchProblems(type, keyword);
        } else if (command == "delete") {
            string title;
            cout << "Enter the title of the problem to delete: ";
            getline(cin, title);
            deleteProblem(title);
        } else if (command == "progress") {
            showProgress();
        
        }else if (command == "update") {
            int id;
            cout<<"Enter the Id : ";
            cin >> id;
            cin.ignore();
            updateProblem(id); 
        } else if (command == "stats") {
            showStats();
        }else if (command == "sort") {
            sortProblems();
        }else if (command == "exit") {
            saveToFile("problems.txt");
            cout << "Progress saved. Goodbye!\n";
            break;
        } else {
            cout << "Invalid command. Try again.\n";
        }
    }
}

void CPProblemManager::addProblem() {
    Problem p;
    p.id = nextId++;

    cout << "Enter title: ";
    getline(cin, p.title);

    cout << "Enter platform (e.g., LeetCode, Codeforces): ";
    getline(cin, p.platform);

    cout << "Enter tags (space-separated): ";
    string tagLine;
    getline(cin, tagLine);
    p.tags.clear();
    string tag;
    istringstream tagStream(tagLine);
    while (tagStream >> tag) {
        p.tags.push_back(tag);
    }

    cout << "Enter status (solved/unsolved): ";
    getline(cin, p.status);

    cout << "Enter notes: ";
    getline(cin, p.notes);

    problems.push_back(p);
    cout << "Problem added!\n";
}

void CPProblemManager::addProblem(const Problem& p) {
    problems.push_back(p);
}

void CPProblemManager::listProblems() {
    if (problems.empty()) {
        cout << "No problems added yet.\n";
        return;
    }

    for (const auto& p : problems) {
        p.display();
        cout << "------------------------\n";
    }
}

void CPProblemManager::markProblem(int id, const string& newStatus) {
    for (Problem& p : problems) {
        if (p.id == id) {
            p.setStatus(newStatus);
            cout << "Status updated.\n";
            return;
        }
    }
    cout << "Problem not found.\n";
}

void CPProblemManager::deleteProblem(const std::string& title) {
    for (auto it = problems.begin(); it != problems.end(); ++it) {
        if (it->getTitle() == title) {
            problems.erase(it);
            std::cout << "Problem deleted.\n";
            return;
        }
    }
    std::cout << "Problem not found.\n";
}

void CPProblemManager::searchProblems(const string& type, const string& keyword) {
    string lowerKeyword = toLower(keyword);
    bool found = false;

    for (const Problem& p : problems) {
        if (type == "title") {
            if (toLower(p.getTitle()).find(lowerKeyword) != string::npos) {
                p.display();
                cout << "------------------------\n";
                found = true;
            }
        } else if (type == "platform") {
            if (toLower(p.getPlatform()).find(lowerKeyword) != string::npos) {
                p.display();
                cout << "------------------------\n";
                found = true;
            }
        } else if (type == "tag") {
            for (const string& tag : p.getTags()) {
                if (toLower(tag).find(lowerKeyword) != string::npos) {
                    p.display();
                    cout << "------------------------\n";
                    found = true;
                    break;
                }
            }
        } else {
            cout << "Invalid search type. Use title, platform, or tag.\n";
            return;
        }
    }

    if (!found) {
        cout << "No matching problems found.\n";
    }
}

void CPProblemManager::saveToFile(const string& filename) const {
    ofstream out(filename);
    if (!out) {
        cout << "[Error] Could not open " << filename << " for writing.\n";
        return;
    }

    for (const auto& p : problems) {
        out << p.serialize() << "\n";
    }
    out.close();
    cout << "All problems saved to \"" << filename << "\".\n";
}


void CPProblemManager::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "[Warning] Couldn't open " << filename << " for reading. Starting fresh.\n";
        return;
    }

    string line;
    int lineNumber = 0;
    while (getline(in, line)) {
        lineNumber++;
        try {
            if (line.empty()) continue;
            Problem p = Problem::deserialize(line);
            problems.push_back(p);
            nextId = max(nextId, p.id + 1);
        } catch (...) {
            cout << "[Error] Failed to load problem from line " << lineNumber << ". Skipping.\n";
        }
    }
    in.close();
}


void CPProblemManager::showProgress() const {
    int total = problems.size();
    int solved = 0;
    for (const auto& p : problems) {
        if (toLower(p.getStatus()) == "solved") {
            solved++;
        }
    }
    int unsolved = total - solved;
    double percent = (total > 0) ? (100.0 * solved / total) : 0;

    cout << "=== Progress ===\n";
    cout << "Total Problems:   " << total << "\n";
    cout << "Solved:           " << solved << "\n";
    cout << "Unsolved:         " << unsolved << "\n";
    cout << "Completion:       " << percent << "%\n";

    cout << "[";
    int bars = static_cast<int>(percent / 5); // 20 bars = 100%
    for (int i = 0; i < 20; i++) {
        cout << (i < bars ? "#" : "-");
    }
    cout << "]\n";
}


void CPProblemManager::updateProblem(int id) {
    if (id <= 0 || id > problems.size()) {
        cout << "Invalid problem ID.\n";
        return;
    }

    Problem& p = problems[id - 1];
    int choice;
    string input;

    while (true) {
        cout << "\nWhat do you want to update?\n";
        cout << "1. Title\n";
        cout << "2. Platform\n";
        cout << "3. Tags\n";
        cout << "4. Status\n";
        cout << "5. Notes\n";
        cout << "0. Done\n";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush newline

        if (choice == 0) break;

        switch (choice) {
            case 1:
                cout << "Enter new title: ";
                getline(cin, input);
                p.title = input;
                break;
            case 2:
                cout << "Enter new platform: ";
                getline(cin, input);
                p.platform = input;
                break;
            case 3:
                cout << "Enter new tags (comma-separated): ";
                getline(cin, input);
                p.tags = split(input, ',');
                break;
            case 4:
                cout << "Enter new status (solved/unsolved): ";
                getline(cin, input);
                p.status = input;
                break;
            case 5:
                cout << "Enter new notes: ";
                getline(cin, input);
                p.notes = input;
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    cout << "✅ Problem updated successfully!\n";
}

void CPProblemManager::showStats() const {
    std::cout << "Choose stats to display:\n";
    std::cout << "1. Total problems\n";
    std::cout << "2. Solved count\n";
    std::cout << "3. Unsolved count\n";
    std::cout << "4. Count by platform\n";
    std::cout << "5. Count by tag\n";
    std::cout << "Enter your choices (space-separated): ";

    std::string line;
    std::getline(std::cin >> std::ws, line);
    std::istringstream iss(line);
    std::set<int> choices;
    int choice;
    while (iss >> choice) choices.insert(choice);

    if (choices.count(1)) std::cout << "Total Problems: " << problems.size() << "\n";
    if (choices.count(2) || choices.count(3)) {
        int solved = 0, unsolved = 0;
        for (const auto& p : problems) {
            if (p.status == "solved") solved++;
            else unsolved++;
        }
        if (choices.count(2)) std::cout << "Solved Problems: " << solved << "\n";
        if (choices.count(3)) std::cout << "Unsolved Problems: " << unsolved << "\n";
    }
    if (choices.count(4)) {
        std::map<std::string, int> platformCount;
        for (const auto& p : problems) platformCount[p.platform]++;
        std::cout << "Problems by Platform:\n";
        for (auto& entry : platformCount) {
            std::cout << " - " << entry.first << ": " << entry.second << "\n";
        }
    }
    if (choices.count(5)) {
        std::map<std::string, int> tagCount;
        for (const auto& p : problems) {
            for (const auto& tag : p.tags) tagCount[tag]++;
        }
        std::cout << "Problems by Tag:\n";
        for (auto& entry : tagCount) {
            std::cout << " - " << entry.first << ": " << entry.second << "\n";
        }
    }
}


void CPProblemManager::sortProblems() {
    if (problems.empty()) {
        cout << "No problems to sort.\n";
        return;
    }

    int choice;
    cout << "\nSort by:\n";
    cout << "1. Title\n";
    cout << "2. Platform\n";
    cout << "3. Status\n";
    cout << "0. Cancel\n> ";
    cin >> choice;
    cin.ignore();

    if (choice == 0) return;

    switch (choice) {
        case 1:
            sort(problems.begin(), problems.end(), [](const Problem& a, const Problem& b) {
                return toLower(a.getTitle()) < toLower(b.getTitle());
            });
            cout << "\n=== Problems (Sorted by Title) ===\n";
            break;
        case 2:
            sort(problems.begin(), problems.end(), [](const Problem& a, const Problem& b) {
                return toLower(a.getPlatform()) < toLower(b.getPlatform());
            });
            cout << "\n=== Problems (Sorted by Platform) ===\n";
            break;
        case 3:
            sort(problems.begin(), problems.end(), [](const Problem& a, const Problem& b) {
                return toLower(a.getStatus()) < toLower(b.getStatus());
            });
            cout << "\n=== Problems (Sorted by Status) ===\n";
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    for (const auto& p : problems) {
        p.display();
        cout << "------------------------\n";
    }
}


