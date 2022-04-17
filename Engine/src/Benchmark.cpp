#include "PCH.h"
#include "Benchmark.h"

Benchmark::Benchmark()
{
	m_arrayIndex = 0;
}

void Benchmark::AddDT(const float& value)
{
	m_deltatimes[m_arrayIndex] = value;
	m_arrayIndex = (m_arrayIndex + 1) % CAPTURED_FRAMES_DT;
}

float Benchmark::GetAverageDT()
{
	float total = 0.f;
	for (size_t i = 0; i < CAPTURED_FRAMES_DT; i++)
	{
		total += m_deltatimes[i];
	}
	return total / static_cast<float>(CAPTURED_FRAMES_DT);
}