#ifndef CPTRACKER_H
#define CPTRACKER_H

#include "Problem.h"
#include <vector>
#include <string>

using namespace std;

class CPProblemManager {
private:
    vector<Problem> problems;
    int nextId;
    
public:
    CPProblemManager();

    void runCLI();

    void addProblem();
    void addProblem(const Problem& problem);
    void listProblems();

    
    void deleteProblem(const std::string& title);
    void markProblem(int id, const string& newStatus);
    void searchProblems(const std::string& type, const std::string& keyword);
    
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);

    void showProgress() const;
    void updateProblem(int id);
    void showStats() const;
    void sortProblems();

};

#endif
