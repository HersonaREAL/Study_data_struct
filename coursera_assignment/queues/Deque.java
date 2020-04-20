import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

import java.util.Iterator;

/* *****************************************************************************
 *  Name:
 *  Date:
 *  Description:
 **************************************************************************** */
public class Deque<Item> implements Iterable<Item> {
    private class node {
        Item item;
        node next;
        node pre;//双向链表
    }

    private node first, last;
    private int N; //元素数量

    // construct an empty deque
    public Deque() {
        last = first = null;
        N = 0;
    }

    // is the deque empty?
    public boolean isEmpty() {
        return N == 0;
    }

    // return the number of items on the deque
    public int size() {
        return N;
    }

    // add the item to the front
    public void addFirst(Item item) {
        if (item == null)
            throw new IllegalArgumentException("Input error");
        node oldfirst = first;
        first = new node();
        first.item = item;
        first.next = oldfirst;
        if (isEmpty())//极端情况处理
            last = first;
        else
            oldfirst.pre = first;
        N++;
    }

    // add the item to the back
    public void addLast(Item item) {
        if (item == null)
            throw new IllegalArgumentException("Input error");
        node oldlast = last;
        last = new node();
        last.item = item;
        last.pre = oldlast;
        if (isEmpty())//极端情况处理
            first = last;
        else
            oldlast.next = last;
        N++;

    }

    // remove and return the item from the front
    public Item removeFirst() {
        if (isEmpty())
            throw new java.util.NoSuchElementException();
        Item tmp_item = first.item;
        //只有一个节点节点的处理比较特殊
        if (N != 1) {
            first = first.next;
            first.pre = null;//防止对象游离
        }
        else
            first = last = null;
        N--;
        return tmp_item;
    }

    // remove and return the item from the back
    public Item removeLast() {
        if (isEmpty())
            throw new java.util.NoSuchElementException();
        Item tmp_item = last.item;
        if (N != 1) {
            last = last.pre;
            last.next = null;//防止对象游离
        }
        else
            last = first = null;
        N--;
        return tmp_item;
    }

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator() {
        return new ListIterator();
    }

    private class ListIterator implements Iterator<Item> {
        private node current = first;

        public boolean hasNext() {
            return current != null;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }

        public Item next() {
            if (current == null)
                throw new java.util.NoSuchElementException();
            Item tmp = current.item;
            current = current.next;
            return tmp;
        }
    }

    // unit testing (required)
    public static void main(String[] args) {
        Deque<String> test = new Deque<String>();
        while (!StdIn.isEmpty()) {
            test.addLast(StdIn.readString());
            StdOut.print(test.size() + " ");
        }
        StdOut.println("\n" + test.isEmpty());
        for (int n = test.size(); n > 0; n--)
            test.addFirst(test.removeLast());
        for (String s : test)
            StdOut.print(s + " ");
        StdOut.println();
        for (int n = test.size(); n > 0; n--)
            StdOut.print(test.size() + ":" + test.removeFirst() + " ");
        StdOut.println("\n" + test.isEmpty());

    }

}
