//
// 프로그램 설명: 터미널 노드를 제외한 모든 노드가 가능한 두 개씩의 subtree를 갖는 완전 이진 트리이다. 
//자신의 key값은 child보다 크다.
//배열을 이용하여 트리를 표현하였다. (root가 Max)
// 학번, 이름, 요일: 2020111301 조하진 목요일 12시-15시
// 날짜: 2021/11/24
//

#define SWAP(x, y, t) (t=x, x=y, y=t)
//생성자
heap:: heap ()
{
	size = 0;
}
//소멸자
heap:: ~heap ()
{
	size = 0;
}

//heap안에 newData 값을 갖는 새로운 노드를 추가한다.
void heap:: insert(heapData newData) 
{
   int parent, child;
   heapData temp;

   size++;					//1 ) size 증가
   node[size] = newData;	//2) 증가된 size 위치에 newData를 넣음
   child = size;			//3) child를 size로 // 높이
   parent = child / 2;		//4) size/2도 가능하나 의미상 child/2 적합;
   while (node[parent].key<=node[child].key && parent>0)	//parent노드의 높이까지 + 0번째의 데이터는 비교 안함	//5,6,7 반복	//parent>0 or child>1
   {	
	   SWAP(node[child], node[parent],temp);	//5) child와 parent 스왑
	   child = parent;							//6) child가 하나 올라감
	   parent = parent / 2;						//7) parent의 parent로 올라감
   }
}
//file을 읽어 data를 insert한다.
void heap:: read ( ifstream &input_file ) 
{
	heapData inputData;

	while ( input_file >> inputData.key ) 
          insert(inputData);
}
//heap의 첫 번째 노드 (Root node)를 제거하고 그 데이터를 반환
heapData heap:: removeMax() 
{
   int parent, child;
   heapData maxData, temp;

   maxData = node[1];					//1) maxData에 노드값(최대값) 저장

   SWAP(node[1], node[size], temp);		//2) 첫번째 노드와 마지막 노드 스왑
   size--;								//3) size 감소

   parent = 1;							//4) parent 먼저 1 설정 
   //loop 시간은 높이에 비례
   do
   {
	   child = largerChild(parent);		//5) largerChild 이용
	   if (parent == child)				// child가 없다면 중간 종료
		   break;						
	   SWAP(node[child], node[parent], temp);	//6) child번째와 parent번째 스왑
		parent = child;							//7) parent가 child를 쫒아감
   } while (parent <= child);

   return maxData;
}
//heap안의 모든 노드들을 삭제
void heap:: clear ()
{
	size = 0;
}
//heap이 empty이면 True 아니면 False값을 반환(관찰자)
bool heap:: isEmpty ()
{
	return(size == 0);		//size가 0인지
}
// heap이 full이면 True 아니면 False값을 반환(관찰자)
bool heap:: isFull ()
{
	return(size == Max);	//size가 Max인지
}
//heap안의 모든 노드들을 Key값에 따라 오름차순으로 출력
void heap:: sort() 
{
	heap temp;
	int i, oldSize = size;
	heapData data;


	while (!isEmpty())		//isEmpty가 아닌 동안
	{
		data = removeMax();
		showSort(oldSize); getchar();//중간단계 보기
	}

	cout << endl;
	for (i=1; i<= oldSize; i++)
		cout << node[i].key << endl;
}

int heap:: height ()
{
	return (int)ceil(log((double)(size + 1) )/ log(2.0));
}
//heap의 단말노드의 개수를 반환
//ceil의 반환값은 double
int  heap:: leafCount()
{
	return (int)ceil(size / 2.0);
}
//heap의 비단말노드의 개수를 반환
//floor의 반환값은 double
int  heap::nonLeafCount()
{
	return (int)floor(size / 2.0);
}

//heap의 모든 노드의 개수를 반환
int  heap::totalCount()
{
	return size;
}
//heap의 노드 중 한 개의 자식만을 갖는 노드의 개수를 반환
int  heap::singleCount()
{
	if ((size % 2) == 0)	
		return 1;			//짝수면 1 반환
	else
		return 0;			
}

//heap을 level별로 출력
void heap::levelOrder()
{
	int newLine,   // 현재 레벨의 마지막 원소 번호
		j;         // loop counter
	newLine = 1;	//newLine의 초기값 1
	
	system("cls");
	cout << endl << endl;

	for (j = 1; j <= size; j++)			//loop counter 만큼 반복
	{
		cout << node[j].key << "  ";	//값 출력
		if (newLine == j)				//현재 레벨의 마지막 원소가 j가 될 때
		{
			cout << endl; // 줄바꿈 
			newLine = 2 * newLine + 1;		//2의 n승 or 2*n+1	//1, 3, 7, 15 ...	//j 갱신
		}
		
	}

}

//---------------   < largerChild(int index) >----------------------------------
// index의 자식이 index 보다 큰 경우 큰 자식의 위치를 반환하며
// 그러한 자식이 존재하지 않은 경우 index 자체를 반환한다
//
int heap::largerChild(int index)
{
	int left = 2 * index;
	int right = 2 * index + 1;

	if (left > size)									// index has no children
		return index;
	else
		if (left == size)								// index has left child only
			if (node[index].key < node[left].key)		// index < left child
				return left;
			else										// index >= left child
				return index;
		else
			if (node[left].key < node[right].key)		// index has two children 
				if (node[index].key < node[right].key) 	// index < right child								
					return right;
				else									// index >= right child
					return index;
			else										// left child >= right child
				if (node[index].key < node[left].key)	// index < left child
					return left;
				else									// index >= left child
					return index;
}

