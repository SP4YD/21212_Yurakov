#include "exceptions.hpp"
#include "Forth_Interpreter.hpp"

#include <gtest/gtest.h>

std::string GetOutput (std::stringstream& Out) {
	std::string tmp;
	std::string output;

	while (getline (Out, tmp, '\n')) {
		output += tmp + '\n';
	}
	if (output.length() > 0) {
		output.pop_back();
	}
	return output;
}

TEST (PushTest, PushNumberOnStack) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 5 6 . . .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 6 5 3 ");
}
TEST (PushTest, PushNumberOnStackWithoutPrint) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 5 6";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< ok");
}
TEST (PushTest, PushNumberGreaterThanIntMax) {
	std::stringstream In;
	std::stringstream Out;
	In << "2147483648";
	ForthInterpreter interpreter(In, Out);
	EXPECT_THROW (interpreter.RunInterpretation(false), std::overflow_error);
}
TEST (PushTest, PushNumberLessThanInt) {
	std::stringstream In;
	std::stringstream Out;
	In << "-2147483649";
	ForthInterpreter interpreter(In, Out);
	EXPECT_THROW (interpreter.RunInterpretation(false), std::overflow_error);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (DupTest, DupOneNumber) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 5 6 dup . . . .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 6 6 5 3 ");
}
TEST (DupTest, DupWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "dup";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (DropTest, DropOneNumberOnStack) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 5 6 drop . .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 5 3 ");
}
TEST (DropTest, DropWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "drop";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (SwapTest, SimpleSwap) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 5 6 swap . . .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 5 6 3 ");
}
TEST (SwapTest, SwapWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "swap";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (SwapTest, SwapWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 swap";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (RotTest, SimpleRot) {
	std::stringstream In;
	std::stringstream Out;
	In << "4 1 2 3 rot . . . .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 2 1 3 4 ");
}
TEST (RotTest, RotWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "rot";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (RotTest, RotWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 rot";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (RotTest, RotWhenOnStackTwoElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 2 rot";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OverTest, SimpleOver) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 2 1 over . . . .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 2 1 2 3 ");
}
TEST (OverTest, OverWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "over";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (OverTest, OverWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 over";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (EmitTest, SimpleEmit) {
	std::stringstream In;
	std::stringstream Out;
	In << "65 66 67 emit emit emit";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< C B A ");
}
TEST (EmitTest, EmitWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "emit";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (CrTest, SimpleCr) {
	std::stringstream In;
	std::stringstream Out;
	In << "100 200 . cr .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 200 \n< 100 ");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (MultipTest, SimpleMultip) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 3 * .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 9 ");
}
TEST (MultipTest, MultipWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "*";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (MultipTest, MultipWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 *";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (MultipTest, MultipWithResultZero) {
	std::stringstream In;
	std::stringstream Out;
	In << "200 0 * .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 0 ");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (DivisionTest, SimpleDivision) {
	std::stringstream In;
	std::stringstream Out;
	In << "15 3 / .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 5 ");
}
TEST (DivisionTest, DivisionWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "/";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (DivisionTest, DivisionWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 /";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (DivisionTest, DivisionByZero) {
	std::stringstream In;
	std::stringstream Out;
	In << "15 0 /";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_DivisionByZero);
}
TEST (DivisionTest, DivisionWithMinus) {
	std::stringstream In;
	std::stringstream Out;
	In << "15 -3 / .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);
	
	EXPECT_EQ (GetOutput(Out), "< -5 ");
}
TEST (DivisionTest, DivisionWithResultZero) {
	std::stringstream In;
	std::stringstream Out;
	In << "5 10 / .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);
	
	EXPECT_EQ (GetOutput(Out), "< 0 ");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (PlusTest, SimplePlus) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 3 + .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 6 ");
}
TEST (PlusTest, PlusWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "+";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (PlusTest, PlusWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 +";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (PlusTest, PlusWithResultZero) {
	std::stringstream In;
	std::stringstream Out;
	In << "200 -200 + .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 0 ");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (SubTest, SimpleSub) {
	std::stringstream In;
	std::stringstream Out;
	In << "10 3 - .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 7 ");
}
TEST (SubTest, SubWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "-";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (SubTest, SubWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 -";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (SubTest, SubWithResultZero) {
	std::stringstream In;
	std::stringstream Out;
	In << "-200 -200 - .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 0 ");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (ModTest, SimpleMod) {
	std::stringstream In;
	std::stringstream Out;
	In << "10 3 mod .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 1 ");
}
TEST (ModTest, ModWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "mod";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (ModTest, ModWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 mod";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (ModTest, ModWithResultZero) {
	std::stringstream In;
	std::stringstream Out;
	In << "0 3 mod .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 0 ");
}
TEST (ModTest, ModWithDivisionByZero) {
	std::stringstream In;
	std::stringstream Out;
	In << "100 0 mod";
	ForthInterpreter interpreter(In, Out);
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_DivisionByZero);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (LogOperEquallyTest, SimpleLogOperEqually) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 3 = . 3 2 = .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 1 0 ");
}
TEST (LogOperEquallyTest, LogOperEquallyWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "=";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (LogOperEquallyTest, LogOperEquallyWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 =";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (LogOperLessTest, SimpleLogOperLess) {
	std::stringstream In;
	std::stringstream Out;
	In << "2 3 < . 3 2 < .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 1 0 ");
}
TEST (LogOperLessTest, LogOperLessWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << "<";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (LogOperLessTest, LogOperLessWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 <";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (LogOperMoreTest, SimpleLogOperMore) {
	std::stringstream In;
	std::stringstream Out;
	In << "3 2 > . 2 3 > .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 1 0 ");
}
TEST (LogOperMoreTest, LogOperMoreWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << ">";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (LogOperMoreTest, LogOperMoreWhenOnStackOneElem) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 >";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (TestUnknownCommand, RandomCharacters) {
	std::stringstream In;
	std::stringstream Out;
	In << "sdfsdg";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_UnknownCommand);
}
TEST (TestUnknownCommand, ItLooksLikeTeamButNotThat_1) {
	std::stringstream In;
	std::stringstream Out;
	In << "moda";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_UnknownCommand);
}
TEST (TestUnknownCommand, ItLooksLikeTeamButNotThat_2) {
	std::stringstream In;
	std::stringstream Out;
	In << "ifa";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (PointTest, SimpleTest) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 2 3 4 5 . .";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 5 4 ");
}
TEST (PointTest, PointWhenStackEmpty) {
	std::stringstream In;
	std::stringstream Out;
	In << ".";
	ForthInterpreter interpreter(In, Out);
	
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (PrintingLineTest, SimpleTest) {
	std::stringstream In;
	std::stringstream Out;
	In << ".\" Hello World\"";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< Hello World ");
}
TEST (PrintingLineTest, WithoutText) {
	std::stringstream In;
	std::stringstream Out;
	In << ".\" \"";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "<  ");
}
TEST (PrintingLineTest, WithProblemSymbol) {
	std::stringstream In;
	std::stringstream Out;
	In << ".\" Hello\"World\"";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< Hello\"World ");
}
TEST (PrintingLineTest, TwoPrintInOneLine) {
	std::stringstream In;
	std::stringstream Out;
	In << ".\" Hello\" .\" World\"";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< Hello World ");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorIfTest, ExecutionBodyIf) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 if .\" Yes\" then ; .\" No\"";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< Yes No ");
}
TEST (OperatorIfTest, SkipBodyIf) {
	std::stringstream In;
	std::stringstream Out;
	In << "0 if .\" Yes\" then ; .\" No\"";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< No ");
}
TEST (OperatorIfTest, ExecutionBodyIfAndSkipElse) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 if .\" Yes\" else .\" No\" then ;";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< Yes ");
}
TEST (OperatorIfTest, ExecutionBodyElse) {
	std::stringstream In;
	std::stringstream Out;
	In << "0 if .\" Yes\" else .\" No\" then ;";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< No ");
}
TEST (OperatorIfTest, EmptyStack) {
	std::stringstream In;
	std::stringstream Out;
	In << "if .\" Yes\" else .\" No\" then ;";
	ForthInterpreter interpreter(In, Out);
	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (OperatorIfTest, NestedIf) {
	std::stringstream In;
	std::stringstream Out;
	In << "1 if 2 . 3 if 4 . 5 . else 0 . then ; then ;";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 2 4 5 ");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST (OperatorDoTest, SimpleTest) {
	std::stringstream In;
	std::stringstream Out;
	In << "10 0 do i . loop ;";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 0 1 2 3 4 5 6 7 8 9 ");
}
TEST (OperatorDoTest, OneParameterIsMissing) {
	std::stringstream In;
	std::stringstream Out;
	In << "0 do i . loop ;";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (OperatorDoTest, TwoParametersIsMissing) {
	std::stringstream In;
	std::stringstream Out;
	In << "do i . loop ;";
	ForthInterpreter interpreter(In, Out);

	EXPECT_THROW (interpreter.RunInterpretation(false), Exception_EmptyStack);
}
TEST (OperatorDoTest, NestedDo) {
	std::stringstream In;
	std::stringstream Out;
	In << "6 0 do i 1 + 0 do i . loop ; cr loop ;";
	ForthInterpreter interpreter(In, Out);
	interpreter.RunInterpretation(false);

	EXPECT_EQ (GetOutput(Out), "< 0 \n< 0 1 \n< 0 1 2 \n< 0 1 2 3 \n< 0 1 2 3 4 \n< 0 1 2 3 4 5 \n< ");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
