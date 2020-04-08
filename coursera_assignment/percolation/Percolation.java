/* *****************************************************************************
 *  Name:              Alan Turing
 *  Coursera User ID:  123456
 *  Last modified:     1/1/2019
 **************************************************************************** */

import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    private boolean[][] grid_status;
    private int open_count;
    private int N;
    private WeightedQuickUnionUF WUF;
    private WeightedQuickUnionUF WUF_NoBottom;

    // creates n-by-n grid, with all sites initially blocked
    public Percolation(int n) {
        if (n <= 0)
            throw new IllegalArgumentException("n illegal\n");
        grid_status = new boolean[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                grid_status[i][j] = false;

        WUF = new WeightedQuickUnionUF(n * n + 2);//留两个点在最上和最下方便判断Percolation,0,N*N+1
        WUF_NoBottom = new WeightedQuickUnionUF(n * n + 1);
        N = n;
        open_count = 0;
    }

    // opens the site (row, col) if it is not open already
    public void open(int row, int col) {
        //Illegal judge
        if (row <= 0 || col <= 0 || row > N || col > N)
            throw new IllegalArgumentException("Input error!\nrow=" + row + "\ncol=" + col);
        if (isOpen(row, col))
            return;

        //open it
        grid_status[row - 1][col - 1] = true;
        open_count++;
        int position = getposition(row, col);

        //union opensite
        union_opensite(row, col, position);


    }

    // is the site (row, col) open?
    public boolean isOpen(int row, int col) {
        //illegal judge
        if (row <= 0 || col <= 0 || row > N || col > N)
            throw new IllegalArgumentException("Input error!\nrow=" + row + "\ncol=" + col);

        return grid_status[row - 1][col - 1];
    }

    // is the site (row, col) full?
    public boolean isFull(int row, int col) {
        //illegal judge
        if (row <= 0 || col <= 0 || row > N || col > N)
            throw new IllegalArgumentException("Input error!\nrow=" + row + "\ncol=" + col);

        return WUF_NoBottom.connected(N * N, getposition(row, col));
    }

    // returns the number of open sites
    public int numberOfOpenSites() {
        return open_count;
    }

    // does the system percolate?
    public boolean percolates() {
        return WUF.connected(N * N, N * N + 1);
    }

    private void union_opensite(int row, int col, int position) {
        int tmp_position;
        int dx[] = { 1, -1, 0, 0 };
        int dy[] = { 0, 0, 1, -1 };

        //top
        if (row == 1) {
            WUF.union(position, N * N);
            WUF_NoBottom.union(position, N * N);
            //查看下面的
            if (row != N)
                if (isOpen(row + 1, col)) {
                    tmp_position = getposition(row + 1, col);
                    WUF.union(position, tmp_position);
                    WUF_NoBottom.union(position, tmp_position);
                }
        }

        //bottom
        if (row == N) {
            WUF.union(position, N * N + 1);
            //查看上面以及左右
            for (int i = 1; i < 4; i++) {
                int X = row + dx[i];
                int Y = col + dy[i];
                if (Y >= 1 && Y <= N && row > 1)//防止极端情况
                    if (isOpen(X, Y)) {
                        tmp_position = getposition(X, Y);
                        WUF.union(position, tmp_position);
                        WUF_NoBottom.union(position, tmp_position);
                    }
            }

        }

        //normal
        if (row > 1 && row < N) {
            for (int i = 0; i < 4; i++) {
                int X = row + dx[i];
                int Y = col + dy[i];
                //上下左右都查
                if (Y >= 1 && Y <= N)
                    if (isOpen(X, Y)) {
                        tmp_position = getposition(X, Y);
                        WUF.union(position, tmp_position);
                        WUF_NoBottom.union(position, tmp_position);
                    }

            }
        }

    }

    private int getposition(int x, int y) {
        return (x - 1) * N + y - 1;
    }

    // test client (optional)
    public static void main(String[] args) {

    }
}

