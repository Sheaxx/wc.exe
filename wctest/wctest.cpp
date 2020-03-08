#include "pch.h"
#include "CppUnitTest.h"
#include "wc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace wctest
{
	TEST_CLASS(wctest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char* name = "file.c";
			Assert::AreEqual(character(name), 18);
		}
	};
}
