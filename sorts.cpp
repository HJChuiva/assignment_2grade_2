//
//
//

#define SWAP(x, y, t) (t=x, x=y, y=t)
#define radix 10

//---------------------------------------------------------------//
// 버블정렬을 이용한 오름차순 정렬                               //
//---------------------------------------------------------------//
void bubbleSort(Array L) 
{
	int temp;




}

int minIndex(Array L, int from, int to)
{





}

void selectionSort(Array L)
{
	int temp, min;





}

void insertionSort (Array L) 
{
	int j, next;















}

void shellSort( Array L ) 
{
	int j, h=1, next;























}

void quickSort(Array L, int left, int right) 
{
	int i, j, pivot, temp;




















}


//---------------------------------------------------------------//
// merge : L1[l..m]+L1[(m+1)..n] => L2[l..m]                     //
//---------------------------------------------------------------//
void merge(Array L1, Array L2, int l, int m, int n)
{
	int i, j, k, t;

	i = l;
	k = l;
	j = m + 1;

	while ((i <= m) && (j <= n))
	{
		if (L1[i] <= L1[j])
			L2[k++] = L1[i++];
		else
			L2[k++] = L1[j++];
	}

	if (i > m)
		for (t = j; t <= n; t++)
			L2[k++] = L1[t];
	else
		for (t = i; t <= m; t++)
			L2[k++] = L1[t];
}

//--------------------------------------------------------------
void Mpass(Array L1, Array L2, int n, int length)
{
	// n: 전체 원소의 개수, length: 합병할 subfile의 길이
	int i, t;

	i = 1;
	while (i <= (n - 2 * length + 1))
	{
		merge(L1, L2, i, i + length - 1, i + 2 * length - 1);
		i += 2 * length;
	}

	if (i + length < n)
		merge(L1, L2, i, i + length - 1, n);
	else
		for (t = i; t < n; t++)
			L2[t] = L1[t];
}

//---------------------------------------------------------------//
// 합병정렬을 이용한 오름차순 정렬                               //
//---------------------------------------------------------------//
void mergeSort(Array L1, int n)
{
	int i, length = 1;   // 합병할 서브파일의 길이
	Array L2;

	while (length < n) {
		Mpass(L1, L2, n, length);
		length *= 2;
		for (i = 1; i < Max + 1; i++)
			L1[i] = L2[i];
		//Mpass(L2, L1, n, length);
		//length *= 2;
	}
}

//---------------------------------------------------------------//
// 힙으로 변환                                                   //
//---------------------------------------------------------------//
void adjust(Array L, int root, int n)
{
	int child, rootkey, temp;
	temp = L[root];
	rootkey = L[root];
	child = 2 * root;		   //왼쪽자식
	while (child <= n)
	{
		if ((child<n) && (L[child]<L[child + 1]))
			child++;
		if (rootkey > L[child])
			break;
		else
		{
			L[child / 2] = L[child];
			child *= 2;
		}
	}
	L[child / 2] = temp;
}

//---------------------------------------------------------------//
// 힙정렬을 이용한 오름차순 정렬                                 //
//---------------------------------------------------------------//
void heapSort(Array L, int n)
{
	int i, temp;

	// heap으로 만든다
	for (i = n / 2; i>0; i--)
		adjust(L, i, n);

	// 제일큰수(1번째 원소)를 마지막(n번째)으로 옮기고 나머지를 다시 heap으로 만든다.
	for (i = n - 1; i>0; i--)
	{
		SWAP(L[1], L[i + 1], temp);
		adjust(L, 1, i);
	}
}

//---------------------------------------------------------------//
// 기수정렬을 이용한 오름차순 정렬                               //
//---------------------------------------------------------------//

// p : 최대자리수 (RAND_MAX의 경우 최대값은 32767이므로 5자리, 따라서 5)
void radixSort(Array L, int p)
{
	Array temp;        // 중간 결과를 저장
	int counts[radix]; // 각 자리수 당 카운트
	int index, power, i, j, n;
	int k;

	for (n = 0; n < p; n++)
	{
		for (i = 0; i<radix; i++)
			counts[i] = 0; // 초기화

		power = (int)pow((double)radix, (double)n);  // power = 10^n

													 // 현재 자리수(=n) 기준으로 각 숫자의 발생횟수를 센다.
		for (j = 1; j <= Max; j++)
		{
			index = (int)(L[j] / power) % radix;
			counts[index]++;
		}

		// 누적 카운트
		for (i = 1; i<radix; i++)
			counts[i] = counts[i] + counts[i - 1];

		// 누적 카운트를 사용해 각 항목의 위치를 결정
		for (j = Max; j >= 1; j--) // 뒤에서 부터 시작
		{
			index = (int)(L[j] / power) % radix;
			temp[counts[index]] = L[j];
			counts[index]--;
		}

		for (k = 1; k <= Max; k++)	// 중간 결과에서 다시 시작하기 위해 복사
			L[k] = temp[k];
	}
}
