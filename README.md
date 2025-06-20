# 📘 ProblemVault (C++ CLI)

A Command-Line Interface (CLI) tool built in C++ to efficiently store and track your **most valuable Competitive Programming problems** — add notes, view stats, search by tags/platforms, and store everything persistently in a text file.

---

## ✨ Features

- ✅ Add, list, update, and delete problems
- 🎯 Mark problems as **solved** or **unsolved**
- 🔍 Search by **title**, **platform**, or **tags**
- 📊 View progress (solved vs. unsolved) with visual bar
- 📈 See detailed **stats by platform** and **tag**
- 🔃 Sort problems by **title**, **platform**, or **status**
- 💾 Persistent file storage using `problem.txt`

---

## 📂 File Structure
ProblemVault/
├── main.cpp
├── CPProblemManager.cpp
├── CPProblemManager.h
├── Problem.cpp
├── Problem.h
├── problem.txt
├── README.md
└── .gitignore


---

## ⚙️ How to Compile and Run

Make sure you're inside the `ProblemVault` directory.

### 🖥️ Compile:
```bash
g++ main.cpp CPProblemManager.cpp Problem.cpp -o problemvault
▶️ Run:
./problemvault

---


🗂 Sample Data Format (problem.txt)
Each line is saved as:
ID|Title|Platform|Status|Notes|Tag1,Tag2,...

Example:
1|Two Sum|Leetcode|solved|Use hashmap|Array
2|Three Sum|Leetcode|solved|Two pointers approach|Array
3|Above The Clouds|Codeforces|unsolved|Wrote wrong logic in contest|String

---

💡 Sample CLI Commands

> add
> list
> search
> mark
> update
> delete
> stats
> progress
> sort
> exit

---

📊 Sample Output

📈 Progress View:
=== Progress ===
Total Problems:   5
Solved:           3
Unsolved:         2
Completion:       60% [##########--------]

🧠 Stats View:
Choose stats to display:
1. Total problems
2. Solved count
3. Unsolved count
4. Count by platform
5. Count by tag
Enter your choices (space-separated): 2 4 5

Solved Problems: 3

Problems by Platform:
 - Leetcode: 2
 - Codeforces: 1

Problems by Tag:
 - Array: 2
 - String: 1

---

📌 Requirements
C++11 or above

Compatible with g++, clang++, etc.

---

🙋‍♂️ Author
Ujjawal Mishra
B.Tech, IIT Delhi
Built during summer break after second semester to organize CP journey effectively.

---

🛡 License
This project is open-source and available under the MIT License.




