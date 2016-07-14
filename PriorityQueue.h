/*
 * 二叉堆
 * */
#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

const int maxNum = 50;
const int MinData = -1;

class PriorityQueue {
    private:
        int capacity;
        int size;
        int* elements;
    public:
        PriorityQueue() : capacity(maxNum), size(0) {
            elements = new int[capacity + 1];
            elements[0] = MinData;  // valid storage starts from elements[1]
        }
        ~PriorityQueue() {
            delete [] elements;
        }

        bool isFull() { return size == capacity; }
        bool isEmpty() { return size == 0; }
        int findMin() {
            if (!isEmpty()) return elements[1];
            else return -1;
        }

        void insert(int ele) {
            if (isFull()) return;
            int i;
            for (i = ++size;  // insert the ele in the last
                    elements[i / 2] > ele;  // if the elements is smaller than its father, percolate up
                        i /= 2)
                elements[i] = elements[i / 2];  // percolate up
            elements[i] = ele;  // the loop is over, so find the correct position to insert
        }
        int pop() {  // deleteMin
            if (isEmpty()) return MinData;
            int minELement = elements[1];
            int lastElement = elements[size--];
            int i, child;
            for (i = 1;  // percolate down starts from first position
                    i * 2 <= size;  // i * 2 > size means the node doesn't have child, then loop is over
                         i = child) {
                child = i * 2;  // i's child is i * 2
                if (child < size && elements[child + 1] < elements[child])
                    child++;  // if right child exists, choose smaller one of two
                if (lastElement > elements[child])  // continue to percolate down
                    elements[i] = elements[child];
                else  // if lastElement < its child, then find the correct position, so break the loop
                    break;
            }
            elements[i] = lastElement;
            return minELement;
        }
};
#endif

