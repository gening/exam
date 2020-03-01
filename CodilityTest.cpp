//
// Created by Ning Ge on 2018/7/12.
//

#include <gtest/gtest.h>
#include "Codility.cpp"
#include <string>
#include <vector>

using namespace std;

class CodilityTest : public ::testing::Test {
protected:
    CodilityTest() {
        // You can do set-up work for each test here.
    }

    ~CodilityTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        strA = "This is the test string A.";
        vecA = {4, 4, 2, 4, 3, 4, 4, 4};
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for the name of this class.
    string strA;
    vector<int> vecA;
};

TEST_F(CodilityTest, OddOccurrencesInArray) {
    cout << OddOccurrencesInArray(vecA) << endl;
}

TEST_F(CodilityTest, TapeEquilibrium) {
    cout << TapeEquilibrium(vecA) << endl;
}

TEST_F(CodilityTest, Nesting) {
    cout << Nesting(strA) << endl;
}

TEST_F(CodilityTest, MinAvgTwoSlice) {
    cout << MinAvgTwoSlice(vecA) << endl;
}

TEST_F(CodilityTest, EquiLeader) {
    cout << EquiLeader(vecA) << endl;
}

TEST_F(CodilityTest, Dominator) {
    cout << Dominator(vecA) << endl;
}

TEST_F(CodilityTest, MaxSliceSum) {
    cout << MaxSliceSum(vecA) << endl;
}

TEST_F(CodilityTest, MaxDoubleSliceSum) {
    cout << MaxDoubleSliceSum(vecA) << endl;
}

TEST_F(CodilityTest, CountFactors) {
    cout << CountFactors(2147483647) << endl;
}

TEST_F(CodilityTest, MinPerimeterRectangle) {
    cout << MinPerimeterRectangle(1000000000) << endl;
}

TEST_F(CodilityTest, Peaks) {
    cout << Peaks(vecA) << endl;
}

TEST_F(CodilityTest, Flags) {
    cout << Flags(vecA) << endl;
}

TEST_F(CodilityTest, FindMissingNumber) {
    int arrayA[] =  {1, 3, 6, 4, 1, 2};
    cout << FindMissingNumber(arrayA, 6);
}
// main
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
