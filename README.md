
# Multi-Language Hungarian Method Implementations

This repository contains implementations of the Hungarian Method (an algorithm for solving the assignment problem) in multiple programming languages.  
Currently, the following languages are supported:

- Python
- C++

Each implementation can be found in the respective directory under `src/`.

## Python Implementation

The Python implementation can be found in the `src/python` directory.

### Dependencies

The Python implementation uses the following libraries:

- [numpy](https://numpy.org/) (BSD License)

### Usage

```python
from hungarian_method import hungarian_method
import numpy as np

# Cost matrix
cost_matrix = np.array([
    [4, 3, 2],
    [1, 5, 3],
    [2, 4, 1]
])

# Find the optimal assignment
assignment = hungarian_method(cost_matrix)

# The result is a list of tuples representing the assigned rows and columns
print(assignment)  # [(0, 1), (1, 0), (2, 2)]
```

## C++ Implementation

The C++ implementation can be found in the `src/cpp` directory.

### Dependencies

The C++ implementation does not use any specific libraries.

### Usage

```cpp
#include "HungarianMethod.h"
#include <vector>

int main() {
    // Cost matrix
    std::vector<std::vector<int>> cost_matrix = {
        {4, 3, 2},
        {1, 5, 3},
        {2, 4, 1}
    };

    // Find the optimal assignment
    std::vector<std::pair<int, int>> result = hungarian_method(cost_matrix);
    
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "(" << result[i].first << ", " << result[i].second << ")";
        if (i < result.size() - 1) {
            std::cout << ", ";
        }
    }
    // The result is a list of tuples representing the assigned rows and columns
    std::cout << "]\n";  // [(0, 1), (1, 0), (2, 2)]

    return 0;
}
```
