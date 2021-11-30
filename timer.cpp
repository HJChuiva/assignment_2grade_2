//--------------------------------------------------------------------
//
//  Laboratory 8
//
//  Implementation of the Timer ADT: timer.cpp
//
//--------------------------------------------------------------------


void Timer::setStartTime ()

// timer 시작

{
    startTime = clock();
}

//--------------------------------------------------------------------

void Timer::setStopTime ()

// timer 종료

{
    stopTime = clock();
}

//--------------------------------------------------------------------

double Timer::runTime ()

// startTime 에서 stopTime까지의 진행시간을 초단위로 계산한다

{
	return  (double)(stopTime - startTime) / CLOCKS_PER_SEC;
}


