#include <iostream>
using namespace std;

// Linked List class --------------------------------------------------------------------------------------------

class node
{
private:
    int data;
    node *next;

public:
    node(int data);
    int Data() const;

    node *&nextpointer()
    {
        return next;
    }
    node *nextpointer() const
    {
        return next;
    }
};

// Node class' functions' definitions. --------------------------------------------------------------------------

node::node(int data)
{
    this->data = data;
    next = nullptr;
}

int node::Data() const
{
    return data;
}

// Linked List class --------------------------------------------------------------------------------------------

class linkedlist
{
private:
    node *first;

public:
    linkedlist()
    {
        first = nullptr;
    }

    void create(int A[], int n) // Creating a linked list using array.
    {
        first = new node(A[0]); // Assigned 1st node with 0th element of the array as it's data.
        node *last = first;     // created the last node and assigned the address of the first node to it.

        for (int i = 1; i < n; i++) // Since 0th element is already taken care of.
        {
            node *nextNode = new node(A[i]); // New node for every index.
            last->nextpointer() = nextNode;  // Address of the new node being assigned to the last node's next pointer.
            last = nextNode;                 // nextNode's address given to the last node so now last points to the last latest created node and as done in the prior step, that last created node's -> nextpointer address is already stored in last-> nextPointer.
        }
    }

    void display()
    {
        node *p = first; // create a new pointer of type node and assign it with first node's address to ensure that first pointer stays undisturbed.
        while (p)        // while p is not null
        {
            cout << p->Data() << " "; // p being of type node, can access the members of a node and hence displaying the data.
            p = p->nextpointer();     // shifting the pointer to the next node/ traversal for displaying the list.
        }
        cout << endl;
    }

    void RdisplayWrap()
    {
        Rdisplay(first);
        cout << endl;
    }

    void Rdisplay(node *p)
    {
        if (p) // base
        {
            cout << p->Data() << " ";
            Rdisplay(p->nextpointer());
        }
    }

    int sum()
    {
        node *p = first;
        if (!p)
        {
            return -1;
        }
        int s = 0;
        while (p)
        {
            s += p->Data();
            p = p->nextpointer();
        }
        return s;
    }

    void itReverseDisplay()
    {
        node *p = first;
        if (p)
        {
            p = p->nextpointer();
            cout << p->Data() << " ";
        }
        cout << endl;
    }

    void reverseDisplayWrapper()
    {
        reverseDisplay(first);
        cout << endl;
    }

    int search(int key)
    {
        node *p = first;   // traversal pointer at 0th index - 1st position
        node *q = nullptr; // auxillary - helper to move to head.
        int index = 0;     // to track the index manually.
        while (p != nullptr)
        {
            if (key == p->Data())
            {
                if (q != nullptr)
                {
                    q->nextpointer() = p->nextpointer(); // let q take care of the node after p where index was found.
                    p->nextpointer() = first;            // let p's linker link to the originally first node making it the 2nd.
                    first = p;                           // first is always at first so let p's current address where the index was
                                                         // found be stored by first.
                }

                return index; // since the middle block didn't get executed as q was still null, means key was found at 0th index.
            }

            q = p;
            p = p->nextpointer();
            index++;
        }
        return -1;
    }

    void reverseDisplay(node *p)
    {
        if (p)
        {
            reverseDisplay(p->nextpointer());
            cout << p->Data() << " ";
        }
    }

    int max()
    {
        node *p = first;

        if (!p)
        {
            return INT_MIN;
        }

        int m = p->Data();
        while (p)
        {
            if (p->Data() > m)
            {
                m = p->Data();
            }
            else
            {
                p = p->nextpointer();
            }
        }
        return m;
    }
    int min()
    {
        node *p = first;

        if (!p)
        {
            return INT_MAX;
        }

        int m = p->Data();
        while (p)
        {
            if (p->Data() < m)
            {
                m = p->Data();
            }
            else
            {
                p = p->nextpointer();
            }
        }
        return m;
    }

    int counter()
    {
        node *p = first;
        int count = 0;
        while (p)
        {
            count++;
            p = p->nextpointer();
        }
        return count;
    }

    int sortedInsert(int value)
    {
        node *p = first;
        node *q = nullptr;
        node *temp = new node(value);
        int index = 0;
        while (p)
        {
            if (!q && temp->Data() <= p->Data())
            {
                temp->nextpointer() = first;
                first = temp;
                return index;
            }

            if (q && temp->Data() >= q->Data() && temp->Data() <= p->Data())
            {
                temp->nextpointer() = q->nextpointer();
                q->nextpointer() = temp;
                return index;
            }

            q = p;
            p = p->nextpointer();
            index++;
        }

        temp->nextpointer() = p;
        q->nextpointer() = temp;
        return index;
    }

    void insertAt(int index, int value)
    {
        if (index < 0 || index > counter()) // check for invalid index.
        {
            return;
        }

        // to insert at head
        node *temp = new node(value);

        if (index == 0)
        {
            temp->nextpointer() = first;
            first = temp;
            return;
        }

        // to insert at given index
        node *p = first;
        for (int i = 0; i < index - 1; i++)
        {
            p = p->nextpointer();
        }
        temp->nextpointer() = p->nextpointer();
        p->nextpointer() = temp;
    }

    int deleteKey(int key)
    {
        node *p = first;
        node *q = nullptr;
        int index = 0;

        while (p)
        {
            if (p->Data() == key)
            {
                if (p == first)
                {
                    first = first->nextpointer();
                }
                else
                {
                    q->nextpointer() = p->nextpointer();
                }

                delete p;
                return index;
            }
            q = p;
            p = p->nextpointer();
            index++;
        }
        return -1;
    }

