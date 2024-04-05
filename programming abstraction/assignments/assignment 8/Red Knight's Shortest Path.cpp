
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct Cell {
    pair<int, int> loc;
    string s;
    Cell* parent;
    Cell() {}
    
    Cell(pair<int, int> loc, string s = "") {
        this->loc = loc;
        this->s = s;
        parent = NULL;
    }
};

const pair<int, int> UL = make_pair(-2, -1);
const pair<int, int> UR = make_pair(-2,  1);
const pair<int, int> R  = make_pair( 0,  2);
const pair<int, int> LR = make_pair( 2,  1);
const pair<int, int> LL = make_pair( 2, -1);
const pair<int, int> L  = make_pair( 0, -2);

string toString(pair<int, int> direction) {
    if (direction == UL) {
        return "UL";
    }
    if (direction == UR) {
        return "UR";
    }
    if (direction == R) {
        return "R";
    }
    if (direction == LR) {
        return "LR";
    }
    if (direction == LL) {
        return "LL";
    }
    if (direction == L) {
        return "L";
    }
    return "";
}

bool inBounds(int row, int col, int size) {
    return row > -1 && row < size && col > -1 && col < size;
}

vector<Cell*> getNeighbors(Cell* curr, vector<vector<bool>>& visited, vector<pair<int, int>>& directions) {
    vector<Cell*> neighbors;
    
    for (pair<int, int> direction : directions) {
        int row = curr->loc.first + direction.first;
        int col = curr->loc.second + direction.second;
        
        if (inBounds(row, col, visited.size()) && !visited[row][col]) {
            visited[row][col] = 1;
            Cell* neighbor = new Cell(make_pair(row, col), toString(direction));
            neighbor->parent = curr;
            neighbors.push_back(neighbor);
        }
    }
    
    return neighbors;
}

void getPath(Cell* curr, string& path, int& num) {
    while (curr->parent != NULL) {
        path = curr->s + " " + path;
        curr = curr->parent;
        num++;
    }
}

string shortestPath(queue<Cell*>& q, vector<vector<bool>>& visited, pair<int, int> end, vector<pair<int, int>>& directions) {
    while (!q.empty()) {
        Cell* curr = q.front();
        q.pop();
        
        visited[curr->loc.first][curr->loc.second] = 1;
        
        if (curr->loc == end) {
            string path = "";
            int num = 0;
            getPath(curr, path, num);
            cout << num << endl;
            return path;
        }
        
        for (Cell* neighbor : getNeighbors(curr, visited, directions)) {
            q.push(neighbor);
        }
    }
    
    return "Impossible";
}

/*
 * Complete the 'printShortestPath' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER i_start
 *  3. INTEGER j_start
 *  4. INTEGER i_end
 *  5. INTEGER j_end
 */

void printShortestPath(int n, int i_start, int j_start, int i_end, int j_end) {
    vector<pair<int, int>> directions = {UL, UR, R, LR, LL, L};
    vector<vector<bool>> visited(n, vector<bool>(n));
    queue<Cell*> q;
    q.push(new Cell(make_pair(i_start, j_start)));
    cout << shortestPath(q, visited, make_pair(i_end, j_end), directions) << endl;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int i_start = stoi(first_multiple_input[0]);

    int j_start = stoi(first_multiple_input[1]);

    int i_end = stoi(first_multiple_input[2]);

    int j_end = stoi(first_multiple_input[3]);

    printShortestPath(n, i_start, j_start, i_end, j_end);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}


/* Search
 * 4. https://www.hackerrank.com/challenges/red-knights-shortest-path/problem
 * C++11
 */