#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::pair<int, int>> hungarian_method(std::vector<std::vector<int>> cost_matrix) {
    int N = cost_matrix.size();
    std::vector<std::pair<int, int>> assignment;
    std::vector<std::vector<bool>> marked_zeros(N, std::vector<bool>(N, false));
    
    // Subtract the smallest value from each row
    for (int i = 0; i < N; ++i) {
        int min_val_row = *std::min_element(cost_matrix[i].begin(), cost_matrix[i].end());
        for (int j = 0; j < N; ++j) {
            cost_matrix[i][j] -= min_val_row;
        }
    }

    // Subtract the smallest value from each column
    for (int j = 0; j < N; ++j) {
        int min_val_col = std::numeric_limits<int>::max();
        for (int i = 0; i < N; ++i) {
            min_val_col = std::min(min_val_col, cost_matrix[i][j]);
        }
        for (int i = 0; i < N; ++i) {
            cost_matrix[i][j] -= min_val_col;
        }
    }

    while (true) {
        // Reset marked zeros
        for (int i = 0; i < N; ++i) {
            std::fill(marked_zeros[i].begin(), marked_zeros[i].end(), false);
        }
        std::vector<bool> row_marked(N, false);
        std::vector<bool> col_marked(N, false);

        // Marking zeros
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (cost_matrix[i][j] == 0 && !row_marked[i] && !col_marked[j]) {
                    marked_zeros[i][j] = true;
                    row_marked[i] = true;
                    col_marked[j] = true;
                }
            }
        }

        // Check if enough zeros are marked
        if (std::all_of(row_marked.begin(), row_marked.end(), [](bool v) { return v; }) &&
            std::all_of(col_marked.begin(), col_marked.end(), [](bool v) { return v; })) {
            break;
        }

        // Find lines that cover zeros
        std::vector<bool> covered_rows(N, true);
        for (int i = 0; i < N; ++i) {
            covered_rows[i] = !row_marked[i];
        }
        std::vector<bool> covered_cols = col_marked;

        while (true) {
            std::vector<bool> new_covered_rows = covered_rows;
            std::vector<bool> new_covered_cols = covered_cols;

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (cost_matrix[i][j] == 0 && covered_rows[i] && !covered_cols[j]) {
                        new_covered_rows[i] = false;
                        new_covered_cols[j] = true;
                    }
                }
            }

            if (new_covered_rows == covered_rows && new_covered_cols == covered_cols) {
                break;
            }

            covered_rows = new_covered_rows;
            covered_cols = new_covered_cols;
        }

        // Find the smallest value not covered by a line
        int min_val = std::numeric_limits<int>::max();
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (!covered_rows[i] && !covered_cols[j]) {
                    min_val = std::min(min_val, cost_matrix[i][j]);
                }
            }
        }

        // Subtract min_val from all uncovered elements and add it to all doubly covered elements
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (!covered_rows[i] && !covered_cols[j]) {
                    cost_matrix[i][j] -= min_val;
                }
                if (!covered_rows[i] && covered_cols[j]) {
                    cost_matrix[i][j] += min_val;
                }
            }
        }
    }

    // Find the assignment from the marked zeros
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (marked_zeros[i][j]) {
                assignment.push_back({i, j});
            }
        }
    }

    return assignment;
}
