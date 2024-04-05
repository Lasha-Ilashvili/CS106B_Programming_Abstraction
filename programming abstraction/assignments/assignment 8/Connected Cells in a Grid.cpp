
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

bool inBounds(int row, int col, int numRows, int numCols) {
    return row > -1 && row < numRows && col > -1 && col < numCols;
} 

int findConnectedCellsNum(int row, int col, vector<vector<int>>& matrix, vector<vector<bool>>& visited, int n) {
    
    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            int newRow = row + x;
            int newCol = col + y;
            
            if(!inBounds(newRow, newCol, matrix.size(), matrix[0].size())
                || matrix[newRow][newCol] == 0 || visited[newRow][newCol]) {
                continue;
            }
            
            visited[newRow][newCol] = 1;
            n = findConnectedCellsNum(newRow, newCol, matrix, visited, n + 1);
        }
    }
    
    return n;
}

/*
 * Complete the 'connectedCell' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */

int connectedCell(vector<vector<int>> matrix) {
    vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size()));
    int max = 0;
    for(int row = 0; row < matrix.size(); row++) {
        for(int col = 0; col < matrix[row].size(); col++) {
            if(matrix[row][col] == 0) {
                continue;
            }
            visited[row][col] = 1;
            int n = findConnectedCellsNum(row, col, matrix, visited, 1);
            if(n > max) {
                max = n;
            }
        }
    }
    
    return max;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < m; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    int result = connectedCell(matrix);

    fout << result << "\n";

    fout.close();

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
 * 2. https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * C++11
 */