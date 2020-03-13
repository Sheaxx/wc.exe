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

			Assert::AreEqual(searchfile("\0", "-c", name), 18);
			Assert::AreEqual(searchfile("\0", "-c", "*.c"), 21);
			Assert::AreEqual(searchfile("\0", "-w", name), 4);
			Assert::AreEqual(searchfile("\0", "-w", "*.c"), 5);
			Assert::AreEqual(searchfile("\0", "-l", name), 7);
			Assert::AreEqual(searchfile("\0", "-l", "*.c"), 8);
			Assert::AreEqual(searchfile("\0", "-a", name), 17);
			Assert::AreEqual(searchfile("\0", "-a", "*.c"), 18);
		}
	};
}