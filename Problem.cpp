#include "Problem.h"
#include <iostream>
#include <sstream>

Problem::Problem() {
    id = -1;
    title = "";
    platform = "";
    tags = {};
    status = "";
    notes = "";
}


Problem::Problem(const string& title, const string& platform, const string& tagsStr, const string& status) {
    this->title = title;
    this->platform = platform;
    this->status = status;
    id = -1;
    notes = "";

    // Split tagsStr by spaces into vector<string>
    istringstream iss(tagsStr);
    string tag;
    while (iss >> tag) {
        tags.push_back(tag);
    }
}

string Problem::getTitle() const {
    return title;
}
string Problem::getPlatform() const {
    return platform;
}

vector<string> Problem::getTags() const {
    return tags;
}

string Problem::getStatus() const {
    return status;
}

void Problem::display() const {
    cout << "ID: " << id << "\n";
    cout << "Title: " << title << "\n";
    cout << "Platform: " << platform << "\n";
    cout << "Tags: ";
    for (const string& tag : tags) {
        cout << tag << " ";
    }
    cout << "\nStatus: " << status << "\n";
    cout << "Notes: " << notes << "\n";
}

void Problem::setStatus(const string& newStatus) {
    status = newStatus;
}

string Problem::serialize() const {
    string serialized = to_string(id) + "|" + title + "|" + platform + "|" + status + "|" + notes + "|";
    for (const string& tag : tags) {
        serialized += tag + ",";
    }
    return serialized;
}

Problem Problem::deserialize(const string& line) {
    Problem p;
    stringstream ss(line);
    string part;

    try {
        // ID
        getline(ss, part, '|');
        if (part.empty()) throw runtime_error("Missing ID");
        p.id = stoi(part);

        // Title
        getline(ss, p.title, '|');
        if (p.title.empty()) throw runtime_error("Missing Title");

        // Platform
        getline(ss, p.platform, '|');
        if (p.platform.empty()) throw runtime_error("Missing Platform");

        // Status
        getline(ss, p.status, '|');
        if (p.status != "solved" && p.status != "unsolved")
            throw runtime_error("Invalid status");

        // Notes
        getline(ss, p.notes, '|');

        // Tags
        getline(ss, part, '|');
        stringstream tagStream(part);
        string tag;
        while (getline(tagStream, tag, ',')) {
            if (!tag.empty())
                p.tags.push_back(tag);
        }
    } catch (...) {
        throw; // Let caller handle error and skip the line
    }

    return p;
}


vector<string> split(const string &s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);
        result.push_back(item);
    }
    return result;
}

string join(const vector<string> &v, const string &delim) {
    string result;
    for (int i = 0; i < v.size(); ++i) {
        result += v[i];
        if (i != v.size() - 1) result += delim;
    }
    return result;
}



