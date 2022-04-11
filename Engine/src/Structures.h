#pragma once
#include "PCH.h"

enum class ETagType : uint
{
	none,
	player,
	enemy,
	goodfood,
	badfood
};

struct Health
{
	uint current = { 0 };
	uint max	 = { 100};
};