    int deleteIndex(int index)
    {
        node *p = first;
        node *q = nullptr;
        int data;
        if (index < 0 || index >= counter() || first == nullptr)
        {
            return -1;
        }
        if (index == 0)
        {
            first = p->nextpointer();
            data = p->Data();
            delete p;
            return data;
        }

        for (int i = 0; i < index; i++)
        {
            q = p;
            p = p->nextpointer();
        }
        q->nextpointer() = p->nextpointer();
        data = p->Data();
        delete p;
        return data;
    }

    int removeDuplicatefromSorted()
    {
        if (!first)
        {
            return -1;
        }

        node *p = first;
        node *q = p->nextpointer();
        int removed = 0;
        while (q)
        {
            if (p->Data() == q->Data())
            {
                p->nextpointer() = q->nextpointer();
                removed = q->Data();
                delete q;
                q = p->nextpointer();
            }
            else
            {
                p = q;
                q = q->nextpointer();
            }
        }

        return removed;
    }

    bool isSorted()
    {
        if (!first || !first->nextpointer())
        {
            return true; // none or 1 node is always sorted
        }
        node *p = first;
        while (p->nextpointer())
        {
            if (p->Data() > p->nextpointer()->Data())
            {
                return false;
            }
            p = p->nextpointer();
        }
        return true;
    }

    void reverseByLinks()
    {
        if (!first)
        {
            return;
        }
        node *p = first, *q = nullptr, *r = nullptr;
        while (p != nullptr)
        {
            r = p->nextpointer();
            p->nextpointer() = q;
            q = p;
            p = r;
        }
        first = q;
    }

    void concat(linkedlist &b)
    {
        if (b.first == 0)
        {
            return;
        }
        if (this->first == nullptr)
        {
            this->first = b.first;
            return;
        }

        node *p = this->first;
        while (p->nextpointer() != nullptr)
        {
            p = p->nextpointer();
        }
        p->nextpointer() = b.first;
        b.first = nullptr;
    }

    void merge(linkedlist &b)
    {
        node *p = this->first;
        node *q = b.first;
        node *last;

        if (p == nullptr)
        {
            first = q;
            q = q->nextpointer();
            return;
        }
        if (q == nullptr)
        {
            return;
        }

        if (p->Data() < q->Data())
        {
            first = p;
            p = p->nextpointer();
        }
        else
        {
            first = q;
            q = q->nextpointer();
        }
        last = first;

        while (p && q)
        {
            if (p->Data() < q->Data())
            {
                last->nextpointer() = p;
                last = p;
                p = p->nextpointer();
            }
            else
            {
                last->nextpointer() = q;
                last = q;
                q = q->nextpointer();
            }
        }

        if (p)
        {
            last->nextpointer() = p;
        }
        else
        {
            last->nextpointer() = q;
        }

        b.first = nullptr;
    }

    bool isLoop()
    {
        if (!first || !first->nextpointer())
            return false;

        node *slow = first;
        node *fast = first;

        while (fast && fast->nextpointer())
        {
            slow = slow->nextpointer();                // 1 step
            fast = fast->nextpointer()->nextpointer(); // 2 steps

            if (slow == fast)
                return true; // loop detected
        }
        return false; // fast reached null hence no loop
    }

    void makecircular()
    {
        if (first == nullptr)
        {
            return;
        }

        node *p = first;
        while (p->nextpointer())
        {
            p = p->nextpointer();
        }
        p->nextpointer() = first;
    }

    void insertincircular(int index, int value)
    {
        if (first == nullptr || index < 0 || index > circularcount())
            return;

        node *p = first;
        node *q = nullptr;
        node *t = new node(value);

        if (index == 0)
        {
            t->nextpointer() = first;
            while (p->nextpointer() != first)
            {
                p = p->nextpointer();
            }
            p->nextpointer() = t;
            first = t;
            return;
        }

        if (index > 0)
        {
            for (int i = 0; i < index; i++)
            {
                q = p;
                p = p->nextpointer();
            }
            q->nextpointer() = t;
            t->nextpointer() = p;
        }
    }

    int circularcount()
    {
        node *p = first;
        int count = 0;

        if (!isLoop())
        {
            cout << "List is not circular." << endl;
            return -1;
        }

        do
        {
            count++;
            p = p->nextpointer();
        } while (p != first);

        return count;
    }

    int deletefromcircular(int index)
    {
        if (first == nullptr || index < 0 || index > circularcount())
            return -1;

        node *p = first, *q = nullptr;
        int data = 0;

        if (index == 0)
        {
            if (first->nextpointer() == first)
            {
                data = first->Data();
                delete first;
                first = nullptr;
                return data;
            }

            while (p->nextpointer() != first)
            {
                p = p->nextpointer();
            }

            data = p->nextpointer()->Data();

            p->nextpointer() = first->nextpointer();
            delete first;
            first = p->nextpointer();
            return data;
        }

        for (int i = 0; i < index; i++)
        {
            q = p;
            p = p->nextpointer();
        }
        data = q->nextpointer()->Data();
        q->nextpointer() = p->nextpointer();
        return data;
    }

    void displaycircular()
    {
        if (!isLoop())
        {
            cout << "List is not circular." << endl;
            return;
        }

        node *p = first;

        do
        {
            cout << p->Data() << " ";
            p = p->nextpointer();
        } while (p != first);

        cout << endl;
    }
};

int main()
{
    int A[] = {11, 22, 33, 44, 50, 60, 70, 80, 90, 100};
    int B[] = {11, 22, 33, 44, 50, 60, 70, 80, 90, 100};
    linkedlist m;
    m.create(A, 10);
    m.makecircular();
    m.displaycircular();
    m.circularcount();
    m.insertincircular(0, 10);
    m.displaycircular();
    m.deletefromcircular(10);
    m.displaycircular();
    return 0;
}