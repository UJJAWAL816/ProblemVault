#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>

using namespace std;

struct Problem {

    Problem(); // Default constructor

    Problem(const string& title, const string& platform, const string& tags, const string& status);
    string getTitle() const;
    string getPlatform() const;
    vector<string> getTags() const;
    string getStatus() const;


    int id;
    string title;
    string platform;
    vector<string> tags;
    string status; // "solved" or "unsolved"
    string notes;

    void display() const; // Print problem info
    void setStatus(const std::string& newStatus);

    string serialize() const;
    static Problem deserialize(const string& line);

};

vector<string> split(const string &s, char delim);
string join(const vector<string> &v, const string &delim);

#endif
