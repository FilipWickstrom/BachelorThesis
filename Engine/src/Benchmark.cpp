#include "PCH.h"
#include "Benchmark.h"

Benchmark::Benchmark()
{
	m_arrayIndex = 0;
	m_arrayFull = false;
}

void Benchmark::AddDT(const float& value)
{
	if (m_arrayIndex + 1 == CAPTURED_FRAMES_DT)
		m_arrayFull = true;
	
	m_deltatimes[m_arrayIndex] = value;
	m_arrayIndex = (m_arrayIndex + 1) % CAPTURED_FRAMES_DT;
}

float Benchmark::GetAverageDT()
{
	float total = 0.f;
	size_t arraySize = m_arrayFull ? CAPTURED_FRAMES_DT : m_arrayIndex;

	for (size_t i = 0; i < arraySize; i++)
	{
		total += m_deltatimes[i];
	}
	return total / static_cast<float>(arraySize);
}