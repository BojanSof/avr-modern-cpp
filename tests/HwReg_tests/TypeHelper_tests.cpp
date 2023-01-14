#include <stdint.h>

#include <gtest/gtest.h>

#include <HwReg/TypeHelper.hpp>

namespace Test
{
    TEST(HwRegTest, TypeHelperAssignmentOpTest)
    {
        using RegType = uint8_t;
        RegType hwReg = 0;  //< assume this is MMIO
        const auto hwRegAddr = reinterpret_cast<std::uintptr_t>(&hwReg);  //< address of MMIO
        HwReg::TypeHelper<decltype(hwRegAddr), RegType> regManipulator(hwRegAddr);
        ASSERT_EQ(hwReg, 0);
        regManipulator = 42;
        ASSERT_EQ(hwReg, 42);
    }

    TEST(HwRegTest, TypeHelperTypeConversionOpTest)
    {
        using RegType = uint8_t;
        RegType hwReg = 0b01101001;  //< assume this is MMIO
        const auto hwRegAddr = reinterpret_cast<std::uintptr_t>(&hwReg);  //< address of MMIO
        HwReg::TypeHelper<decltype(hwRegAddr), RegType> regManipulator(hwRegAddr);
        ASSERT_EQ(hwReg, 0b01101001);
        regManipulator = regManipulator | 0b11110011;
        ASSERT_EQ(hwReg, 0b11111011);
    }

}