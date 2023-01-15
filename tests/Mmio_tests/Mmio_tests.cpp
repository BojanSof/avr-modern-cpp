#include <stdint.h>

#include <gtest/gtest.h>

#include <Mmio/Register.hpp>

namespace Test
{
    TEST(MmioTest, RegisterAssignmentOpTest)
    {
        using RegType = uint8_t;
        RegType hwReg = 0;  //< assume this is MMIO
        const auto hwRegAddr = reinterpret_cast<std::uintptr_t>(&hwReg);  //< address of MMIO
        Mmio::Register<decltype(hwRegAddr), RegType> regManipulator(hwRegAddr);
        ASSERT_EQ(hwReg, 0);
        regManipulator = 42;
        ASSERT_EQ(hwReg, 42);
    }

    TEST(MmioTest, RegisterConversionOpTest)
    {
        using RegType = uint8_t;
        RegType hwReg = 0b01101001;  //< assume this is MMIO
        const auto hwRegAddr = reinterpret_cast<std::uintptr_t>(&hwReg);  //< address of MMIO
        Mmio::Register<decltype(hwRegAddr), RegType> regManipulator(hwRegAddr);
        ASSERT_EQ(hwReg, 0b01101001);
        regManipulator = regManipulator | 0b11110011;
        ASSERT_EQ(hwReg, 0b11111011);
    }

    TEST(MmioTest, RegisterOrAssignmentOpTest)
    {
        using RegType = uint8_t;
        RegType hwReg = 0b01101001;  //< assume this is MMIO
        const auto hwRegAddr = reinterpret_cast<std::uintptr_t>(&hwReg);  //< address of MMIO
        Mmio::Register<decltype(hwRegAddr), RegType> regManipulator(hwRegAddr);
        ASSERT_EQ(hwReg, 0b01101001);
        regManipulator |= 0b11110011;
        ASSERT_EQ(hwReg, 0b11111011);
    }

    TEST(MmioTest, RegisterAndAssignmentOpTest)
    {
        using RegType = uint8_t;
        RegType hwReg = 0b01101001;  //< assume this is MMIO
        const auto hwRegAddr = reinterpret_cast<std::uintptr_t>(&hwReg);  //< address of MMIO
        Mmio::Register<decltype(hwRegAddr), RegType> regManipulator(hwRegAddr);
        ASSERT_EQ(hwReg, 0b01101001);
        regManipulator &= 0b11110011;
        ASSERT_EQ(hwReg, 0b01100001);
    }

    TEST(MmioTest, RegisterSetBitTest)
    {
        using RegType = uint8_t;
        RegType hwReg = 0b01101001;  //< assume this is MMIO
        const auto hwRegAddr = reinterpret_cast<std::uintptr_t>(&hwReg);  //< address of MMIO
        Mmio::Register<decltype(hwRegAddr), RegType> regManipulator(hwRegAddr);
        ASSERT_EQ(hwReg, 0b01101001);
        regManipulator.setBit(1);
        ASSERT_EQ(hwReg, 0b01101011);
        regManipulator.setBit(7);
        ASSERT_EQ(hwReg, 0b11101011);
    }

    TEST(MmioTest, RegisterClearBitTest)
    {
        using RegType = uint8_t;
        RegType hwReg = 0b01101001;  //< assume this is MMIO
        const auto hwRegAddr = reinterpret_cast<std::uintptr_t>(&hwReg);  //< address of MMIO
        Mmio::Register<decltype(hwRegAddr), RegType> regManipulator(hwRegAddr);
        ASSERT_EQ(hwReg, 0b01101001);
        regManipulator.clearBit(0);
        ASSERT_EQ(hwReg, 0b01101000);
        regManipulator.clearBit(6);
        ASSERT_EQ(hwReg, 0b00101000);
    }
}