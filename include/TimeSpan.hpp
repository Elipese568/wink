#pragma once

#include<chrono>

template<class TimePoint>
class TimeSpan{
private:
    TimePoint _startTime;
    TimePoint _endTime;
public:
    TimeSpan(const TimePoint& startTime,
             const TimePoint& endTime) :
             _startTime(startTime), _endTime(endTime)
    {}

    constexpr bool contains(const TimePoint& timePoint) const{
        return _startTime <= timePoint && timePoint <= _endTime;
    }

    TimePoint start() const{
        return _startTime;
    }
    TimePoint end() const{
        return _endTime;
    }
};

