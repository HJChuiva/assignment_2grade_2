//--------------------------------------------------------------------
//
//  Laboratory 7                                             heap.h
//
//  Class declaration for the array implementation of the heap ADT
//
//--------------------------------------------------------------------

class heapData
{
  public:

    void setKey ( int newKey )
    { key = newKey; }   

    int getKey () const
    { return key; }     

  private:
    int key;           

  friend class heap;
};

class heap
{
  public:

    // Constructor
    heap ();

    // Destructor
    ~heap ();

    // 변환자
    void insert(heapData newData);			// insert data
    heapData removeMax();					// remove and return max data
    void clear ();                          // clear heap
	void read (ifstream &input_file ) ;		// read data from file => heap 
	void tempRead (ifstream &input_file ) ;	// read data from file => binary tree (힙변환에 사용)
	void copy (heap &);						// copy heap (힙정렬에 사용)
	void siftDown (int bottom, int top);	// parent <-> child (convert 에서 호출)
	void convert();							// complete binary tree => heap (힙변환에 사용)

    // 관찰자
    bool isEmpty () ;			            // heap is empty
    bool isFull () ;				        // heap is full

	int leafCount () ;						// # of leaf nodes
	int nonLeafCount () ;					// # of nonleaf nodes
	int totalCount () ;						// # of nodes
	int singleCount () ;					// # of single child nodes   
	int height() ;							// height of heap 

	//  heap 을 출력하기 위한 여러가지 함수: 관찰자
    void showStructure () ;
	void showSort(int size) ;
	void showConvert(int bottom);

	void levelOrder();						// 과제 212
	void sort();

private:

    // Recursive partner of the showStructure() function
    void showSubtree ( int index, int level ) ;
	void showSortSubtree (int index, int level, int sortSize);
	void showConvertSubtree (int index, int level, int sortSize, int bottom);
	int  largerChild(int hole);

    // Data members
    int size;								// Actual number of elements in the heap
    heapData node[Max+1];					// Array containing the heap elements
};