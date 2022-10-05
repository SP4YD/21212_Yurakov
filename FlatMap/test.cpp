#include <gtest/gtest.h>
#include "FlatMap.hpp"

TEST (InsertTest, InsertAnEmpty) {
    TFlatMap fm;
    TValue val (18, 70);
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_EQ (fm["nikita"].Age, val.Age);
    EXPECT_EQ (fm["nikita"].Weight, val.Weight);
}
TEST (InsertTest, InsertTwoElements) {
    TFlatMap fm;
    TValue val (1, 1);
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_EQ (fm["nikita"].Age, val.Age);
    EXPECT_EQ (fm["nikita"].Weight, val.Weight);

    val = TValue (2, 2);
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_EQ (fm["vlad"].Age, val.Age);
    EXPECT_EQ (fm["vlad"].Weight, val.Weight);
}
TEST (InsertTest, InsertToBegin) {
    TFlatMap fm;
    TValue val (1, 1);
    EXPECT_TRUE (fm.insert ("a1", val));
    EXPECT_TRUE (fm.insert ("a2", val));
    EXPECT_TRUE (fm.insert ("a3", val));

    val = TValue (10, 100);
    EXPECT_TRUE (fm.insert ("a0", val));
    EXPECT_EQ (fm["a0"].Age, val.Age);
    EXPECT_EQ (fm["a0"].Weight, val.Weight);
}
TEST (InsertTest, InsertToEnd) {
    TFlatMap fm;
    TValue val (1, 1);
    EXPECT_TRUE (fm.insert ("a1", val));
    EXPECT_TRUE (fm.insert ("a2", val));
    EXPECT_TRUE (fm.insert ("a3", val));

    val = TValue (10, 100);
    EXPECT_TRUE (fm.insert ("test", val));
    EXPECT_EQ (fm["test"].Age, val.Age);
    EXPECT_EQ (fm["test"].Weight, val.Weight);
}
TEST (InsertTest, InsertToMid) {
    TFlatMap fm;
    TValue val (1, 1);
    EXPECT_TRUE (fm.insert ("a1", val));
    EXPECT_TRUE (fm.insert ("a2", val));
    EXPECT_TRUE (fm.insert ("a4", val));
    EXPECT_TRUE (fm.insert ("a5", val));

    val = TValue (10, 100);
    EXPECT_TRUE (fm.insert ("a3", val));
    EXPECT_EQ (fm["a3"].Age, val.Age);
    EXPECT_EQ (fm["a3"].Weight, val.Weight);
}
TEST (InsertTest, InsertAnExisting) {
    TFlatMap fm;
    TValue val1 (1, 1);
    EXPECT_TRUE (fm.insert ("a", val1));

    TValue val2 (2, 3);
    EXPECT_FALSE (fm.insert ("a", val2));
    EXPECT_EQ (fm["a"].Age, val1.Age);
    EXPECT_EQ (fm["a"].Weight, val1.Weight);
}
TEST (InsertTest, InsertElThatHasBeenDeleted) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.erase ("nikita"));
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.contains ("nikita"));
}
TEST (InsertTest, InsertAfterClear) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_TRUE (fm.insert ("egor", val));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));

    EXPECT_NO_THROW (fm.clear ());
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_TRUE (fm.insert ("egor", val));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));
}
TEST (InsertTest, IncreaseOfAllocatedMemoryAfterInsert) {
    TFlatMap fm;
    sKey key = "a";
    for (int i = 0; i < 20; ++i) {
      EXPECT_TRUE (fm.insert (key, TValue (i , i)));
      EXPECT_TRUE (fm.contains (key));
      EXPECT_TRUE (fm[key] == TValue (i , i));
      key += "a";
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (EraseTest, EraseFistEl) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_TRUE (fm.insert ("egor", val));
    EXPECT_TRUE (fm.insert ("den", val));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));
    EXPECT_TRUE (fm.contains ("den"));

    EXPECT_TRUE (fm.erase ("nikita"));
    EXPECT_FALSE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));
    EXPECT_TRUE (fm.contains ("den"));
}
TEST (EraseTest, EraseLastEl) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_TRUE (fm.insert ("egor", val));
    EXPECT_TRUE (fm.insert ("den", val));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));
    EXPECT_TRUE (fm.contains ("den"));

    EXPECT_TRUE (fm.erase ("den"));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));
    EXPECT_FALSE (fm.contains ("den"));
}
TEST (EraseTest, EraseCentralEl) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_TRUE (fm.insert ("egor", val));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));

    EXPECT_TRUE (fm.erase ("vlad"));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_FALSE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));
}
TEST (EraseTest, EraseAllEl) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_TRUE (fm.insert ("egor", val));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));

    EXPECT_TRUE (fm.erase ("nikita"));
    EXPECT_TRUE (fm.erase ("vlad"));
    EXPECT_TRUE (fm.erase ("egor"));
    EXPECT_FALSE (fm.contains ("nikita"));
    EXPECT_FALSE (fm.contains ("vlad"));
    EXPECT_FALSE (fm.contains ("egor"));
}
TEST (EraseTest, EraseErased) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.erase ("nikita"));
    EXPECT_FALSE (fm.contains ("nikita"));
    EXPECT_FALSE (fm.erase ("nikita"));
    EXPECT_FALSE (fm.contains ("nikita"));
}
TEST (EraseTest, EraseFromEmptyArr) {
    TFlatMap fm;
    EXPECT_FALSE (fm.erase ("nikita"));
    EXPECT_FALSE (fm.erase ("vlad"));
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.erase ("nikita"));
    EXPECT_FALSE (fm.erase ("nikita"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (ClearTest, ClearEmpty) {
    TFlatMap fm;
    EXPECT_NO_THROW (fm.clear ());
}
TEST (ClearTest, ClearAfterInsert) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_NO_THROW (fm.clear ());
}
TEST (ClearTest, ClearCleared) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_NO_THROW (fm.clear ());
    EXPECT_NO_THROW (fm.clear ());
}
TEST (ClearTest, ClearAfterErase) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.erase ("nikita"));
    EXPECT_NO_THROW (fm.clear ());
}
TEST (ClearTest, ClearArr) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_TRUE (fm.insert ("egor", val));
    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));

    EXPECT_NO_THROW (fm.clear ());
    EXPECT_FALSE (fm.contains ("nikita"));
    EXPECT_FALSE (fm.contains ("vlad"));
    EXPECT_FALSE (fm.contains ("egor"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (ContainsTest, ContainsExisting) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_TRUE (fm.insert ("egor", val));

    EXPECT_TRUE (fm.contains ("nikita"));
    EXPECT_TRUE (fm.contains ("vlad"));
    EXPECT_TRUE (fm.contains ("egor"));
}
TEST (ContainsTest, ContainsNotExisting) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.insert ("vlad", val));
    EXPECT_TRUE (fm.insert ("egor", val));

    EXPECT_FALSE (fm.contains ("den"));
    EXPECT_FALSE (fm.contains ("nikit"));
}
TEST (ContainsTest, ContainsInEmptyArr) {
    TFlatMap fm;
    EXPECT_FALSE (fm.contains ("nikita"));
    EXPECT_FALSE (fm.contains ("a"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (SizeTest, SizeEmptyArr) {
    TFlatMap fm;
    EXPECT_EQ (fm.size (), 0);
}
TEST (SizeTest, SizeSomeEl) {
    TFlatMap fm;
    TValue val;
    int fmSize = 0;

    EXPECT_TRUE (fm.insert ("nikita", val));
    fmSize++;
    EXPECT_TRUE (fm.insert ("vlad", val));
    fmSize++;
    EXPECT_TRUE (fm.insert ("egor", val));
    fmSize++;

    EXPECT_EQ (fm.size (), fmSize);
}
TEST (SizeTest, SizeAfterErase) {
    TFlatMap fm;
    TValue val;
    int fmSize = 0;
    EXPECT_TRUE (fm.insert ("nikita", val)); fmSize++;
    EXPECT_TRUE (fm.insert ("vlad", val)); fmSize++;
    EXPECT_TRUE (fm.insert ("egor", val)); fmSize++;
    EXPECT_EQ (fm.size (), fmSize);
    EXPECT_TRUE (fm.erase ("nikita")); fmSize--;
    EXPECT_EQ (fm.size (), fmSize);
    EXPECT_TRUE (fm.erase ("vlad")); fmSize--;
    EXPECT_EQ (fm.size (), fmSize);
    EXPECT_TRUE (fm.erase ("egor")); fmSize--;
    EXPECT_EQ (fm.size (), fmSize);
}
TEST (SizeTest, SizeAfterClear) {
    TFlatMap fm;
    TValue val;
    int fmSize = 0;
    EXPECT_TRUE (fm.insert ("nikita", val)); fmSize++;
    EXPECT_TRUE (fm.insert ("vlad", val)); fmSize++;
    EXPECT_TRUE (fm.insert ("egor", val)); fmSize++;
    EXPECT_EQ (fm.size (), fmSize);
    EXPECT_NO_THROW (fm.clear ()); fmSize = 0;
    EXPECT_EQ (fm.size (), fmSize);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (EmptyTest, CheckEmptyArr) {
    TFlatMap fm;
    EXPECT_TRUE (fm.empty ());
}
TEST (EmptyTest, CheckNotEmptyArr) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_FALSE (fm.empty ());
}
TEST (EmptyTest, CheckArrAfterErase) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_TRUE (fm.erase ("nikita"));
    EXPECT_TRUE (fm.empty ());
}
TEST (EmptyTest, CheckArrAfterClear) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("nikita", val));
    EXPECT_NO_THROW (fm.clear ());
    EXPECT_TRUE (fm.empty ());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (BinarySearchTest, BinarySearchInEmptyArr) {
    TFlatMap fm;
    EXPECT_EQ (fm.BinarySearch ("1"), 0);
}
TEST (BinarySearchTest, BinarySearchInArrOfOneEl) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("2", val));
    EXPECT_EQ (fm.BinarySearch ("1"), 0);
    EXPECT_EQ (fm.BinarySearch ("3"), 1);
}
TEST (BinarySearchTest, BinarySearchInArrOfTwoEl) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("b", val));
    EXPECT_TRUE (fm.insert ("f", val));
    EXPECT_EQ (fm.BinarySearch ("a"), 0);
    EXPECT_EQ (fm.BinarySearch ("d"), 1);
    EXPECT_EQ (fm.BinarySearch ("z"), 2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (SwapTest, SimpleSwap) {
    TFlatMap fm1;
    TValue val1 (1, 2);
    EXPECT_TRUE (fm1.insert ("a1", val1));
    EXPECT_TRUE (fm1.insert ("a2", val1));
    EXPECT_TRUE (fm1.insert ("a3", val1));
    TFlatMap fm2;
    TValue val2 (3, 4);
    EXPECT_TRUE (fm2.insert ("b1", val2));
    EXPECT_TRUE (fm2.insert ("b2", val2));
    EXPECT_TRUE (fm2.insert ("b3", val2));

    EXPECT_NO_THROW (fm1.swap (fm2));
    EXPECT_TRUE (fm1.contains ("b1"));
    EXPECT_TRUE (fm1.contains ("b2"));
    EXPECT_TRUE (fm1.contains ("b3"));
    EXPECT_TRUE (fm2.contains ("a1"));
    EXPECT_TRUE (fm2.contains ("a2"));
    EXPECT_TRUE (fm2.contains ("a3"));
}
TEST (SwapTest, SwapYourself) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("a1", val));
    EXPECT_TRUE (fm.insert ("a2", val));
    EXPECT_TRUE (fm.insert ("a3", val));

    EXPECT_NO_THROW (fm.swap (fm));
    EXPECT_TRUE (fm.contains ("a1"));
    EXPECT_TRUE (fm.contains ("a2"));
    EXPECT_TRUE (fm.contains ("a3"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorNotEqTest, DifferentVal) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    EXPECT_TRUE (fm1.insert ("nikita", val1));
    EXPECT_TRUE (fm2.insert ("nikita", val2));
    EXPECT_TRUE (fm1 != fm2);
}
TEST (OperatorNotEqTest, DifferentKey) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    EXPECT_TRUE (fm1.insert ("nikita", val));
    EXPECT_TRUE (fm2.insert ("vlad", val));
    EXPECT_TRUE (fm1 != fm2);
}
TEST (OperatorNotEqTest, EqualFlatMap) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    EXPECT_TRUE (fm1.insert ("nikita", val));
    EXPECT_TRUE (fm2.insert ("nikita", val));
    EXPECT_FALSE (fm1 != fm2);
}
TEST (OperatorNotEqTest, CompareYourself) {
    TFlatMap fm1;
    TValue val;
    EXPECT_TRUE (fm1.insert ("nikita", val));
    EXPECT_FALSE (fm1 != fm1);
}
TEST (OperatorNotEqTest, DifferentSize) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    EXPECT_TRUE (fm1.insert ("nikita", val));
    EXPECT_TRUE (fm2.insert ("vlad", val));
    EXPECT_TRUE (fm2.insert ("egor", val));
    EXPECT_TRUE (fm1 != fm2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorEqTest, DifferentVal) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    EXPECT_TRUE (fm1.insert ("nikita", val1));
    EXPECT_TRUE (fm2.insert ("nikita", val2));
    EXPECT_FALSE (fm1 == fm2);
}
TEST (OperatorEqTest, DifferentKey) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    EXPECT_TRUE (fm1.insert ("nikita", val));
    EXPECT_TRUE (fm2.insert ("vlad", val));
    EXPECT_FALSE (fm1 == fm2);
}
TEST (OperatorEqTest, EqualFlatMap) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    EXPECT_TRUE (fm1.insert ("nikita", val));
    EXPECT_TRUE (fm2.insert ("nikita", val));
    EXPECT_TRUE (fm1 == fm2);
}
TEST (OperatorEqTest, CompareYourself) {
    TFlatMap fm1;
    TValue val;
    EXPECT_TRUE (fm1.insert ("nikita", val));
    EXPECT_TRUE (fm1 == fm1);
}
TEST (OperatorEqTest, DifferentSize) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    EXPECT_TRUE (fm1.insert ("nikita", val));
    EXPECT_TRUE (fm2.insert ("vlad", val));
    EXPECT_TRUE (fm2.insert ("egor", val));
    EXPECT_FALSE (fm1 == fm2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (AtTest, AllElFromArr) {
    TFlatMap fm;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    TValue val3 (3, 3);
    EXPECT_TRUE (fm.insert ("a", val1));
    EXPECT_TRUE (fm.insert ("b", val2));
    EXPECT_TRUE (fm.insert ("c", val3));
    EXPECT_TRUE (fm.at ("a") == val1);
    EXPECT_TRUE (fm.at ("b") == val2);
    EXPECT_TRUE (fm.at ("c") == val3);
}
TEST (AtTest, ElFromEmptyArr) {
    TFlatMap fm;
    EXPECT_ANY_THROW (fm.at ("a"));
    EXPECT_ANY_THROW (fm.at ("b"));
    EXPECT_ANY_THROW (fm.at ("c"));
}
TEST (AtTest, ElThatDoesntExist) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("a", val));
    EXPECT_TRUE (fm.insert ("b", val));
    EXPECT_TRUE (fm.insert ("c", val));
    EXPECT_ANY_THROW (fm.at ("nikita"));
    EXPECT_ANY_THROW (fm.at ("vlad"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (ConstAtTest, AllElFromArr) {
    TFlatMap fm;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    TValue val3 (3, 3);
    EXPECT_TRUE (fm.insert ("a", val1));
    EXPECT_TRUE (fm.insert ("b", val2));
    EXPECT_TRUE (fm.insert ("c", val3));
    const TFlatMap fm2 = fm;
    EXPECT_TRUE (fm2.at ("a") == val1);
    EXPECT_TRUE (fm2.at ("b") == val2);
    EXPECT_TRUE (fm2.at ("c") == val3);
}
TEST (ConstAtTest, ElFromEmptyArr) {
    const TFlatMap fm;
    EXPECT_ANY_THROW (fm.at ("a"));
    EXPECT_ANY_THROW (fm.at ("b"));
    EXPECT_ANY_THROW (fm.at ("c"));
}
TEST (ConstAtTest, ElThatDoesntExist) {
    TFlatMap fm1;
    TValue val;
    EXPECT_TRUE (fm1.insert ("a", val));
    EXPECT_TRUE (fm1.insert ("b", val));
    EXPECT_TRUE (fm1.insert ("c", val));
    const TFlatMap fm2 = fm1;
    EXPECT_ANY_THROW (fm2.at ("nikita"));
    EXPECT_ANY_THROW (fm2.at ("vlad"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorSquareBracketsTest, AllElFromArr) {
    TFlatMap fm;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    TValue val3 (3, 3);
    EXPECT_TRUE (fm.insert ("a", val1));
    EXPECT_TRUE (fm.insert ("b", val2));
    EXPECT_TRUE (fm.insert ("c", val3));
    EXPECT_TRUE (fm["a"] == val1);
    EXPECT_TRUE (fm["b"] == val2);
    EXPECT_TRUE (fm["c"] == val3);
}
TEST (OperatorSquareBracketsTest, ElFromEmptyArr) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm["a"] == val);
    EXPECT_TRUE (fm["b"] == val);
    EXPECT_TRUE (fm["c"] == val);
}
TEST (OperatorSquareBracketsTest, ElThatDoesntExist) {
    TFlatMap fm;
    TValue val;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    TValue val3 (3, 3);
    EXPECT_TRUE (fm.insert ("a", val1));
    EXPECT_TRUE (fm.insert ("b", val2));
    EXPECT_TRUE (fm.insert ("c", val3));
    EXPECT_TRUE (fm["nikita"] == val);
    EXPECT_TRUE (fm["vlad"] == val);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorAssignLValTest, SimpleAssign) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    EXPECT_TRUE (fm1.insert ("a", val1));
    EXPECT_TRUE (fm1.insert ("b", val1));
    EXPECT_TRUE (fm1.insert ("c", val1));
    EXPECT_NO_THROW (fm2 = fm1);
    EXPECT_TRUE (fm2.contains ("a"));
    EXPECT_TRUE (fm2.contains ("b"));
    EXPECT_TRUE (fm2.contains ("c"));
    EXPECT_FALSE (fm2.contains ("d"));
}
TEST (OperatorAssignLValTest, CopyToNotEmpty) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    EXPECT_TRUE (fm2.insert ("a", val1));
    EXPECT_TRUE (fm2.insert ("b", val1));
    EXPECT_TRUE (fm2.insert ("c", val1));
    EXPECT_TRUE (fm1.insert ("a1", val2));
    EXPECT_TRUE (fm1.insert ("b1", val2));
    EXPECT_TRUE (fm1.insert ("c1", val2));
    EXPECT_NO_THROW (fm2 = fm1);
    EXPECT_TRUE (fm2.contains ("a1"));
    EXPECT_TRUE (fm2.contains ("b1"));
    EXPECT_TRUE (fm2.contains ("c1"));
    EXPECT_FALSE (fm2.contains ("a"));
    EXPECT_FALSE (fm2.contains ("b"));
    EXPECT_FALSE (fm2.contains ("c"));
}
TEST (OperatorAssignLValTest, CopyEmpty) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    EXPECT_TRUE (fm2.insert ("a", val));
    EXPECT_TRUE (fm2.insert ("b", val));
    EXPECT_TRUE (fm2.insert ("c", val));
    EXPECT_NO_THROW (fm2 = fm1);
    EXPECT_FALSE (fm2.contains ("a"));
    EXPECT_FALSE (fm2.contains ("b"));
    EXPECT_FALSE (fm2.contains ("c"));
    EXPECT_FALSE (fm2.contains ("d"));
}
TEST (OperatorAssignLValTest, CopyYourself) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("a", val));
    EXPECT_TRUE (fm.insert ("b", val));
    EXPECT_TRUE (fm.insert ("c", val));
    EXPECT_NO_THROW (fm = fm);
    EXPECT_TRUE (fm.contains ("a"));
    EXPECT_TRUE (fm.contains ("b"));
    EXPECT_TRUE (fm.contains ("c"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorAssignRValTest, SimpleAssign) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    EXPECT_TRUE (fm1.insert ("a", val));
    EXPECT_TRUE (fm1.insert ("b", val));
    EXPECT_TRUE (fm1.insert ("c", val));
    EXPECT_NO_THROW (fm2 = TFlatMap (fm1));
    EXPECT_TRUE (fm2.contains ("a"));
    EXPECT_TRUE (fm2.contains ("b"));
    EXPECT_TRUE (fm2.contains ("c"));
    EXPECT_FALSE (fm2.contains ("d"));
}
TEST (OperatorAssignRValTest, CopyToNotEmpty) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    EXPECT_TRUE (fm2.insert ("a", val1));
    EXPECT_TRUE (fm2.insert ("b", val1));
    EXPECT_TRUE (fm2.insert ("c", val1));
    EXPECT_TRUE (fm1.insert ("a1", val2));
    EXPECT_TRUE (fm1.insert ("b1", val2));
    EXPECT_TRUE (fm1.insert ("c1", val2));
    EXPECT_NO_THROW (fm2 = TFlatMap (fm1));
    fm1.clear ();
    EXPECT_TRUE (fm2.contains ("a1"));
    EXPECT_TRUE (fm2.contains ("b1"));
    EXPECT_TRUE (fm2.contains ("c1"));
    EXPECT_FALSE (fm2.contains ("a"));
    EXPECT_FALSE (fm2.contains ("b"));
    EXPECT_FALSE (fm2.contains ("c"));
}
TEST (OperatorAssignRValTest, CopyEmpty) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    EXPECT_TRUE (fm2.insert ("a", val));
    EXPECT_TRUE (fm2.insert ("b", val));
    EXPECT_TRUE (fm2.insert ("c", val));
    EXPECT_NO_THROW (fm2 = TFlatMap ());
    EXPECT_FALSE (fm2.contains ("a"));
    EXPECT_FALSE (fm2.contains ("b"));
    EXPECT_FALSE (fm2.contains ("c"));
    EXPECT_FALSE (fm2.contains ("d"));
}
TEST (OperatorAssignRValTest, CopyYourself) {
    TFlatMap fm;
    TValue val;
    EXPECT_TRUE (fm.insert ("a", val));
    EXPECT_TRUE (fm.insert ("b", val));
    EXPECT_TRUE (fm.insert ("c", val));
    EXPECT_NO_THROW (fm = TFlatMap (fm));
    EXPECT_TRUE (fm.contains ("a"));
    EXPECT_TRUE (fm.contains ("b"));
    EXPECT_TRUE (fm.contains ("c"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (DefaultConstructorTest, SimpleCreation) {
    TFlatMap fm;
    EXPECT_EQ (fm.size (), 0);
    EXPECT_FALSE (fm.contains ("a"));
    EXPECT_FALSE (fm.contains ("b"));
    EXPECT_TRUE (fm.empty ());
}
TEST (DefaultConstructorTest, InsertAfterDefaultConstructor) {
    TFlatMap fm;
    TValue val (1, 1);
    EXPECT_TRUE (fm.insert ("a", val));
    EXPECT_EQ (fm.size (), 1);
    EXPECT_TRUE (fm.contains ("a"));
    EXPECT_TRUE (fm["a"] == val);
    EXPECT_FALSE (fm.contains ("b"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (CopyConstructor, SimpleCopy) {
    TFlatMap fm;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    EXPECT_TRUE (fm.insert ("a", val1));
    EXPECT_TRUE (fm.insert ("b", val2));
    TFlatMap fm2 (fm);
    EXPECT_TRUE (fm2.contains ("a"));
    EXPECT_TRUE (fm2["a"] == val1);
    EXPECT_TRUE (fm2.contains ("b"));
    EXPECT_TRUE (fm2["b"] == val2);
    EXPECT_EQ (fm2.size (), 2);
}
TEST (CopyConstructor, CopyEmpty) {
    TFlatMap fm;
    TFlatMap fm2 (fm);
    EXPECT_FALSE (fm2.contains ("a"));
    EXPECT_FALSE (fm2.contains ("b"));
    EXPECT_EQ (fm2.size (), 0);
    EXPECT_TRUE (fm2.empty ());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (MoveConstructor, SimpleCopy) {
    TFlatMap fm;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    EXPECT_TRUE (fm.insert ("a", val1));
    EXPECT_TRUE (fm.insert ("b", val2));
    TFlatMap fm2 (std::move(fm));
    EXPECT_TRUE (fm2.contains ("a"));
    EXPECT_TRUE (fm2["a"] == val1);
    EXPECT_TRUE (fm2.contains ("b"));
    EXPECT_TRUE (fm2["b"] == val2);
    EXPECT_EQ (fm2.size (), 2);
}
TEST (MoveConstructor, CopyEmpty) {
    TFlatMap fm;
    TFlatMap fm2 (std::move(fm));
    EXPECT_FALSE (fm2.contains ("a"));
    EXPECT_FALSE (fm2.contains ("b"));
    EXPECT_EQ (fm2.size (), 0);
    EXPECT_TRUE (fm2.empty ());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}