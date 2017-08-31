#include "stdafx.h"
#include "..\Simulator\Simulator.h"
#include "CppUnitTest.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimulatorTest
{

	TEST_CLASS(Simulator_Test)
	{
	public:

		TEST_METHOD(convert_LLH_to_ECEF)
		{
			Simulator* simu;
			//simu->llh2ecef(50.0,50.0);
			Assert::Fail(L"Implement me");
		}

	};
}