//--------------------------------------------------------------------
//
//  Laboratory 7                                         test7.cpp
//
//  Test program for the operations in the heap ADT
//--------------------------------------------------------------------

#include <assert.h>
#include <ctype.h>
#include <windows.h>	

#include <iostream>
#include <fstream>
#include <iomanip>	// setw()
#include <cmath>	// log(), ceil()
#include <ctime>	// clock_t, clock()
using namespace std;

#define Max 100

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

//-----------------------------------------------------
// 화면을 지운다

void clrScr()
{
	system("cls");
}

//--------------------< sleep >----------------------
// (주어진 시간)/1000 초 동안 실행을 멈춘다.
//
void sleep( clock_t wait ) {
   clock_t goal;
   goal = wait + clock();
   while( goal > clock() )
      ;
}

#include "heap.h"
#include "heap.cpp"

void menu()
{
	clrScr();
	cout << endl << "Commands:" << endl << endl;
	cout << "  R FileName : read data from file and build heap" << endl;
	cout << "  +key       : insert data into heap(Priority Queue)" << endl;
	cout << "  -          : removeMax from a heap(Priority Queue)" << endl;
	cout << "  Z          : clear the heap(Priority Queue)" << endl;
	cout << endl;
	cout << "  L  : # of Leaves" << endl;
	cout << "  N  : # of Non_Leaves" << endl;
	cout << "  T  : # of Total Nodes" << endl;
	cout << "  S  : # of SingleChild Nodes" << endl;
	cout << endl;
	cout << "  B  : binary tree -> heap" << endl;
	cout << "  H  : height" << endl;
	cout << "  X  : sort" << endl;
	cout << "  Y  : levelOrder" << endl;
	cout << endl;
	cout << "  Q  : quit the test program" << endl;
	cout << endl;
//	getchar();
}

//------------< tempRead() >-------------------------------------
// 입력 순서대로 heap에 저장
// convert() 함수 호출 전에 임시로 입력!
// 순차적으로 그대로 입력했다가 변환!
//
void heap:: tempRead ( ifstream &input_file ) 
{
	int inputKey;
	heapData inputData;

	while ( input_file >> inputKey ) 
	{
          inputData.key = inputKey;
          node[++size] = inputData;
	}
}

//--------------------< heapCopy() >-----------------------
// heapSort() 호출 전에 heap을 복사하여 정렬하기 위해 사용
//
void heap:: copy(heap &to) 
{
	int i;
	
	to.size = size;
	for (i=1; i<=size; i++)
		to.node[i] = node[i];
}

//--------------------------------------------------------------------

int main()
{
	heap testHeap;			      // test heap
	heap copyHeap;			      // copy heap for heapSort
	heapData testData;			  // test data
	int inputKey;                 // user input key
	char cmd;	                  // input command

	char FileName[25];		      // R 명령어 처리시의 화일명 
	ifstream  input_file;	      // input file stream for R 명령어
	ifstream  convert_file;		  // input file stream for B 명령어

	system("C:\\WINDOWS\\system32\\chcp 437");		      // code page:  영어:437  한글:949
	system("cls");

	menu();
	cout << endl << "Command: ";  // input command
	cin >> cmd;
	system("cls");	

	do
    {
        if ( cmd == '+' )
           cin >> inputKey;
		else if
			( toupper(cmd) == 'R' )
			cin >> FileName;
		cin.ignore (80,'\n');

        switch ( toupper(cmd) )
        {
		case 'R' :								  // read
			input_file.open(FileName, ios_base::in) ;
			if ( !input_file ) 
			{
				system("C:\\WINDOWS\\system32\\chcp 949");	clrScr();   // code page:  영어:437  한글:949
				cout << "\n\n" << FileName << " 파일을 열 수 없습니다. " << endl << endl;
				exit(1);
			}
			else 
			{
				testHeap.read( input_file );
				input_file.close() ;
			}
			break;
			
		case '+' :                                  // insert(insert)
			if (testHeap.isFull())
				cout << "heap is full..." << endl;
			else
			{
				testData.setKey(inputKey);
				cout << "insert : key = " << testData.getKey() << endl;
				testHeap.insert(testData);
			}
			break;
			
		case '-' :                                  // removeMax(removeMax)
			if (testHeap.isEmpty())
				cout << "heap is empty..." << endl;
			else
			{
				testData = testHeap.removeMax();
				cout << "removed element : "
					<< " key = " << testData.getKey() << endl;
			}
			break;
			
		case 'H':
			cout << "Height of heap : " << testHeap.height() << endl;
			break;
			
		case 'L':
			cout << "Number of Leaf nodes: " << testHeap.leafCount() << endl;
			break;
			
		case 'N':
			cout << "Number of Non Leaf nodes: " << testHeap.nonLeafCount() << endl;
			break;
			
		case 'T':
			cout << "Number of Total nodes: " << testHeap.totalCount() << endl;
			break;
			
		case 'S':	
			cout << "Number of singleChild nodes: " << testHeap.singleCount() << endl;
			break;
			
		case 'B':		// Binary tree -> heap
			convert_file.open("data2.lab7", ios_base::in) ;
			if ( !convert_file ) 
			{
				cout << "can not open datafile" << endl;
				exit(1);
			}
			else 
			{
				testHeap.clear();
				testHeap.tempRead( convert_file );
		        testHeap.showStructure();	getchar();
				testHeap.convert();
				convert_file.close();
			}
			break;

		case 'X':		
			if ( testHeap.isEmpty() ) 
				cout << "heap is empty! " << endl;
			else
			{
				testHeap.copy(copyHeap);
				copyHeap.sort();				   // 임시 heap을 정렬한다
			}
			break;

		case 'Y':		
			if ( testHeap.isEmpty() ) 
				cout << "heap is empty! " << endl;
			else
				testHeap.levelOrder();
			break;

		case 'Z' :                                 // clear
			cout << "Clear the heap" << endl;
			testHeap.clear();
			break;
			
		case '?' :								   // Help
			menu();	getchar();
			break;
			
		case 'Q' :                                 // Quit test program
			break;
			
		default :                                  // Invalid command
			cout << "Invalid command" << endl;
        }
		//cout << endl;
        testHeap.showStructure();					// Output tree
        cout << endl << "Command: ";				// Read command
        cin >> cmd;
		system("cls");
    }
    while ( ( toupper(cmd) != 'Q' ) );
    system("chcp 949"); system("cls");
	getchar(); getchar();

	return 0;
}