//------------------<  SiftDown() >--------------------------
// 자신 보다 큰 키값를 갖는 자식과 교환한다.
void heap:: siftDown (int bottom, int top) 
{
	int i;
	heapData temp;

    for (i = top; i >= bottom; i--) 
	{
       if (node[i].key < node[i*2].key)				// 자신이 왼쪽자식보다 작으면 
            if (node[i*2].key > node[i*2 + 1].key)	// 왼쪽자식이 오른쪽 자식보다 크면 
				SWAP(node[i], node[i*2], temp);		// 자신 <-> 왼쪽자식 
            else
				SWAP(node[i], node[i*2+1], temp);	// 자신 <-> 오른쪽자식 
	   else if (node[i].key < node[i*2+1].key)		// 자신이 오른쪽자식보다 작으면 
			SWAP(node[i], node[i*2+1], temp);		// 자신 <-> 오른쪽자식 
    }
}

//------------------<  convert() >--------------------------
// complete banary tree => heap 변환
void heap:: convert()
{ 
	int top = (int)(size / 2);	   // top <- 자식을 가지는 마지막 노드 
	int bottom;

	for (bottom = 1; bottom <= top; bottom++) 
	{
		system("cls");
		// cout << "bottom = " << bottom << endl << endl;
		siftDown(bottom, top);
		showConvert(bottom);		// 1에서 bottom까지 빨간색으로 출력
		getchar();
	}
}

//
/****************************************************/
/*													*/
/*       heap 을 출력하기 위한 여러가지 함수        */
/*													*/
/****************************************************/
//

//--------------------------------------------------------------------
// heap을 반시계방향으로 90도 돌린 트리형식으로 보인다. 

void heap:: showStructure () 
{
    int j;   // loop counter

    cout << endl << endl;
    if ( isEmpty() )
       cout << "Empty heap" << endl;
    else
    {
       cout << endl << "size = " << size << endl;  // 배열 형식으로 출력
	   cout.setf(ios::right); 
	   for ( j = 1 ; j <= size ; j++ ) 
	   {
		   cout.width(5);
           cout << j << " : " << node[j].key << endl;
	   }
	   cout.unsetf(ios::right); 
       cout << endl;
       showSubtree(1,0);                        // 트리 형식으로 출력
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Recursive partner of the showStructure()

void heap:: showSubtree ( int index, int level ) 
{
     int j;   // Loop counter

     if ( index <= size )
     {
        showSubtree(2*index+1,level+1);		// R
        for ( j = 1 ; j <= level ; j++ )	// tab 
            cout << "\t";
        cout << " " << node[index].key;		// D
        if ( 2*index+1 <= size )			// 연결자 출력
           cout << "<";
        else if ( 2*index <= size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index, level+1);		// L
    }
}

//------------------< showSortSubtree >--------------------------
// Recursive partner of the showSort() function. 
//
void heap:: showSortSubtree (int index, int level, int sortSize)
{
     int j, oldTextColor;   
     if ( index <= sortSize )
     {
        showSortSubtree(2*index+1, level+1, sortSize);	// R
        for ( j = 1 ; j <= level ; j++ )        
            cout << '\t';
		oldTextColor = GetColor(0);
		if (index > size) 
				SetColor(12);							// 빨간색
        cout << node[index].key;						// D
		SetColor(oldTextColor);							// 원래색으로! 
		if ( 2*index+1 <= sortSize )                
           cout << '<';									// branch 출력
        else if ( 2*index <= sortSize )
           cout << '\\';								// branch 출력
        cout << endl;
        showSortSubtree(2*index, level+1, sortSize);	// L
    }
}

//------------------< heapSortTree >--------------------------
// heap sort 과정을 반시계방향으로 90도 돌린 트리형식으로 보인다. 
//
void heap:: showSort(int size) 
{
    if ( isEmpty() )
		cout << "Empty heap" << endl;
	else
	{
		clrScr();								 //system("cls");	
		cout << "size = " << size << endl;       // 배열 형식으로 출력
		cout.setf(ios::right); 
		for ( int j = 1 ; j <= size ; j++ ) 
		{
			cout.width(5);
			cout << j << " : " << node[j].key << endl;
		}
		cout.unsetf(ios::right); 
		cout << endl;
		showSortSubtree(1, 0, size);
	}
}

//------------------< showSortSubtree >--------------------------
// Recursive partner of the showSort() function. 
//
void heap:: showConvertSubtree (int index, int level, int sortSize, int bottom)
{
    int j, oldTextColor; ;   
	if ( index <= sortSize )
	{
        showConvertSubtree(2*index+1, level+1, sortSize, bottom);	// R
        for ( j = 1 ; j <= level ; j++ )        
            cout << '\t';
		oldTextColor = GetColor(0);
		if (index <= bottom) 
			SetColor(12);								// 빨간색
		cout << node[index].key;						// D
		SetColor(oldTextColor);							// 원래색으로! 
		if ( 2*index+1 <= sortSize )                
			cout << '<';								// branch 출력
        else if ( 2*index <= sortSize )
			cout << '\\';								// branch 출력
        cout << endl;
        showConvertSubtree(2*index, level+1, sortSize, bottom);	// L
    }
}

//------------------< showConvert >--------------------------
// 변환 과정을 반시계방향으로 90도 돌린 트리형식으로 보인다. 
//
void heap:: showConvert(int bottom) 
{
    cout << endl;
    if ( isEmpty() )
		cout << "Empty heap" << endl;
	else
	{
		clrScr();								//system("cls");	
		cout << "size = " << size << endl;      // 배열 형식으로 출력
		cout.setf(ios::right); 
		for ( int j = 1 ; j <= size ; j++ ) 
		{
			cout.width(5);
			cout << j << " : " << node[j].key << endl;
		}
		cout.unsetf(ios::right); 
		cout << endl;
		showConvertSubtree(1, 0, size, bottom);
	}
}