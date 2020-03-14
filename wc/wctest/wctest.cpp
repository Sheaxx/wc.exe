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
			char* path = "E:\\test\\";
			char* name = "file.c";
			Assert::AreEqual(charactercount(path, name), 63);
			Assert::AreEqual(wordcount(path, name), 9);
			Assert::AreEqual(linecount1(path, name), 7);
			Assert::AreEqual(linecount2(path, name), 19);
			
			
			Assert::AreEqual(searchfile(path, "-c", name), 63);
			Assert::AreEqual(searchfile(path, "-c", "*.c"), 84);
			Assert::AreEqual(searchfile(path, "-c", "*"), 93);
			Assert::AreEqual(searchfile(path, "-c", "fil?.c"), 81);
		
			Assert::AreEqual(searchfile(path, "-w", name), 9);
			Assert::AreEqual(searchfile(path, "-w", "*.c"), 13);
			Assert::AreEqual(searchfile(path, "-w", "*"), 16);
			Assert::AreEqual(searchfile(path, "-w", "fil?.c"), 12);
			
			Assert::AreEqual(searchfile(path, "-l", name), 7);
			Assert::AreEqual(searchfile(path, "-l", "*.c"), 14);
			Assert::AreEqual(searchfile(path, "-l", "*"), 19);
			Assert::AreEqual(searchfile(path, "-l", "fil?.c"), 13);
			
			Assert::AreEqual(searchfile(path, "-a", name), 19);
			Assert::AreEqual(searchfile(path, "-a", "*.c"), 32);
			Assert::AreEqual(searchfile(path, "-a", "*"), 45);
			Assert::AreEqual(searchfile(path, "-a", "fil?.c"), 31);
		}
	};
}