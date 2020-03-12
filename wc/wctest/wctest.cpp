#include "pch.h"
#include "CppUnitTest.h"
#include "../wc/wc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace wctest
{
	TEST_CLASS(wctest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char* path = "E:\\wc.exe\\wc\\Debug";
			char* name = "file.c";
			char* op = "-c";
			Assert::AreEqual(charactercount(name), 18);
			Assert::AreEqual(wordcount(name), 4);
			Assert::AreEqual(linecount1(name), 7);
			Assert::AreEqual(linecount2(name), 17);
			Assert::AreEqual(searchfile("E:\\wc.exe\\wc\\Debug", "file1.c", "-c"), 3);
		}
	};
}
