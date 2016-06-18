// NX 8.5.3.3
// Journal created by NicholasWang on Tue Apr 12 15:28:25 2016 中国标准时间
//
#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/Features_PointFeatureBuilder.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/Scalar.hxx>
#include <NXOpen/ScalarCollection.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/SmartObject.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/UnitCollection.hxx>
using namespace NXOpen;

extern "C" DllExport int ufusr_ask_unload()
{
    return (int)Session::LibraryUnloadOptionImmediately;
}

extern "C" DllExport void ufusr(char *param, int *retCode, int paramLen)
{
    Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    Part *displayPart(theSession->Parts()->Display());
    // ----------------------------------------------
    //   Menu: Insert->Datum/Point->Point...
    // ----------------------------------------------
    Session::UndoMarkId markId1;
    markId1 = theSession->SetUndoMark(Session::MarkVisibilityVisible, "Start");
    
    Unit *unit1(dynamic_cast<Unit *>(workPart->UnitCollection()->FindObject("MilliMeter")));
    Expression *expression1;
    expression1 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", unit1);
    
    Expression *expression2;
    expression2 = workPart->Expressions()->CreateSystemExpressionWithUnits("p7_x=0.00000000000", unit1);
    
    Expression *expression3;
    expression3 = workPart->Expressions()->CreateSystemExpressionWithUnits("p8_y=0.00000000000", unit1);
    
    Expression *expression4;
    expression4 = workPart->Expressions()->CreateSystemExpressionWithUnits("p9_z=0.00000000000", unit1);
    
    Expression *expression5;
    expression5 = workPart->Expressions()->CreateSystemExpressionWithUnits("p10_xdelta=0.00000000000", unit1);
    
    Expression *expression6;
    expression6 = workPart->Expressions()->CreateSystemExpressionWithUnits("p11_ydelta=0.00000000000", unit1);
    
    Expression *expression7;
    expression7 = workPart->Expressions()->CreateSystemExpressionWithUnits("p12_zdelta=0.00000000000", unit1);
    
    Expression *expression8;
    expression8 = workPart->Expressions()->CreateSystemExpressionWithUnits("p13_radius=0.00000000000", unit1);
    
    Unit *unit2(dynamic_cast<Unit *>(workPart->UnitCollection()->FindObject("Degrees")));
    Expression *expression9;
    expression9 = workPart->Expressions()->CreateSystemExpressionWithUnits("p14_angle=0.00000000000", unit2);
    
    Expression *expression10;
    expression10 = workPart->Expressions()->CreateSystemExpressionWithUnits("p15_zdelta=0.00000000000", unit1);
    
    Expression *expression11;
    expression11 = workPart->Expressions()->CreateSystemExpressionWithUnits("p16_radius=0.00000000000", unit1);
    
    Expression *expression12;
    expression12 = workPart->Expressions()->CreateSystemExpressionWithUnits("p17_angle1=0.00000000000", unit2);
    
    Expression *expression13;
    expression13 = workPart->Expressions()->CreateSystemExpressionWithUnits("p18_angle2=0.00000000000", unit2);
    
    Expression *expression14;
    expression14 = workPart->Expressions()->CreateSystemExpressionWithUnits("p19_distance=0", unit1);
    
    Expression *expression15;
    expression15 = workPart->Expressions()->CreateSystemExpressionWithUnits("p20_arclen=0", unit1);
    
    Unit *nullUnit(NULL);
    Expression *expression16;
    expression16 = workPart->Expressions()->CreateSystemExpressionWithUnits("p21_percent=0", nullUnit);
    
    expression2->SetRightHandSide("10");
    
    expression3->SetRightHandSide("20");
    
    expression4->SetRightHandSide("30");
    
    expression5->SetRightHandSide("0");
    
    expression6->SetRightHandSide("0");
    
    expression7->SetRightHandSide("0");
    
    expression8->SetRightHandSide("0");
    
    expression9->SetRightHandSide("0");
    
    expression10->SetRightHandSide("0");
    
    expression11->SetRightHandSide("0");
    
    expression12->SetRightHandSide("0");
    
    expression13->SetRightHandSide("0");
    
    expression14->SetRightHandSide("0");
    
    expression16->SetRightHandSide("100");
    
    expression15->SetRightHandSide("0");
    
    theSession->SetUndoMarkName(markId1, NXString("Point \345\257\271\350\257\235\346\241\206", NXString::UTF8));
    
    Expression *expression17;
    expression17 = workPart->Expressions()->CreateSystemExpressionWithUnits("p22_x=0.00000000000", unit1);
    
    Scalar *scalar1;
    scalar1 = workPart->Scalars()->CreateScalarExpression(expression17, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression18;
    expression18 = workPart->Expressions()->CreateSystemExpressionWithUnits("p23_y=0.00000000000", unit1);
    
    Scalar *scalar2;
    scalar2 = workPart->Scalars()->CreateScalarExpression(expression18, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression19;
    expression19 = workPart->Expressions()->CreateSystemExpressionWithUnits("p24_z=0.00000000000", unit1);
    
    Scalar *scalar3;
    scalar3 = workPart->Scalars()->CreateScalarExpression(expression19, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Point *point1;
    point1 = workPart->Points()->CreatePoint(scalar1, scalar2, scalar3, SmartObject::UpdateOptionWithinModeling);
    
    expression2->SetRightHandSide("0");
    
    expression3->SetRightHandSide("0");
    
    expression4->SetRightHandSide("0");
    
    expression2->SetRightHandSide("0.00000000000");
    
    expression3->SetRightHandSide("0.00000000000");
    
    expression4->SetRightHandSide("0.00000000000");
    
    expression2->SetRightHandSide("0");
    
    expression3->SetRightHandSide("0");
    
    expression4->SetRightHandSide("0");
    
    expression2->SetRightHandSide("0.00000000000");
    
    expression3->SetRightHandSide("0.00000000000");
    
    expression4->SetRightHandSide("0.00000000000");
    
    expression5->SetRightHandSide("0.00000000000");
    
    expression6->SetRightHandSide("0.00000000000");
    
    expression7->SetRightHandSide("0.00000000000");
    
    expression8->SetRightHandSide("0.00000000000");
    
    expression9->SetRightHandSide("0.00000000000");
    
    expression10->SetRightHandSide("0.00000000000");
    
    expression11->SetRightHandSide("0.00000000000");
    
    expression12->SetRightHandSide("0.00000000000");
    
    expression13->SetRightHandSide("0.00000000000");
    
    expression16->SetRightHandSide("100.00000000000");
    
    expression2->SetRightHandSide("0");
    
    expression3->SetRightHandSide("0");
    
    expression4->SetRightHandSide("0");
    
    expression2->SetRightHandSide("0.00000000000");
    
    expression3->SetRightHandSide("0.00000000000");
    
    expression4->SetRightHandSide("0.00000000000");
    
    expression2->SetRightHandSide("10.00000000000");
    
    workPart->Points()->DeletePoint(point1);
    
    expression2->SetRightHandSide("10.00000000000");
    
    expression3->SetRightHandSide("0.00000000000");
    
    expression4->SetRightHandSide("0.00000000000");
    
    Expression *expression20;
    expression20 = workPart->Expressions()->CreateSystemExpressionWithUnits("p8_x=10.00000000000", unit1);
    
    Scalar *scalar4;
    scalar4 = workPart->Scalars()->CreateScalarExpression(expression20, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression21;
    expression21 = workPart->Expressions()->CreateSystemExpressionWithUnits("p9_y=0.00000000000", unit1);
    
    Scalar *scalar5;
    scalar5 = workPart->Scalars()->CreateScalarExpression(expression21, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression22;
    expression22 = workPart->Expressions()->CreateSystemExpressionWithUnits("p10_z=0.00000000000", unit1);
    
    Scalar *scalar6;
    scalar6 = workPart->Scalars()->CreateScalarExpression(expression22, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Point *point2;
    point2 = workPart->Points()->CreatePoint(scalar4, scalar5, scalar6, SmartObject::UpdateOptionWithinModeling);
    
    expression3->SetRightHandSide("20.00000000000");
    
    expression2->SetRightHandSide("10.00000000000");
    
    expression3->SetRightHandSide("20.00000000000");
    
    expression4->SetRightHandSide("0.00000000000");
    
    workPart->Points()->DeletePoint(point2);
    
    Expression *expression23;
    expression23 = workPart->Expressions()->CreateSystemExpressionWithUnits("p8_x=10.00000000000", unit1);
    
    Scalar *scalar7;
    scalar7 = workPart->Scalars()->CreateScalarExpression(expression23, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression24;
    expression24 = workPart->Expressions()->CreateSystemExpressionWithUnits("p9_y=20.00000000000", unit1);
    
    Scalar *scalar8;
    scalar8 = workPart->Scalars()->CreateScalarExpression(expression24, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression25;
    expression25 = workPart->Expressions()->CreateSystemExpressionWithUnits("p10_z=0.00000000000", unit1);
    
    Scalar *scalar9;
    scalar9 = workPart->Scalars()->CreateScalarExpression(expression25, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Point *point3;
    point3 = workPart->Points()->CreatePoint(scalar7, scalar8, scalar9, SmartObject::UpdateOptionWithinModeling);
    
    expression4->SetRightHandSide("30.00000000000");
    
    expression2->SetRightHandSide("10.00000000000");
    
    expression3->SetRightHandSide("20.00000000000");
    
    expression4->SetRightHandSide("30.00000000000");
    
    workPart->Points()->DeletePoint(point3);
    
    Expression *expression26;
    expression26 = workPart->Expressions()->CreateSystemExpressionWithUnits("p8_x=10.00000000000", unit1);
    
    Scalar *scalar10;
    scalar10 = workPart->Scalars()->CreateScalarExpression(expression26, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression27;
    expression27 = workPart->Expressions()->CreateSystemExpressionWithUnits("p9_y=20.00000000000", unit1);
    
    Scalar *scalar11;
    scalar11 = workPart->Scalars()->CreateScalarExpression(expression27, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression28;
    expression28 = workPart->Expressions()->CreateSystemExpressionWithUnits("p10_z=30.00000000000", unit1);
    
    Scalar *scalar12;
    scalar12 = workPart->Scalars()->CreateScalarExpression(expression28, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Point *point4;
    point4 = workPart->Points()->CreatePoint(scalar10, scalar11, scalar12, SmartObject::UpdateOptionWithinModeling);
    
    Session::UndoMarkId markId2;
    markId2 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Point");
    
    theSession->DeleteUndoMark(markId2, NULL);
    
    Session::UndoMarkId markId3;
    markId3 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Point");
    
    expression2->SetRightHandSide("10.00000000000");
    
    expression3->SetRightHandSide("20.00000000000");
    
    expression4->SetRightHandSide("30.00000000000");
    
    workPart->Points()->DeletePoint(point4);
    
    Expression *expression29;
    expression29 = workPart->Expressions()->CreateSystemExpressionWithUnits("p8_x=10.00000000000", unit1);
    
    Scalar *scalar13;
    scalar13 = workPart->Scalars()->CreateScalarExpression(expression29, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression30;
    expression30 = workPart->Expressions()->CreateSystemExpressionWithUnits("p9_y=20.00000000000", unit1);
    
    Scalar *scalar14;
    scalar14 = workPart->Scalars()->CreateScalarExpression(expression30, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression31;
    expression31 = workPart->Expressions()->CreateSystemExpressionWithUnits("p10_z=30.00000000000", unit1);
    
    Scalar *scalar15;
    scalar15 = workPart->Scalars()->CreateScalarExpression(expression31, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Point *point5;
    point5 = workPart->Points()->CreatePoint(scalar13, scalar14, scalar15, SmartObject::UpdateOptionWithinModeling);
    
    theSession->DeleteUndoMark(markId3, NULL);
    
    theSession->SetUndoMarkName(markId1, "Point");
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression2);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression3);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression4);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression5);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression6);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression7);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression8);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression9);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression10);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression11);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression12);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression13);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression14);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression15);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression16);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    workPart->Expressions()->Delete(expression1);
    
    point5->SetVisibility(SmartObject::VisibilityOptionVisible);
    
    Features::Feature *nullFeatures_Feature(NULL);
    
    if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
    {
        throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
    }
    
    Features::PointFeatureBuilder *pointFeatureBuilder1;
    pointFeatureBuilder1 = workPart->BaseFeatures()->CreatePointFeatureBuilder(nullFeatures_Feature);
    
    pointFeatureBuilder1->SetPoint(point5);
    
    NXObject *nXObject1;
    nXObject1 = pointFeatureBuilder1->Commit();
    
    pointFeatureBuilder1->Destroy();
    
    // ----------------------------------------------
    //   Menu: Tools->Journal->Stop Recording
    // ----------------------------------------------
}
