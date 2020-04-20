/* *****************************************************************************
 *  Name:
 *  Date:
 *  Description:
 **************************************************************************** */

import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

import java.util.Iterator;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private Item a[];
    private int N;

    // construct an empty randomized queue
    public RandomizedQueue() {
        a = (Item[]) new Object[1];
        N = 0;
    }

    // is the randomized queue empty?
    public boolean isEmpty() {
        return N == 0;
    }

    // return the number of items on the randomized queue
    public int size() {
        return N;
    }

    // add the item
    public void enqueue(Item item) {
        if (item == null)
            throw new IllegalArgumentException("input error");
        if (N == a.length)
            resize(2 * a.length);
        a[N++] = item;
    }

    // remove and return a random item
    public Item dequeue() {
        if (isEmpty())
            throw new java.util.NoSuchElementException();
        swap(N - 1, StdRandom.uniform(N), a);//整个数列中随机取一个到尾部
        Item tmp = a[--N];
        a[N] = null;//防止对象游离
        if (N == a.length / 4 && N > 0)
            resize(a.length / 2);
        return tmp;//弹出尾部
    }

    // return a random item (but do not remove it)
    public Item sample() {
        if (isEmpty())
            throw new java.util.NoSuchElementException();
        return a[StdRandom.uniform(N)];
    }

    private void swap(int i, int j, Item[] a) {
        //数组内交换
        if (a[i] == a[j])//值相同就不做多余的操作了
            return;
        Item tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    private void resize(int len) {
        Item[] tmp = (Item[]) new Object[len];
        for (int i = 0; i < N; i++)
            tmp[i] = a[i];
        a = tmp;
    }

    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new ArrayIterator();
    }

    private class ArrayIterator implements Iterator<Item> {
        private int i = N;
        private Item[] tmp;

        public ArrayIterator() {
            //另开一个数组，防止影响原队列
            tmp = (Item[]) new Object[N];
            for (int j = 0; j < N; j++)
                tmp[j] = a[j];
        }

        public boolean hasNext() {
            return i > 0;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }

        public Item next() {
            if (i == 0)
                throw new java.util.NoSuchElementException();
            swap(i - 1, StdRandom.uniform(i), tmp);//kruth老爷子的洗牌算法
            return tmp[--i];
        }
    }

    // unit testing (required)
    public static void main(String[] args) {
        RandomizedQueue<String> test = new RandomizedQueue<String>();
        while (!StdIn.isEmpty()) {
            test.enqueue(StdIn.readString());
            StdOut.print(test.size() + " ");
        }
        StdOut.println();
        for (String s : test)
            StdOut.print(s + " ");
        StdOut.println();
        int n = test.size();
        for (int i = 0; i < n + 2; i++)
            StdOut.print(test.sample() + " ");
        StdOut.println();
        for (int i = 0; i < n; i++)
            StdOut.print(test.dequeue() + " ");
        StdOut.println();
        StdOut.println(test.size() + " " + test.isEmpty());
    }

}
