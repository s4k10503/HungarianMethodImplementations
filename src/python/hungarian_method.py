import numpy as np


def hungarian_method(cost_matrix):
    N = cost_matrix.shape[0]

    # Subtract the smallest value from each row and column
    cost_matrix -= cost_matrix.min(axis=1, keepdims=True)
    cost_matrix -= cost_matrix.min(axis=0)

    while True:
        marked_zeros = np.zeros_like(cost_matrix, dtype=bool)
        row_marked = np.zeros(N, dtype=bool)
        col_marked = np.zeros(N, dtype=bool)

        # Finding all zero positions in the matrix
        zero_rows, zero_cols = np.where(cost_matrix == 0)

        # Looping through unique rows containing zeros
        for i in np.unique(zero_rows):
            unmarked_zero_cols = zero_cols[(zero_rows == i) & ~col_marked[zero_cols]]
            if unmarked_zero_cols.size > 0:
                j = unmarked_zero_cols[0]
                marked_zeros[i, j] = True
                row_marked[i] = True
                col_marked[j] = True

        # Check if we found enough zeros
        if marked_zeros.sum() == N:
            break

        # Find lines that cover zeros
        covered_mask = np.zeros_like(cost_matrix, dtype=bool)
        covered_mask[row_marked, :] = True
        covered_mask[:, col_marked] = True

        # Find the smallest value not covered by a line
        min_val = np.min(cost_matrix[~covered_mask])

        # Subtract min_val from all uncovered elements and add it to all doubly covered elements
        cost_matrix[~covered_mask] -= min_val
        cost_matrix[(covered_mask.sum(axis=0) + covered_mask.sum(axis=1)[:, None]) == 2] += min_val

    # Find the assignment from the marked zeros
    assignment = list(zip(*np.where(marked_zeros)))
    return assignment