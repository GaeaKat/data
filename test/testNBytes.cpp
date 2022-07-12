// Copyright (c) 2019-2020 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <data/data.hpp>
#include <data/math/number/bytes/N.hpp>
#include "gtest/gtest.h"
#include <iostream>

namespace data::math::number {
    
    TEST(NBytesTest, TestStringToNBytes) {
        
        EXPECT_THROW(N_bytes<endian::big>{"a"}, std::logic_error);
        EXPECT_THROW(N_bytes<endian::big>{"-"}, std::logic_error);
        EXPECT_THROW(N_bytes<endian::big>{"-1"}, std::logic_error);
        EXPECT_THROW(N_bytes<endian::big>{"01"}, std::logic_error);
        EXPECT_THROW(N_bytes<endian::big>{"0x1"}, std::logic_error);
        
        EXPECT_THROW(N_bytes<endian::little>{"a"}, std::logic_error);
        EXPECT_THROW(N_bytes<endian::little>{"-"}, std::logic_error);
        EXPECT_THROW(N_bytes<endian::little>{"-1"}, std::logic_error);
        EXPECT_THROW(N_bytes<endian::little>{"01"}, std::logic_error);
        EXPECT_THROW(N_bytes<endian::little>{"0x1"}, std::logic_error);
        
        EXPECT_EQ(N_bytes<endian::big>{0}, N_bytes<endian::big>{});
        EXPECT_EQ(N_bytes<endian::big>{0}, N_bytes<endian::big>{""});
        EXPECT_EQ(N_bytes<endian::big>{0}, N_bytes<endian::big>{"0"});
        EXPECT_EQ(N_bytes<endian::big>{0}, N_bytes<endian::big>{"0x"});
        
        EXPECT_FALSE(N_bytes<endian::big>{1} == N_bytes<endian::big>{"0"});
        EXPECT_FALSE(N_bytes<endian::big>{0} == N_bytes<endian::big>{"1"});
        
        EXPECT_TRUE(N_bytes<endian::big>{1} == N_bytes<endian::big>{"1"});
        EXPECT_TRUE(N_bytes<endian::big>{1} == N_bytes<endian::big>{"0x01"});
        EXPECT_TRUE(N_bytes<endian::big>{1} == N_bytes<endian::big>{"0x0001"});
        
        EXPECT_EQ(N_bytes<endian::little>{0}, N_bytes<endian::little>{});
        EXPECT_EQ(N_bytes<endian::little>{0}, N_bytes<endian::little>{""});
        EXPECT_EQ(N_bytes<endian::little>{0}, N_bytes<endian::little>{"0"});
        EXPECT_EQ(N_bytes<endian::little>{0}, N_bytes<endian::little>{"0x"});
        
        EXPECT_FALSE(N_bytes<endian::little>{1} == N_bytes<endian::little>{"0"});
        EXPECT_FALSE(N_bytes<endian::little>{0} == N_bytes<endian::little>{"1"});
        
        EXPECT_TRUE(N_bytes<endian::little>{1} == N_bytes<endian::little>{"1"});
        EXPECT_TRUE(N_bytes<endian::little>{1} == N_bytes<endian::little>{"0x01"});
        EXPECT_TRUE(N_bytes<endian::little>{1} == N_bytes<endian::little>{"0x0001"});
        
        EXPECT_EQ(N_bytes<endian::big>{"23"}, N_bytes<endian::big>{23});
        EXPECT_EQ(N_bytes<endian::little>{"23"}, N_bytes<endian::little>{23});
        
    }
    
