// 프로그램 설명 : 여러 가지 내부정렬 방법을 공부하고 각각의 방법으로 같은 데이터를 정렬하는데 걸리는 수행시간을 측정, 비교한다.
// bubbleSort, minIndex. selectionSort. insertionSort. shellSort, quickSort 속도 비교
// 학번: 2020111301 
// 이름: 조하진 
// 분반: 1분반 12시-15시
// 날짜: 2021/12/01

#define SWAP(x, y, t) (t=x, x=y, y=t)
#define radix 10

//---------------------------------------------------------------//
// 버블정렬을 이용한 오름차순 정렬                               //
//---------------------------------------------------------------//

//서로 인접한 두 원소를 검사하여 정렬
void bubbleSort(Array L) 
{
	int temp;

	for (int i = 1; i <= Max; i++)				//i looping 돌면서  작은 원소를 찾음
		for (int j = i + 1; j <= Max; j++)		//j looping i+1부터 돔
			if (L[i] > L[j])					//i번째보다 j번째가 작을 때
				SWAP(L[i], L[j], temp);			//SWAP

}

//원소를 처음부터 탐색하면서 작은 수를 찾음
int minIndex(Array L, int from, int to)
{
	int min = from;							//가장 작은 값의 위치를 받아서 반환, from에서 출발
	for (int i = from + 1; i <= to; i++)	//제일 작은 위치를 찾음
		if (L[i] < L[min])					//i번째가 min번째보다 작으면
			min = i;						//i번째가 더 작은 위치
	return min;								//제일 작은 min번째 반환

}

//작은 수를 찾고 그 수를 배열의 앞쪽에 보내고 다시 작은 수를 찾는 정렬
void selectionSort(Array L)
{
	int temp, min;

	for (int i = 1; i <= Max; i++)
	{
		min = minIndex(L, i, Max);		//L 배열에서 i부터 Max까지 가장 작은 값이 어디있는지 받아서 min에 저장
		SWAP(L[i], L[min], temp);		//i번째로 작은 원소는 min번째에 있음
	}
}

// 2번째 원소부터 시작하여 그 앞(왼쪽)의 원소들과 비교하여 삽입할 위치를 지정한 후
//원소를 뒤로 옮기고 지정된 자리에 자료를 삽입 하여 정렬
void insertionSort (Array L) 
{
	int j, next;

	for (int i = 1; i <= Max; i++)
	{
		next = L[i];					//i번째 원소 저장
		j = i - 1;						
		while (L[j] > next && j>0)		//j번째 원소와 next 비교하여 '1'번에서 선택한 값보다 크다면, 1번 아래로 내려가지 않도록 j>0 조건 추가
		{
			L[j + 1] = L[j];			//서로 값을 교환
			j--;						//j 하나 내려옴
		}	
		L[j + 1] = next;				//j에는 현재 temp 값보다 작은 값들 중 제일 큰 값의 위치 i 를 가리키게 됨
	}

}
//간격을 크게 삽입정렬로 하고 간격이 1이 될때까지 반복하는 정렬
void shellSort( Array L ) 
{
	int j, h=1, next;

	//최대간격(h) 결정
	while (3 * h + 1 < Max)
		h = 3 * h + 1;
	//간격이 1이 될때까지
	while (h > 0)
	{
		//간격 h 인 삽입정렬 
		for (int i = 1; i <= Max; i++)
		{
			next = L[i];
			j = i - h;
			while (L[j] > next && j > 0)
			{
				L[j + h] = L[j];
				j = j - h;
			}
			L[j + h] = next;
		}

		//h 감소
		h = h / 3;
	}//while

}
//임의의 pivot값을 두고, pivot 의 좌측에는 pivot 보다 작은값을 두고 우측에는 pivot 보다 큰 값을 두어 재귀적으로 반복하는 정렬
void quickSort(Array L, int left, int right) 
{
	int i, j, pivot, temp;

	if (left < right)							//진행조건
	{
		i = left;
		j = right + 1;
		pivot = L[left];
		do
		{
			do i++; while (L[i] < pivot);		//i가 pivot보다 작은 동안 올라가다가 pivot보다 큰 원소를 만나면 멈춤
			do j--; while (L[j] > pivot);		//j가 pivot보다 큰 동안 내려가다가 pivot보다 작은 원소를 만나면 멈춤
			if (i < j)							//아직 i,j가 안 만났으면 SWAP
				SWAP(L[i], L[j], temp);
		} while (i < j);						//한바퀴 돌때까지 반복

		SWAP(L[left], L[j], temp);				//pivot이 자기 위치를 찾음
		quickSort(L, left, j - 1);				//j번째에 pivot이 들어가 있으므로 left부터 j-1번까지 재귀호출
		quickSort(L, j + 1, right);				//j+1부터 right까지 재귀호출
	}
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
