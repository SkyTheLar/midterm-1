/***************************************

COMSC 210 | Midterm 1 | Skylar Robinson | IDE Used: Eclipse

****************************************/

#include <iostream> //include  iostream library
using namespace std; //namespace standard

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; //define constants for min/max random number and list size

class DoublyLinkedList { //define dll class
private: //private variables
    struct Node { //private structure definition for single node
        int data; //int that is the data in a node
        Node* prev; //pointer to previous list node
        Node* next; //pointer to next list node
        Node(int val, Node* p = nullptr, Node* n = nullptr) { //node constructor definition
            data = val; //set node data to input val
            prev = p; //set node previous to input p or nullptr
            next = n; //set node next to input n or nullptr
        }
    };

    Node* head; //private pointer variable head for first node
    Node* tail; //private pointer variable tail for last node

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; } //default constructor

    void insert_after(int value, int position) { //function to insert a given value after a given position
        if (position < 0) { //if position is less than zero (cant exist)
            cout << "Position must be >= 0." << endl; //display error message
            return; //end funciton call
        }

        Node* newNode = new Node(value); //create new node with given value and nullptr prev and next
        if (!head) { //if the list is empty
            head = tail = newNode; //make the first and last item the new node
            return; //end function call
        }

        Node* temp = head; //create temp node pointer pointing to head
        for (int i = 0; i < position && temp; ++i) //loop "position" times
            temp = temp->next; //set temp pointer to next item in list (temp will be node to add newnode after)

        if (!temp) { //if temp is nullptr (position was outside list)
            cout << "Position exceeds list size. Node not inserted.\n"; //display error message
            delete newNode; //delete the node we created
            return; //end function call
        }

        newNode->next = temp->next; //set newnode next pointer to node following temp
        newNode->prev = temp; //set newnode prev pointer to temp
        if (temp->next) //if temp is not the end of the list
            temp->next->prev = newNode; //set the prev pointer of the node after temp to the new node
        else //temp is the end of the list
            tail = newNode; //tail points to newnode
        temp->next = newNode; //the node after temp is now newnode
    }

    void delete_val(int value) { //delete a node with a given value
        if (!head) return; //if list is empty end funciton call

        Node* temp = head; //create temporary node pointer to head
        
        while (temp && temp->data != value) //while temp is't nullptr (not the end of the list) and temp data isn't the target value
            temp = temp->next; //move temp to next list item (temp will be node to delete)

        if (!temp) return; //if value not found end function call

        if (temp->prev) //if temp is not beginning of list
            temp->prev->next = temp->next; //next ptr of node before temp becomes node after temp
        else //temp is beginning of list
            head = temp->next; //head becomes node after temp

        if (temp->next) //if temp is not end of list
            temp->next->prev = temp->prev; //prev of node after temp becomes node before temp
        else //temp is end of list
            tail = temp->prev; //tail becomes node before temp

        delete temp; //delete temp node
    }

    void delete_pos(int pos) { //delete a node at a given position
        if (!head) { //if list is empty
            cout << "List is empty." << endl; //display error message
            return; //end function call
        }
    
        if (pos == 1) { //if position is 1
            pop_front(); //remove the first list item
            return; //end function call
        }
    
        Node* temp = head; //create temp node pointer pointing to head
    
        for (int i = 1; i < pos; i++){ //loop pos - 1 times
            if (!temp) { //if temp is nullptr (pos out of list)
                cout << "Position doesn't exist." << endl; //display error message
                return; //end function call
            }
            else //if temp isn't out of list
                temp = temp->next; //temp points to next node in list (temp will be node to delete)
        }
        if (!temp) { //if temp is out of list
            cout << "Position doesn't exist." << endl; //display error message
            return; //end function call
        }
    
        if (!temp->next) { //if temp is end of list
            pop_back(); //delete last item in list
            return; //end function call
        }
    
        Node* tempPrev = temp->prev; //create node pointer pointing to node before temp
        tempPrev->next = temp->next; //next of node before temp becomes node after temp
        temp->next->prev = tempPrev; //prev of node after temp becomes node before temp
        delete temp; //delete node at given position
    }

    void push_back(int v) { //add item with value v to end of list
        Node* newNode = new Node(v); //create new node with value v
        if (!tail) //if list is empty
            head = tail = newNode; //first and last items of list are newnode
        else { //list is not empty
            tail->next = newNode; //next of last item becomes newnode
            newNode->prev = tail; //prev of newnode is original last node
            tail = newNode; //end of list is now newnode
        }
    }
    
    void push_front(int v) { //add item to beginning of list
        Node* newNode = new Node(v); //create new node with value v
        if (!head) //if list is empty
            head = tail = newNode; //first and last items of list are newnode
        else { //list is not empty
            newNode->next = head; //next of newnode is original fist node
            head->prev = newNode; //prev of original first item is newnode
            head = newNode; //new first node is newnode
        }
    }
    
    void pop_front() { //remove first item in list

        if (!head) { //if list is empty
            cout << "List is empty." << endl; //display error message
            return; //end function call
        }

        Node * temp = head; //create temp pointer to head node

        if (head->next) { //if head is not the only item in the list
            head = head->next; //original second item becomes first item
            head->prev = nullptr; //prev of new head is nullptr
        }
        else //first item is only item
            head = tail = nullptr; //make list empty
        delete temp; //delete temp which is the original first node
    }

    void pop_back() { //remove the last item in the list
        if (!tail) { //if list is empty
            cout << "List is empty." << endl; //display error message
            return; //end function call
        }
        Node * temp = tail; //create node pointer temp pointing to the end of the list

        if (tail->prev) { //if tail is not the only node
            tail = tail->prev; //new last item is the item before old last item
            tail->next = nullptr; //next of new tail is nullptr
        }
        else //last item is the only item
            head = tail = nullptr; //make list empty
        delete temp; //delete temp aka last node
    }

    ~DoublyLinkedList() { //deconstructor
        while (head) { //while list isn't empty
            Node* temp = head; //create node pointer to head
            head = head->next; //move head pointer to next node in list
            delete temp; //delete old head
        }
    }
    void print() { //print function
        Node* current = head; //create node pointer to head
        if (!current) { //if list is empty
            cout << "List is empty." << endl; //display list is empty
            return; //end function call
        }
        while (current) { //while current isn't nullptr (while it's pointing to the list)
            cout << current->data << " "; //display the data of the current node + a space
            current = current->next; //move current ptr to next item in list
        }
        cout << endl; //linebreak
    }

    void print_reverse() { //print in reverse order
        Node* current = tail; //create node pointer to tail
        if (!current) { //if list is empty
            cout << "List is empty." << endl; //display list is empty
            return; //end function call
        }
        while (current) { //while current isn't outside the list
            cout << current->data << " "; //display data of current node + space
            current = current->prev; //move current ptr to previous item in the list
        }
        cout << endl; //linebreak
    }

    //function to display every other element
    void every_other_element() {
    	Node* current = head; //node pointer to head
    	int count = 1; //counter int starts at 1
    	if (!current) { //if list is empty
    		cout << "List is empty." << endl; //display list is empty
    		return; //end function call
    	}
    	while (current) { //while current is in list
    		if (count % 2 == 1) //if count is odd
    			cout << current->data << " "; //display the data in current
    		current = current->next; //current to next node
    		count++; //increment counter
    	}
    	cout << endl; //linebreak
    }
};

int main() { //main function
    DoublyLinkedList list; //make list

    //populate list with 1-20
    for (int i = 0; i < 20; i++) {
    	list.push_back(i + 1);
    }

    //display whole list
    cout << "Entire List: ";
    list.print();
    //display every other
    cout << "Every other element: ";
    list.every_other_element();

    return 0; //end program return 0
}
