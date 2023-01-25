# CST211_Lab2

Lab 2 

Doubly-Linked List 

Description 

Write a Doubly-Linked List ADT that includes the methods listed below. Work off of the associated Shell. Be sure to make it a Template!  

 

List class variables and methods:  

 

private: 

    Node<T>* l_head; // pointer to the head of the list 

    Node<T>* l_tail; // pointer to the tail of the list 

    int l_count; // number of nodes in the list 

public: 

    List(); // default constructor 

    List(const T data); // parameterized constructor 

    List(const List& copy); // copy constructor 

    List(List&& move) noexcept; // move constructor 

    ~List(); // deconstructor 

  

    List& operator=(const List& copy); //copy assignment operator  

    List& operator=(List&& move) noexcept; //move assignment operator 

    explicit operator bool() const; // T if list is empty, otherwise F 

  

    void Append(const T data); // put T data at the end of the list 

    void Prepend(const T data); // put T data at the end of the list 

    void RemoveLast(); // remove the last node of the list 

    void RemoveFirst(); // remove the first node of the list 

    void Extract(const T data); // remove the node that equals T data  

    void InsertAfter(const T data, const T after); //insert T data after T after 

    void InsertBefore(const T data, const T before); //insert T data before T before 

    void Purge() noexcept; // delete all of the nodes in the list 

  

    T& Last(); // return the address of the last element 

    T Last() const; // return the value of the last element 

    T& First(); // return the address of the first element 

    T First() const; // return the value of the value element 

  

    Node<T>* getHead(); // return the pointer to the head of the list 

    Node<T>* getTail(); // return the pointer to the tail of the list 

    bool isEmpty() const noexcept; // T if list is empty, otherwise F 

    size_t Size() const noexcept; // return the size of the list 

    bool operator==(const List<T>& rhs) const noexcept; // compare if 2 lists are equal 

 

 

Node class variables and methods: 

private: 

    T n_data; // data for the node 

    Node<T>* next_ptr; // pointer to the next node 

    Node<T>* prev_ptr; // pointer to the previous node 

  

    template<typename U>friend class List; // connection to the list 

public: 

    Node(); // default constructor 

    Node(const Node& copy); // copy constructor 

    Node(Node&& move) noexcept; // move constructor 

    Node(const T data); // parameterized constructor 

    Node(const T data, Node<T>* next, Node<T>* prev);// parameterized constructor2 

    ~Node() = default; // deconstructor 

  

    Node<T>& operator=(const Node& copy); //copy assignment operator 

    Node<T>& operator=(Node&& move) noexcept; //move assignment operator 

  

    T& Value() noexcept; // returns the address of the value 

    T Value() const noexcept; // returns the data value 

    void Value(const T data); // sets the data value 

  

    Node<T>* Next() noexcept; // gets the next node pointer 

    Node<T>* Next() const noexcept; // gets the next node pointer 

    Node<T>* Previous() noexcept; // gets the previous node pointer 

    Node<T>* Previous() const noexcept; // gets the previous node pointer 

    void Next(Node<T>* const next) noexcept; // sets the next node pointer 

    void Previous(Node<T>* const previous) noexcept; // sets the previous node pointer 

 

Stipulations 

Make a friendship relationship between Node and List. 
Do not use the sentinel method (a counter – check for nullptr). 
There should be NO memory leaks. 
Each method should have at least 1 comment. 
Your name should be in the final project name AND in each file in the project. 
Use you Exception class to throw appropriate errors. 
 

Grading: 

Correct List Members 15 pts 
No Memory Leaks 10 pts 

Documentation 10 pts 

Naming 5 pts 

Tests passed 50 pts 
