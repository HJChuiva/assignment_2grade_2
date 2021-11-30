//
//  Test program for Lab8 
//
#include <time.h>	  // clock(), CLOCKS_PER_SEC	
#include <limits.h>   // INT_MAX
#include <math.h>	  // pow()	
#include <windows.h>

#include <iomanip>  // setw()
#include <iostream>
using namespace std;

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 핸들값

COORD  Pos;                                              // 위치

//-----------------------------------------------------
//  화면상의 임의의 위치로 커서 이동

void gotoXY(int x, int y)
{
   Pos.X = x - 1;
   Pos.Y = y - 1;
   SetConsoleCursorPosition(hConsole, Pos);
}

// 현재 영역 색 추출, 0은 텍스트 영역, 1이상은 배경 영역 색을 리턴
// GetColor(0) => 텍스트 색상 반환, GetColor(1) => 배경 색상 반환
//
int GetColor(int area)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	int color;
	GetConsoleScreenBufferInfo(hConsole, &info);

	if(area) 
		color = (info.wAttributes & 0xf0) >> 4;
	else 
		color = info.wAttributes & 0xf;
	return color;
}

//텍스트, 배경 색 설정
void SetColor(int txtcolor, int bgcolor)
{
	txtcolor &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(hConsole, (bgcolor << 4) | txtcolor);
}

// 텍스트 색 설정
// 배경 색은 GetColor(1)을 통해 원래의 배경색으로 설정
void SetColor(int txtcolor)
{
	txtcolor &= 0xf;
	int bgcolor = GetColor(1);
	SetConsoleTextAttribute(hConsole, (bgcolor << 4) | txtcolor);
}

#include "timer.h"
#include "timer.cpp"

typedef int Array[100000+2];	// 1..n 을 위해서 +1
								// quickSort의 INT_MAX를위해서 +1
clock_t start, finish;
Array TestArray, tempArray;
int i, Max;

#include "sorts.cpp"

//---------------------------------------------------------------//
// 난수를 발생하여 배열을 초기화 한다.                           //
//---------------------------------------------------------------//
// rand() 함수는 0 ~ RAND_MAX 사이의 난수를 발생한다.
// RAND_MAX: 0x7fff, 즉 32767

void initArray (Array L) 
{
	int i;
	srand( (unsigned)time( NULL ) );
	for (i = 1; i <= Max; i++)
		L[i] = rand();			// random
//		L[i] =  i;				// 1, 2, 3, ... , Max-2, Max-1, Max
//		L[i] =  Max + 1 - i;	// Max, Max-1, Max-2, . . , 3, 2, 1
}

//---------------------------------------------------------------//
// 배열을 복사 한다.                                             //
//---------------------------------------------------------------//
void copyArray()
{
	for (i=1; i<=Max; i++) 
		tempArray[i] = TestArray[i];
}

//---------------------------------------------------------------//
// 정렬 결과 확인                                                //
//---------------------------------------------------------------//
bool isSorted(Array L) 
{
	for (i=1; i<Max-1; i++) 
	{
		if ( L[i] > L[i+1] ) 
		{
			cout << "Order error: " << L[i] << " > " << L[i+1] << " at " << i << endl;
			return false;
		}
	}
	return true;
}

//-------------------  main() -----------------------------------//

int main()
{
    Timer sortTimer;      // Timer for sorting routine
	char c;

	while(1)
	{
		system("cls");
		cout << endl << "Enter number of elements: " ;
		cin >> Max;

		initArray(TestArray);
		cout << endl << "# of elements: " << Max << endl;
		
		//--------------- Bubble  Sort O(N*N) ---------------------------//
		copyArray();
		sortTimer.setStartTime();
		bubbleSort(tempArray);
		sortTimer.setStopTime();
		cout << endl << "bubbleSort:    " << sortTimer.runTime() << "초" << endl;
		if (isSorted(tempArray))
			cout << "OK" << endl;


		//--------------- Selection Sort O(N*N) -------------------------//
		
		copyArray();
		sortTimer.setStartTime();
		selectionSort(tempArray);
		sortTimer.setStopTime();
		cout << "selectionSort:   " << sortTimer.runTime() << "초" << endl;
		if (isSorted(tempArray))
			cout << "OK" << endl;
		
		//-----------------  Insertion  Sort O(N*N) ---------------------//
		
		copyArray();
		sortTimer.setStartTime();
		insertionSort(tempArray);
		sortTimer.setStopTime();
		cout << "insertionSort: " << sortTimer.runTime() << "초" << endl;
		if (isSorted(tempArray))
			cout << "OK" << endl;
		
		//-------------------  Shell Sort O(N*N) ------------------------//
		
		copyArray();
		sortTimer.setStartTime();
		shellSort(tempArray);
		sortTimer.setStopTime();
		cout << "shellSort:     " << sortTimer.runTime() << "초" << endl;
		if (isSorted(tempArray))
			cout << "OK" << endl;
		
		//------------------  quickSort O(NlogN) ------------------------//
		
		copyArray();
		tempArray[Max+1] = INT_MAX;
		sortTimer.setStartTime();
		quickSort(tempArray,1,Max);
		sortTimer.setStopTime();
		cout << "quickSort:     " << sortTimer.runTime() << "초" << endl;
		if (isSorted(tempArray))
			cout << "OK" << endl;
		
		//-------------------  MergeSort O(NlogN) -----------------------//
		
		copyArray();
		sortTimer.setStartTime();
		mergeSort(tempArray,Max+1);
		sortTimer.setStopTime();
		cout << "mergeSort:     " << sortTimer.runTime() << "초" << endl;
		if (isSorted(tempArray))
			cout << "OK" << endl;
		
		//-----------------   Heap Sort O(NlogN) ------------------------//
		
		copyArray();
		sortTimer.setStartTime();
		heapSort(tempArray,Max);
		sortTimer.setStopTime();
		cout << "heapSort:      " << sortTimer.runTime() << "초" << endl;
		if (isSorted(tempArray))
			cout << "OK" << endl;
		
		//-------------   RadixSort O(NlogN) -------------------------//
		
		copyArray();
		sortTimer.setStartTime();
		radixSort(tempArray, 5);
		sortTimer.setStopTime();
		cout << "radixSort:     " << sortTimer.runTime() << "초" << endl;
		if (isSorted(tempArray))
			cout << "OK" << endl;

		cout << endl << "continue(Y/N) ? ";
		cin >> c;
		if (toupper(c) == 'N')
			break;
	} // while

	return 0;
}