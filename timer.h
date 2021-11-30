//--------------------------------------------------------------------
//
//  Laboratory 8
//
//  timer.h
//
//--------------------------------------------------------------------

// SystemTime의 type 선언
typedef long SystemTime;

class Timer
{
public:

	// 변환자
	void setStartTime ();
	void setStopTime ();

	// 진행 시간 계산
	double runTime ();

private:

	SystemTime	startTime,   // 시작시간
				stopTime;    // 종료시간
};
