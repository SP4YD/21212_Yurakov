#include "pch.h"
#include "FlatMap.cpp"

TEST (InsertTest, InsertAnEmpty) {
    TFlatMap fm;
    TValue val (18, 70);
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_EQ (fm["nikita"].Age, val.Age);
    ASSERT_EQ (fm["nikita"].Weight, val.Weight);
}
TEST (InsertTest, InsertTwoElements) {
    TFlatMap fm;
    TValue val (1, 1);
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_EQ (fm["nikita"].Age, val.Age);
    ASSERT_EQ (fm["nikita"].Weight, val.Weight);

    val = TValue (2, 2);
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_EQ (fm["vlad"].Age, val.Age);
    ASSERT_EQ (fm["vlad"].Weight, val.Weight);
}
TEST (InsertTest, InsertToBegin) {
    TFlatMap fm;
    TValue val (1, 1);
    ASSERT_TRUE (fm.insert ("a1", val));
    ASSERT_TRUE (fm.insert ("a2", val));
    ASSERT_TRUE (fm.insert ("a3", val));

    val = TValue (10, 100);
    ASSERT_TRUE (fm.insert ("a0", val));
    ASSERT_EQ (fm["a0"].Age, val.Age);
    ASSERT_EQ (fm["a0"].Weight, val.Weight);
}
TEST (InsertTest, InsertToEnd) {
    TFlatMap fm;
    TValue val (1, 1);
    ASSERT_TRUE (fm.insert ("a1", val));
    ASSERT_TRUE (fm.insert ("a2", val));
    ASSERT_TRUE (fm.insert ("a3", val));

    val = TValue (10, 100);
    ASSERT_TRUE (fm.insert ("test", val));
    ASSERT_EQ (fm["test"].Age, val.Age);
    ASSERT_EQ (fm["test"].Weight, val.Weight);
}
TEST (InsertTest, InsertToMid) {
    TFlatMap fm;
    TValue val (1, 1);
    ASSERT_TRUE (fm.insert ("a1", val));
    ASSERT_TRUE (fm.insert ("a2", val));
    ASSERT_TRUE (fm.insert ("a4", val));
    ASSERT_TRUE (fm.insert ("a5", val));

    val = TValue (10, 100);
    ASSERT_TRUE (fm.insert ("a3", val));
    ASSERT_EQ (fm["a3"].Age, val.Age);
    ASSERT_EQ (fm["a3"].Weight, val.Weight);
}
TEST (InsertTest, InsertAnExisting) {
    TFlatMap fm;
    TValue val1 (1, 1);
    ASSERT_TRUE (fm.insert ("a", val1));

    TValue val2 (2, 3);
    ASSERT_FALSE (fm.insert ("a", val2));
    ASSERT_EQ (fm["a"].Age, val1.Age);
    ASSERT_EQ (fm["a"].Weight, val1.Weight);
}
TEST (InsertTest, InsertElThatHasBeenDeleted) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.erase ("nikita"));
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.contains ("nikita"));
}
TEST (InsertTest, InsertAfterClear) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_TRUE (fm.insert ("egor", val));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));

    ASSERT_NO_THROW (fm.clear ());
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_TRUE (fm.insert ("egor", val));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (EraseTest, EraseFistEl) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_TRUE (fm.insert ("egor", val));
    ASSERT_TRUE (fm.insert ("den", val));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));
    ASSERT_TRUE (fm.contains ("den"));

    ASSERT_TRUE (fm.erase ("nikita"));
    ASSERT_FALSE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));
    ASSERT_TRUE (fm.contains ("den"));
}
TEST (EraseTest, EraseLastEl) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_TRUE (fm.insert ("egor", val));
    ASSERT_TRUE (fm.insert ("den", val));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));
    ASSERT_TRUE (fm.contains ("den"));

    ASSERT_TRUE (fm.erase ("den"));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));
    ASSERT_FALSE (fm.contains ("den"));
}
TEST (EraseTest, EraseCentralEl) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_TRUE (fm.insert ("egor", val));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));

    ASSERT_TRUE (fm.erase ("vlad"));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_FALSE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));
}
TEST (EraseTest, EraseAllEl) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_TRUE (fm.insert ("egor", val));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));

    ASSERT_TRUE (fm.erase ("nikita"));
    ASSERT_TRUE (fm.erase ("vlad"));
    ASSERT_TRUE (fm.erase ("egor"));
    ASSERT_FALSE (fm.contains ("nikita"));
    ASSERT_FALSE (fm.contains ("vlad"));
    ASSERT_FALSE (fm.contains ("egor"));
}
TEST (EraseTest, EraseErased) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.erase ("nikita"));
    ASSERT_FALSE (fm.contains ("nikita"));
    ASSERT_FALSE (fm.erase ("nikita"));
    ASSERT_FALSE (fm.contains ("nikita"));
}
TEST (EraseTest, EraseFromEmptyArr) {
    TFlatMap fm;
    ASSERT_FALSE (fm.erase ("nikita"));
    ASSERT_FALSE (fm.erase ("vlad"));
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.erase ("nikita"));
    ASSERT_FALSE (fm.erase ("nikita"));
    fm.PrintMap ();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (ClearTest, ClearEmpty) {
    TFlatMap fm;
    ASSERT_NO_THROW (fm.clear ());
}
TEST (ClearTest, ClearAfterInsert) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_NO_THROW (fm.clear ());
}
TEST (ClearTest, ClearCleared) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_NO_THROW (fm.clear ());
    ASSERT_NO_THROW (fm.clear ());
}
TEST (ClearTest, ClearAfterErase) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.erase ("nikita"));
    ASSERT_NO_THROW (fm.clear ());
}
TEST (ClearTest, ClearArr) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_TRUE (fm.insert ("egor", val));
    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));

    ASSERT_NO_THROW (fm.clear ());
    ASSERT_FALSE (fm.contains ("nikita"));
    ASSERT_FALSE (fm.contains ("vlad"));
    ASSERT_FALSE (fm.contains ("egor"));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (ContainsTest, ContainsExisting) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_TRUE (fm.insert ("egor", val));

    ASSERT_TRUE (fm.contains ("nikita"));
    ASSERT_TRUE (fm.contains ("vlad"));
    ASSERT_TRUE (fm.contains ("egor"));
}
TEST (ContainsTest, ContainsNotExisting) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.insert ("vlad", val));
    ASSERT_TRUE (fm.insert ("egor", val));

    ASSERT_FALSE (fm.contains ("den"));
    ASSERT_FALSE (fm.contains ("nikit"));
}
TEST (ContainsTest, ContainsInEmptyArr) {
    TFlatMap fm;
    ASSERT_FALSE (fm.contains ("nikita"));
    ASSERT_FALSE (fm.contains ("a"));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (SizeTest, SizeEmptyArr) {
    TFlatMap fm;
    ASSERT_EQ (fm.size (), 0);
}
TEST (SizeTest, SizeSomeEl) {
    TFlatMap fm;
    TValue val;
    int fmSize = 0;

    ASSERT_TRUE (fm.insert ("nikita", val));
    fmSize++;
    ASSERT_TRUE (fm.insert ("vlad", val));
    fmSize++;
    ASSERT_TRUE (fm.insert ("egor", val));
    fmSize++;

    ASSERT_EQ (fm.size (), fmSize);
}
TEST (SizeTest, SizeAfterErase) {
    TFlatMap fm;
    TValue val;
    int fmSize = 0;
    ASSERT_TRUE (fm.insert ("nikita", val)); fmSize++;
    ASSERT_TRUE (fm.insert ("vlad", val)); fmSize++;
    ASSERT_TRUE (fm.insert ("egor", val)); fmSize++;
    ASSERT_EQ (fm.size (), fmSize);
    ASSERT_TRUE (fm.erase ("nikita")); fmSize--;
    ASSERT_EQ (fm.size (), fmSize);
    ASSERT_TRUE (fm.erase ("vlad")); fmSize--;
    ASSERT_EQ (fm.size (), fmSize);
    ASSERT_TRUE (fm.erase ("egor")); fmSize--;
    ASSERT_EQ (fm.size (), fmSize);
}
TEST (SizeTest, SizeAfterClear) {
    TFlatMap fm;
    TValue val;
    int fmSize = 0;
    ASSERT_TRUE (fm.insert ("nikita", val)); fmSize++;
    ASSERT_TRUE (fm.insert ("vlad", val)); fmSize++;
    ASSERT_TRUE (fm.insert ("egor", val)); fmSize++;
    ASSERT_EQ (fm.size (), fmSize);
    ASSERT_NO_THROW (fm.clear ()); fmSize = 0;
    ASSERT_EQ (fm.size (), fmSize);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (EmptyTest, CheckEmptyArr) {
    TFlatMap fm;
    ASSERT_TRUE (fm.empty ());
}
TEST (EmptyTest, CheckNotEmptyArr) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_FALSE (fm.empty ());
}
TEST (EmptyTest, CheckArrAfterErase) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_TRUE (fm.erase ("nikita"));
    ASSERT_TRUE (fm.empty ());
}
TEST (EmptyTest, CheckArrAfterClear) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("nikita", val));
    ASSERT_NO_THROW (fm.clear ());
    ASSERT_TRUE (fm.empty ());
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (BinarySearchTest, BinarySearchInEmptyArr) {
    TFlatMap fm;
    ASSERT_EQ (fm.BinarySearch ("1"), 0);
}
TEST (BinarySearchTest, BinarySearchInArrOfOneEl) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("2", val));
    ASSERT_EQ (fm.BinarySearch ("1"), 0);
    ASSERT_EQ (fm.BinarySearch ("3"), 1);
}
TEST (BinarySearchTest, BinarySearchInArrOfTwoEl) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("b", val));
    ASSERT_TRUE (fm.insert ("f", val));
    ASSERT_EQ (fm.BinarySearch ("a"), 0);
    ASSERT_EQ (fm.BinarySearch ("d"), 1);
    ASSERT_EQ (fm.BinarySearch ("z"), 2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (SwapTest, SimpleSwap) {
    TFlatMap fm1;
    TValue val1 (1, 2);
    ASSERT_TRUE (fm1.insert ("a1", val1));
    ASSERT_TRUE (fm1.insert ("a2", val1));
    ASSERT_TRUE (fm1.insert ("a3", val1));
    TFlatMap fm2;
    TValue val2 (3, 4);
    ASSERT_TRUE (fm2.insert ("b1", val2));
    ASSERT_TRUE (fm2.insert ("b2", val2));
    ASSERT_TRUE (fm2.insert ("b3", val2));

    ASSERT_NO_THROW (fm1.swap (fm2));
    ASSERT_TRUE (fm1.contains ("b1"));
    ASSERT_TRUE (fm1.contains ("b2"));
    ASSERT_TRUE (fm1.contains ("b3"));
    ASSERT_TRUE (fm2.contains ("a1"));
    ASSERT_TRUE (fm2.contains ("a2"));
    ASSERT_TRUE (fm2.contains ("a3"));
}
TEST (SwapTest, SwapYourself) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("a1", val));
    ASSERT_TRUE (fm.insert ("a2", val));
    ASSERT_TRUE (fm.insert ("a3", val));

    ASSERT_NO_THROW (fm.swap (fm));
    ASSERT_TRUE (fm.contains ("a1"));
    ASSERT_TRUE (fm.contains ("a2"));
    ASSERT_TRUE (fm.contains ("a3"));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (MinTest, FirstMin) {
    int a = 5;
    int b = 4;
    ASSERT_EQ (min (a, b), 4);
}
TEST (MinTest, SecondMin) {
    int a = 4;
    int b = 5;
    ASSERT_EQ (min (a, b), 4);
}
TEST (MinTest, MinEq) {
    int a = 5;
    int b = 5;
    ASSERT_EQ (min (a, b), 5);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorNotEqTest, DifferentVal) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    ASSERT_TRUE (fm1.insert ("nikita", val1));
    ASSERT_TRUE (fm2.insert ("nikita", val2));
    ASSERT_TRUE (fm1 != fm2);
}
TEST (OperatorNotEqTest, DifferentKey) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    ASSERT_TRUE (fm1.insert ("nikita", val));
    ASSERT_TRUE (fm2.insert ("vlad", val));
    ASSERT_TRUE (fm1 != fm2);
}
TEST (OperatorNotEqTest, EqualFlatMap) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    ASSERT_TRUE (fm1.insert ("nikita", val));
    ASSERT_TRUE (fm2.insert ("nikita", val));
    ASSERT_FALSE (fm1 != fm2);
}
TEST (OperatorNotEqTest, CompareYourself) {
    TFlatMap fm1;
    TValue val;
    ASSERT_TRUE (fm1.insert ("nikita", val));
    ASSERT_FALSE (fm1 != fm1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorEqTest, DifferentVal) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    ASSERT_TRUE (fm1.insert ("nikita", val1));
    ASSERT_TRUE (fm2.insert ("nikita", val2));
    ASSERT_FALSE (fm1 == fm2);
}
TEST (OperatorEqTest, DifferentKey) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    ASSERT_TRUE (fm1.insert ("nikita", val));
    ASSERT_TRUE (fm2.insert ("vlad", val));
    ASSERT_FALSE (fm1 == fm2);
}
TEST (OperatorEqTest, EqualFlatMap) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    ASSERT_TRUE (fm1.insert ("nikita", val));
    ASSERT_TRUE (fm2.insert ("nikita", val));
    ASSERT_TRUE (fm1 == fm2);
}
TEST (OperatorEqTest, CompareYourself) {
    TFlatMap fm1;
    TValue val;
    ASSERT_TRUE (fm1.insert ("nikita", val));
    ASSERT_TRUE (fm1 == fm1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (AtTest, AllElFromArr) {
    TFlatMap fm;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    TValue val3 (3, 3);
    ASSERT_TRUE (fm.insert ("a", val1));
    ASSERT_TRUE (fm.insert ("b", val2));
    ASSERT_TRUE (fm.insert ("c", val3));
    ASSERT_TRUE (fm.at ("a") == val1);
    ASSERT_TRUE (fm.at ("b") == val2);
    ASSERT_TRUE (fm.at ("c") == val3);
}
TEST (AtTest, ElFromEmptyArr) {
    TFlatMap fm;
    ASSERT_ANY_THROW (fm.at ("a"));
    ASSERT_ANY_THROW (fm.at ("b"));
    ASSERT_ANY_THROW (fm.at ("c"));
}
TEST (AtTest, ElThatDoesntExist) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("a", val));
    ASSERT_TRUE (fm.insert ("b", val));
    ASSERT_TRUE (fm.insert ("c", val));
    ASSERT_ANY_THROW (fm.at ("nikita"));
    ASSERT_ANY_THROW (fm.at ("vlad"));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (ConstAtTest, AllElFromArr) {
    TFlatMap fm;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    TValue val3 (3, 3);
    ASSERT_TRUE (fm.insert ("a", val1));
    ASSERT_TRUE (fm.insert ("b", val2));
    ASSERT_TRUE (fm.insert ("c", val3));
    const TFlatMap fm2 = fm;
    ASSERT_TRUE (fm2.at ("a") == val1);
    ASSERT_TRUE (fm2.at ("b") == val2);
    ASSERT_TRUE (fm2.at ("c") == val3);
}
TEST (ConstAtTest, ElFromEmptyArr) {
    const TFlatMap fm;
    ASSERT_ANY_THROW (fm.at ("a"));
    ASSERT_ANY_THROW (fm.at ("b"));
    ASSERT_ANY_THROW (fm.at ("c"));
}
TEST (ConstAtTest, ElThatDoesntExist) {
    TFlatMap fm1;
    TValue val;
    ASSERT_TRUE (fm1.insert ("a", val));
    ASSERT_TRUE (fm1.insert ("b", val));
    ASSERT_TRUE (fm1.insert ("c", val));
    const TFlatMap fm2 = fm1;
    ASSERT_ANY_THROW (fm2.at ("nikita"));
    ASSERT_ANY_THROW (fm2.at ("vlad"));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorSquareBracketsTest, AllElFromArr) {
    TFlatMap fm;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    TValue val3 (3, 3);
    ASSERT_TRUE (fm.insert ("a", val1));
    ASSERT_TRUE (fm.insert ("b", val2));
    ASSERT_TRUE (fm.insert ("c", val3));
    ASSERT_TRUE (fm["a"] == val1);
    ASSERT_TRUE (fm["b"] == val2);
    ASSERT_TRUE (fm["c"] == val3);
}
TEST (OperatorSquareBracketsTest, ElFromEmptyArr) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm["a"] == val);
    ASSERT_TRUE (fm["b"] == val);
    ASSERT_TRUE (fm["c"] == val);
}
TEST (OperatorSquareBracketsTest, ElThatDoesntExist) {
    TFlatMap fm;
    TValue val;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    TValue val3 (3, 3);
    ASSERT_TRUE (fm.insert ("a", val1));
    ASSERT_TRUE (fm.insert ("b", val2));
    ASSERT_TRUE (fm.insert ("c", val3));
    ASSERT_TRUE (fm["nikita"] == val);
    ASSERT_TRUE (fm["vlad"] == val);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorAssignLValTest, SimpleAssign) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    ASSERT_TRUE (fm1.insert ("a", val1));
    ASSERT_TRUE (fm1.insert ("b", val1));
    ASSERT_TRUE (fm1.insert ("c", val1));
    ASSERT_NO_THROW (fm2 = fm1);
    ASSERT_TRUE (fm2.contains ("a"));
    ASSERT_TRUE (fm2.contains ("b"));
    ASSERT_TRUE (fm2.contains ("c"));
    ASSERT_FALSE (fm2.contains ("d"));
}
TEST (OperatorAssignLValTest, CopyToNotEmpty) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    ASSERT_TRUE (fm2.insert ("a", val1));
    ASSERT_TRUE (fm2.insert ("b", val1));
    ASSERT_TRUE (fm2.insert ("c", val1));
    ASSERT_TRUE (fm1.insert ("a1", val2));
    ASSERT_TRUE (fm1.insert ("b1", val2));
    ASSERT_TRUE (fm1.insert ("c1", val2));
    ASSERT_NO_THROW (fm2 = fm1);
    ASSERT_TRUE (fm2.contains ("a1"));
    ASSERT_TRUE (fm2.contains ("b1"));
    ASSERT_TRUE (fm2.contains ("c1"));
    ASSERT_FALSE (fm2.contains ("a"));
    ASSERT_FALSE (fm2.contains ("b"));
    ASSERT_FALSE (fm2.contains ("c"));
}
TEST (OperatorAssignLValTest, CopyEmpty) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    ASSERT_TRUE (fm2.insert ("a", val));
    ASSERT_TRUE (fm2.insert ("b", val));
    ASSERT_TRUE (fm2.insert ("c", val));
    ASSERT_NO_THROW (fm2 = fm1);
    ASSERT_FALSE (fm2.contains ("a"));
    ASSERT_FALSE (fm2.contains ("b"));
    ASSERT_FALSE (fm2.contains ("c"));
    ASSERT_FALSE (fm2.contains ("d"));
}
TEST (OperatorAssignLValTest, CopyYourself) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("a", val));
    ASSERT_TRUE (fm.insert ("b", val));
    ASSERT_TRUE (fm.insert ("c", val));
    ASSERT_NO_THROW (fm = fm);
    ASSERT_TRUE (fm.contains ("a"));
    ASSERT_TRUE (fm.contains ("b"));
    ASSERT_TRUE (fm.contains ("c"));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorAssignRValTest, SimpleAssign) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    ASSERT_TRUE (fm1.insert ("a", val));
    ASSERT_TRUE (fm1.insert ("b", val));
    ASSERT_TRUE (fm1.insert ("c", val));
    ASSERT_NO_THROW (fm2 = TFlatMap (fm1));
    ASSERT_TRUE (fm2.contains ("a"));
    ASSERT_TRUE (fm2.contains ("b"));
    ASSERT_TRUE (fm2.contains ("c"));
    ASSERT_FALSE (fm2.contains ("d"));
}
TEST (OperatorAssignRValTest, CopyToNotEmpty) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val1 (1, 1);
    TValue val2 (2, 2);
    ASSERT_TRUE (fm2.insert ("a", val1));
    ASSERT_TRUE (fm2.insert ("b", val1));
    ASSERT_TRUE (fm2.insert ("c", val1));
    ASSERT_TRUE (fm1.insert ("a1", val2));
    ASSERT_TRUE (fm1.insert ("b1", val2));
    ASSERT_TRUE (fm1.insert ("c1", val2));
    ASSERT_NO_THROW (fm2 = TFlatMap (fm1));
    fm1.clear ();
    ASSERT_TRUE (fm2.contains ("a1"));
    ASSERT_TRUE (fm2.contains ("b1"));
    ASSERT_TRUE (fm2.contains ("c1"));
    ASSERT_FALSE (fm2.contains ("a"));
    ASSERT_FALSE (fm2.contains ("b"));
    ASSERT_FALSE (fm2.contains ("c"));
}
TEST (OperatorAssignRValTest, CopyEmpty) {
    TFlatMap fm1;
    TFlatMap fm2;
    TValue val;
    ASSERT_TRUE (fm2.insert ("a", val));
    ASSERT_TRUE (fm2.insert ("b", val));
    ASSERT_TRUE (fm2.insert ("c", val));
    ASSERT_NO_THROW (fm2 = TFlatMap ());
    ASSERT_FALSE (fm2.contains ("a"));
    ASSERT_FALSE (fm2.contains ("b"));
    ASSERT_FALSE (fm2.contains ("c"));
    ASSERT_FALSE (fm2.contains ("d"));
}
TEST (OperatorAssignRValTest, CopyYourself) {
    TFlatMap fm;
    TValue val;
    ASSERT_TRUE (fm.insert ("a", val));
    ASSERT_TRUE (fm.insert ("b", val));
    ASSERT_TRUE (fm.insert ("c", val));
    ASSERT_NO_THROW (fm = TFlatMap (fm));
    ASSERT_TRUE (fm.contains ("a"));
    ASSERT_TRUE (fm.contains ("b"));
    ASSERT_TRUE (fm.contains ("c"));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////