class Solution {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		int rows = matrix.size();
		int cols = matrix[0].size();

		//
		// Just walk over matrix and set
		// matrix[0][i] = 0 or
		// matrix[i][0] = 0 to mark if we
		// need to zero the column or row.
		//
		// Since matrix[x][0] and matrix[0][x]
		// may have zeros itself we need an
		// additional variables.

		bool clear_col0 = false;
		bool clear_row0 = false;

		//
		// Find if we need to clear
		// column 0 and row 0.
		for (int r = 0; r < rows; r++) {
			if (matrix[r][0] == 0) {
				clear_col0 = true;
				break;
			}
		}

		for (int c = 0; c < cols; c++) {
			if (matrix[0][c] == 0) {
				clear_row0 = true;
				break;
			}
		}

		//
		// Setup marks.
		for (int r = 1; r < rows; r++) {
			for (int c = 1; c < cols; c++) {
				if (matrix[r][c] != 0)
					continue;
				matrix[r][0] = 0;
				matrix[0][c] = 0;
			}
		}

		//
		// Clear the matrix without border lines.
		for (int r = 1; r < rows; r++) {
			for (int c = 1; c < cols; c++) {
				if (matrix[r][0] == 0 ||
				    matrix[0][c] == 0)
					matrix[r][c] = 0;
			}
		}


		//
		// Clear borderlines.
		if (clear_row0) {
			for (int c = 0; c < cols; c++)
				matrix[0][c] = 0;
		}

		if (clear_col0) {
			for (int r = 0; r < rows; r++)
				matrix[r][0] = 0;
		}
	}
};
