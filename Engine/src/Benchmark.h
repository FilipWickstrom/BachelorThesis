#pragma once

class Benchmark
{
private: 
	float m_deltatimes[CAPTURED_FRAMES_DT] = {0.f};
	int	  m_arrayIndex;

public:
	Benchmark();
	~Benchmark() = default;

	void AddDT(const float& value);
	float GetAverageDT();

};