#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Simulator\trajectoryReader.h"
#include <iostream>
#include <fstream>
#include "..\Simulator\GNSStime.h"
#include "..\Simulator\CoordinateFrames.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimulatorTest
{
	TEST_CLASS(TrajectoryReaderTest)
	{
	public:

		TEST_METHOD(create_trajectoRreader_object){
			trajectoryReader testObject1;
			trajectoryReader* testObject2 = new trajectoryReader();
		}
		TEST_METHOD(create_trajectorReader_object_with_input_filename){
			char* fileName = "exampleFile.txt";
			trajectoryReader* testObject = new trajectoryReader(fileName);
		}
		TEST_METHOD(open_file){
			char* fileName = "exampleFile.txt";
			trajectoryReader* testObject = new trajectoryReader(fileName);
			testObject->open();
		}
		TEST_METHOD(close_file){
			char* fileName = "exampleFile.txt";
			trajectoryReader* testObject = new trajectoryReader(fileName);
			testObject->open();
			testObject->close();
		}
		TEST_METHOD(open_existing_file_and_close_it){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\simpleTrajectoryFile.txt";

			trajectoryReader* testObject = new trajectoryReader(fileName);
			testObject->open();

			std::ifstream ifs(fileName);	
			Assert::IsTrue(testObject->is_open());
			testObject->close();
			Assert::IsFalse(testObject->is_open());
		}
		TEST_METHOD(calling_destructor){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\simpleTrajectoryFile.txt";

			trajectoryReader* testObject = new trajectoryReader();
			testObject->~trajectoryReader();
			free(testObject);

			testObject = new trajectoryReader(fileName);
			testObject->~trajectoryReader();
		}
		TEST_METHOD(open_file_without_filename){

			trajectoryReader testObject;
			testObject.open();
		}
		TEST_METHOD(open_file_and_readline){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\exampleTrajectoryFile.txt";
			std::string firstLine("WN ToW LLH\n");
			trajectoryReader testObject(fileName);
			testObject.open();

			std::string line;
			line = testObject.readLine();
			Assert::IsTrue(firstLine.compare(line));
			testObject.close();
		}
		TEST_METHOD(read_file){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\exampleTrajectoryFile.txt";
			std::string line1("WN ToW LLH\n");
			std::string line2("1956 86400 45 45 100\n");
			std::string line3("1956 86401 44 46 101\n");
			std::string line4("1956 86402 43 47 102\n");
			std::string line5("1956 86403 42 48 103\n");
			std::string line6("1956 86404 41 49 104\n");

			trajectoryReader testObject(fileName);
			testObject.open();

			std::string line;

			line = testObject.readLine();
			Assert::IsTrue(line1.compare(line));
			line = testObject.readLine();
			Assert::IsTrue(line2.compare(line));
			line = testObject.readLine();
			Assert::IsTrue(line3.compare(line));
			line = testObject.readLine();
			Assert::IsTrue(line4.compare(line));
			line = testObject.readLine();
			Assert::IsTrue(line5.compare(line));
			line = testObject.readLine();
			Assert::IsTrue(line6.compare(line));
			testObject.close();
		}
		TEST_METHOD(read_first_line_and_parse_it_it_is_a_good_file_with_LLH_in_the_first_line){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewLLH.txt";
			std::string firstLine("WN ToW LLH\n");
			trajectoryReader testObject(fileName);
			testObject.open();

			Assert::IsTrue(testObject.isFormatValid());

			std::string line;
			line = testObject.readLine();

			Assert::IsTrue(firstLine.compare(line));
			testObject.close();
		}
		TEST_METHOD(read_first_line_and_parse_it_it_is_a_good_file_with_ECEF_in_the_first_line){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewECEF.txt";
			std::string firstLine("WN ToW ECEF\n");
			trajectoryReader testObject(fileName);
			testObject.open();

			Assert::IsTrue(testObject.isFormatValid());

			std::string line;
			line = testObject.readLine();

			Assert::IsTrue(firstLine.compare(line));
			testObject.close();
		}
		TEST_METHOD(read_first_line_and_parse_it_it_is_a_bad_file_w_missing_LLH_at_the_end){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\badTrajectoryFile1.txt";
			std::string firstLine("WN ToW\n");
			trajectoryReader testObject(fileName);
			testObject.open();

			Assert::IsFalse(testObject.isFormatValid());

			std::string line;
			line = testObject.readLine();

			Assert::IsTrue(firstLine.compare(line));
			testObject.close();

		}
		TEST_METHOD(read_first_line_and_parse_it_it_is_a_bad_file_w_missing_WN){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\badTrajectoryFile2.txt";
			std::string firstLine(" ToW LLH\n");
			trajectoryReader testObject(fileName);
			testObject.open();

			Assert::IsFalse(testObject.isFormatValid());

			std::string line;
			line = testObject.readLine();

			Assert::IsTrue(firstLine.compare(line));
			testObject.close();
		}
		TEST_METHOD(get_the_time_of_the_first_epoch){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewLLH.txt";
			std::string firstLine(" WN ToW LLH\n");
			trajectoryReader testObject(fileName);
			testObject.open();

			Assert::IsTrue(testObject.isFormatValid());

			std::string line;
			line = testObject.readLine();

			Assert::IsTrue(firstLine.compare(line));

			GPSTime time;
			time = testObject.nextTime();
			Assert::AreEqual(int(time.WN), 1956);
			Assert::AreEqual(int(time.ToW), 86400);
			testObject.close();
		}
		TEST_METHOD(get_the_time_of_the_first_and_second_epoch){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewLLH.txt";
			std::string firstLine(" WN ToW LLH\n");
			trajectoryReader testObject(fileName);
			testObject.open();

			Assert::IsTrue(testObject.isFormatValid());

			std::string line;
			line = testObject.readLine();

			Assert::IsTrue(firstLine.compare(line));

			GPSTime time;
			time = testObject.nextTime();
			Assert::AreEqual(int(time.WN), 1956);
			Assert::AreEqual(int(time.ToW), 86400);
			time = testObject.nextTime();
			Assert::AreEqual(int(time.WN), 1956);
			Assert::AreEqual(int(time.ToW), 86401);
			testObject.close();
		}

		TEST_METHOD(get_the_first_LLH_position_from_LLH_file){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewLLH.txt";
			trajectoryReader testObject(fileName);
			testObject.open();


			LLHCoordinate pos;
			pos = testObject.nextLLH();
			Assert::AreEqual(int(pos.latitude), 45);
			Assert::AreEqual(int(pos.longitude), 45);
			Assert::AreEqual(int(pos.height), 100);
			
			testObject.close();
		}

		TEST_METHOD(get_the_first_2_LLH_position_from_LLH_file){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewLLH.txt";
			trajectoryReader testObject(fileName);
			testObject.open();


			LLHCoordinate pos;
			pos = testObject.nextLLH();
			Assert::AreEqual(int(pos.latitude), 45);
			Assert::AreEqual(int(pos.longitude), 45);
			Assert::AreEqual(int(pos.height), 100);

			pos = testObject.nextLLH();
			Assert::AreEqual(int(pos.latitude), 44);
			Assert::AreEqual(int(pos.longitude), 46);
			Assert::AreEqual(int(pos.height), 101);

			testObject.close();
		}

		TEST_METHOD(get_the_first_ECEF_position_from_LLH_file){

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewLLH.txt";
			trajectoryReader testObject(fileName);
			testObject.open();


			ECEFCoordinate pos;
			pos = testObject.nextECEF();
			Assert::IsTrue(abs(double(pos.x) - 3194469.15)<0.1);
			Assert::IsTrue(abs(double(pos.y) - 3194469.15)<0.1);
			Assert::IsTrue(abs(double(pos.z) - 4487419.12)<0.1);

			/*pos = testObject.nextLLH();
			Assert::AreEqual(int(pos.latidute), 44);
			Assert::AreEqual(int(pos.longitude), 46);
			Assert::AreEqual(int(pos.height), 101);*/

			testObject.close();
		}

		TEST_METHOD(get_the_first_ECEF_position_from_ECEF_file) {

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewECEF.txt";
			trajectoryReader testObject(fileName);
			testObject.open();


			ECEFCoordinate pos;
			pos = testObject.nextECEF();
			Assert::IsTrue(abs(double(pos.x) - 3194469.15)<0.1);
			Assert::IsTrue(abs(double(pos.y) - 3194469.15)<0.1);
			Assert::IsTrue(abs(double(pos.z) - 4487419.12)<0.1);

			/*pos = testObject.nextLLH();
			Assert::AreEqual(int(pos.latidute), 44);
			Assert::AreEqual(int(pos.longitude), 46);
			Assert::AreEqual(int(pos.height), 101);*/

			testObject.close();
		}
		TEST_METHOD(get_the_first_2_ECEF_position_from_ECEF_file) {

			char* fileName = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewECEF.txt";
			trajectoryReader testObject(fileName);
			testObject.open();


			ECEFCoordinate pos;
			pos = testObject.nextECEF();
			Assert::IsTrue(abs(double(pos.x) - 3194469.15)<0.1);
			Assert::IsTrue(abs(double(pos.y) - 3194469.15)<0.1);
			Assert::IsTrue(abs(double(pos.z) - 4487419.12)<0.1);

			pos = testObject.nextECEF();
			Assert::IsTrue(abs(double(pos.x) - 3194469.15)<0.1);
			Assert::IsTrue(abs(double(pos.y) - 3194469.15)<0.1);
			Assert::IsTrue(abs(double(pos.z) - 4487419.12)<0.1);

			/*pos = testObject.nextLLH();
			Assert::AreEqual(int(pos.latidute), 44);
			Assert::AreEqual(int(pos.longitude), 46);
			Assert::AreEqual(int(pos.height), 101);*/

			testObject.close();
		}
		TEST_METHOD(read_line_as_structure_time_and_positions) {
			Assert::IsTrue(false);
		}
	};
	
}