    TEST(NBytesTest, TestNBytesToHexString) {
        
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::big>{"0"}), std::string{"0x00"});
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::big>{"127"}), std::string{"0x7f"});
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::big>{"128"}), std::string{"0x80"});
        
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::little>{"0"}), std::string{"0x00"});
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::little>{"127"}), std::string{"0x7f"});
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::little>{"128"}), std::string{"0x80"});
        
    }
    
    TEST(NBytesTest, TestZeroSize) {
        
        EXPECT_EQ(N_bytes<endian::big>{"0x"}.size(), 0);
        EXPECT_EQ(N_bytes<endian::big>{"0x00"}.size(), 1);
        EXPECT_EQ(N_bytes<endian::big>{"0x000000"}.size(), 3);
        
        EXPECT_EQ(N_bytes<endian::little>{"0x"}.size(), 0);
        EXPECT_EQ(N_bytes<endian::little>{"0x00"}.size(), 1);
        EXPECT_EQ(N_bytes<endian::little>{"0x000000"}.size(), 3);
        
    }
    
    TEST(NBytesTest, TestZeroAndNegativeNBytes) {
        
        EXPECT_EQ(N_bytes<endian::big>{"0x"}, N_bytes<endian::big>{0});
        EXPECT_EQ(N_bytes<endian::big>{"0x00"}, N_bytes<endian::big>{0});
        EXPECT_EQ(N_bytes<endian::big>{"0x000000"}, N_bytes<endian::big>{0});
        EXPECT_EQ(N_bytes<endian::little>{"0x"}, N_bytes<endian::little>{0});
        EXPECT_EQ(N_bytes<endian::little>{"0x00"}, N_bytes<endian::little>{0});
        EXPECT_EQ(N_bytes<endian::little>{"0x000000"}, N_bytes<endian::little>{0});
        
        EXPECT_EQ(N_bytes<endian::big>{"0x01"}, N_bytes<endian::big>{1});
        EXPECT_EQ(N_bytes<endian::big>{"0x0001"}, N_bytes<endian::big>{1});
        EXPECT_EQ(N_bytes<endian::big>{"0x00000001"}, N_bytes<endian::big>{1});
        EXPECT_EQ(N_bytes<endian::little>{"0x01"}, N_bytes<endian::little>{1});
        EXPECT_EQ(N_bytes<endian::little>{"0x0001"}, N_bytes<endian::little>{1});
        EXPECT_EQ(N_bytes<endian::little>{"0x00000001"}, N_bytes<endian::little>{1});
        
    }
    
    // Problem: string reversal not happening correctly for some reason!!
    TEST(NBytesTest, TestNToNBytes) {
        
        EXPECT_EQ(N_bytes<endian::big>{N{"1"}}, N_bytes<endian::big>{"1"});
        EXPECT_EQ(N_bytes<endian::little>{N{"1"}}, N_bytes<endian::little>{"1"});
        EXPECT_EQ(N_bytes<endian::big>{N{"23"}}, N_bytes<endian::big>{"23"});
        EXPECT_EQ(N_bytes<endian::little>{N{"23"}}, N_bytes<endian::little>{"23"});
        EXPECT_EQ(N_bytes<endian::big>{N{"5704566599993321"}}, N_bytes<endian::big>{"5704566599993321"});
        EXPECT_EQ(N_bytes<endian::little>{N{"5704566599993321"}}, N_bytes<endian::little>{"5704566599993321"});
        
    }
    
    template <endian::order r> 
    struct test_bit_shift {
        void operator()(string num, int shift) {
            EXPECT_EQ(N_bytes<r>(num) >> shift, N_bytes<r>(num) << -shift);
            EXPECT_EQ(N_bytes<r>(num) << shift, N_bytes<r>(num) >> -shift);
            EXPECT_EQ(N(num) >> shift, N(N_bytes<r>(num) >> shift));
            EXPECT_EQ(N(num) << shift, N(N_bytes<r>(num) << shift));
        }
    };
    
    TEST(NBytesTest, TestNBitShift) {
        list<string> nums{"0", "1", "23", "5704566599993321"};
        list<int> shifts{0, 1, 5, 8, 15, 16};
        map_thread([](string num, int shift) -> int {
            test_bit_shift<endian::big>{}(num, shift);
            test_bit_shift<endian::little>{}(num, shift);
            return 0;
        }, nums, shifts);
        
    }
    
    TEST(NBytesTest, TestNBytesToString) {
        
        EXPECT_EQ(encoding::integer::write(N_bytes<endian::big>{1}), std::string{"1"});
        EXPECT_EQ(encoding::integer::write(N_bytes<endian::little>{1}), std::string{"1"});
        EXPECT_EQ(encoding::integer::write(N_bytes<endian::big>{23}), std::string{"23"});
        EXPECT_EQ(encoding::integer::write(N_bytes<endian::little>{23}), std::string{"23"});
        EXPECT_EQ(encoding::integer::write(N_bytes<endian::big>{"5704566599993321"}), std::string{"5704566599993321"});
        EXPECT_EQ(encoding::integer::write(N_bytes<endian::little>{"5704566599993321"}), std::string{"5704566599993321"});
        
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::big>{1}.trim()), std::string{"0x01"});
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::little>{1}.trim()), std::string{"0x01"});
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::big>{23}.trim()), std::string{"0x17"});
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::little>{23}.trim()), std::string{"0x17"});        
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::big>{"5704566599993321"}), std::string{"0x144445e9ca47e9"});
        EXPECT_EQ(encoding::hexidecimal::write(N_bytes<endian::little>{"5704566599993321"}), std::string{"0x144445e9ca47e9"});
        
    }
    
    TEST(NBytesTest, TestNBytesToN) {
        
        EXPECT_EQ(N{N_bytes<endian::big>{}}, N{0});
        EXPECT_EQ(N{N_bytes<endian::big>{""}}, N{0});
        EXPECT_EQ(N{N_bytes<endian::little>{}}, N{0});
        EXPECT_EQ(N{N_bytes<endian::little>{""}}, N{0});
        
    }
    
    TEST(NBytesTest, TestIncrement) {
        
        EXPECT_EQ(++N_bytes<endian::big>{"0x"}, N_bytes<endian::big>{1});
        EXPECT_EQ(++N_bytes<endian::big>{"0x00"}, N_bytes<endian::big>{1});
        EXPECT_EQ(++N_bytes<endian::big>{"0x000000"}, N_bytes<endian::big>{1});
        EXPECT_EQ(++N_bytes<endian::little>{"0x"}, N_bytes<endian::little>{1});
        EXPECT_EQ(++N_bytes<endian::little>{"0x00"}, N_bytes<endian::little>{1});
        EXPECT_EQ(++N_bytes<endian::little>{"0x000000"}, N_bytes<endian::little>{1});
        
    }
    
}

