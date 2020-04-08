/* *****************************************************************************
 *  Name:              Alan Turing
 *  Coursera User ID:  123456
 *  Last modified:     1/1/2019
 **************************************************************************** */

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {
    // perform independent trials on an n-by-n grid
    private double[] threshold;
    private int N, T;
    private double mean, stddev;

    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0)
            throw new IllegalArgumentException("Input error\n");
        threshold = new double[trials];
        N = n;
        T = trials;
        for (int i = 0; i < T; i++) {
            Percolation exp = new Percolation(n);
            while (!exp.percolates())
                exp.open(StdRandom.uniform(1, n + 1), StdRandom.uniform(1, n + 1));
            threshold[i] = (double) exp.numberOfOpenSites() / (double) (N * N);
        }
        mean = StdStats.mean(threshold);
        stddev = StdStats.stddev(threshold);


    }

    // sample mean of percolation threshold

    public double mean() {
        return mean;
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        return stddev;

    }

    // low endpoint of 95% confidence interval
    public double confidenceLo() {
        return mean - (1.96 * stddev) / Math.sqrt(T);
    }

    // high endpoint of 95% confidence interval
    public double confidenceHi() {
        return mean + (1.96 * stddev) / Math.sqrt(T);
    }

    // test client (see below)
    public static void main(String[] args) {
        PercolationStats PlS = new PercolationStats(Integer.parseInt(args[0]),
                                                    Integer.parseInt(args[1]));
        StdOut.println("mean                    = " + PlS.mean());
        StdOut.println("stddev                  = " + PlS.stddev());
        StdOut.println("95% confidence interval = " + "[" + PlS.confidenceLo()
                               + ", " + PlS.confidenceHi() + "]");
    }
}
