//
// Created by theo on 18/02/2020.
//

#include <gtest/gtest.h>

TEST(Model,untest) {
    double arr[2][3] =
            {
                    {1,8,12},
                    {5,9,13}
            };
    //Model* model = new Model((double **)arr, 3);
    ASSERT_EQ(6, 6);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}