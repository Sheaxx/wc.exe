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
			char* path = "\0";
			char* name = "file.c";
			Assert::AreEqual(charactercount(path, name), 18);
			Assert::AreEqual(wordcount(path, name), 4);
			Assert::AreEqual(linecount1(path, name), 7);
			Assert::AreEqual(linecount2(path, name), 17);
			

			Assert::AreEqual(searchfile(path, "-c", name), 18);
			Assert::AreEqual(searchfile(path, "-c", "*.c"), 30);
			Assert::AreEqual(searchfile(path, "-c", "fil?.c"), 27);
		
			Assert::AreEqual(searchfile(path, "-w", name), 4);
			Assert::AreEqual(searchfile(path, "-w", "*.c"), 6);
			Assert::AreEqual(searchfile(path, "-w", "fil?.c"), 5);

			Assert::AreEqual(searchfile(path, "-l", name), 7);
			Assert::AreEqual(searchfile(path, "-l", "*.c"), 9);
			Assert::AreEqual(searchfile(path, "-l", "fil?.c"), 8);

			Assert::AreEqual(searchfile(path, "-a", name), 17);
			Assert::AreEqual(searchfile(path, "-a", "*.c"), 19);
			Assert::AreEqual(searchfile(path, "-a", "fil?.c"), 18);
		}
	};
}