/**
 * @file RRTCarrotTest.cpp
 *
 * @date   Feb 23, 2013
 * @author Adam Panzica
 * @brief Test Set for OccupancyGrid
 */

//License File

//****************SYSTEM DEPENDANCIES**************************//
#include<gtest/gtest.h>
//*****************LOCAL DEPENDANCIES**************************//
#include<aero_path_planning/OccupancyGrid.h>
//**********************NAMESPACES*****************************//
using namespace aero_path_planning;

 class OccupancyGridTest:public ::testing::Test
 {
 protected:
 	virtual void SetUp()
 	{
 		res_       = .1;

 		x_size_    = 50;
 		y_size_    = 50;
 		z_size_    = 0;

 		zero_.x    = 0;
 		zero_.y    = 0;
 		zero_.z    = 0;
 		zero_.rgba = 0;

 		pxpy_.x    = 10;
 		pxpy_.y    = 10;
 		pxpy_.z    = 0;
 		pxpy_.rgba = aero_path_planning::OBSTACLE;

 		pxny_.x    = 5;
 		pxny_.y    = -10;
 		pxny_.z    = 0;
 		pxny_.rgba = aero_path_planning::TENTACLE;

 		nxny_.x    = -10;
 		nxny_.y    = -5;
 		nxny_.z    = 0;
 		nxny_.rgba = aero_path_planning::FREE_LOW_COST;

 		nxpy_.x    = -5;
 		nxpy_.y    = 10;
 		nxpy_.z    = 0;
 		nxpy_.rgba = aero_path_planning::FREE_HIGH_COST;
 	}

 	double res_;

 	int x_size_;
 	int y_size_;
 	int z_size_;

 	Point zero_;
 	Point pxpy_;
 	Point nxny_;
 	Point pxny_;
 	Point nxpy_;

 };

 /**
 * @author Adam Panzica
 * @brief  Neive tests of constructors
 */
 TEST_F(OccupancyGridTest, testBasicSetupAndSize)
 {
 	//Test empty constructor
 	OccupancyGrid testGrid;
 	ASSERT_EQ(0, testGrid.size());

 	//Test 2D constructor
 	OccupancyGrid testGrid2D(x_size_, y_size_, res_, zero_);
 	ASSERT_EQ(x_size_  , testGrid2D.getXSize());
 	ASSERT_EQ(y_size_  , testGrid2D.getYSize());
 	ASSERT_EQ(z_size_  , testGrid2D.getZSize());
 	ASSERT_EQ((x_size_+1)*(y_size_+1), testGrid2D.size());

 	//Test 3D constructor
 	OccupancyGrid testGrid3D(x_size_, y_size_, z_size_, res_, zero_);
 	ASSERT_EQ(x_size_  , testGrid3D.getXSize());
 	ASSERT_EQ(y_size_  , testGrid3D.getYSize());
 	ASSERT_EQ(z_size_  , testGrid3D.getZSize());
 	ASSERT_EQ((x_size_+1)*(y_size_+1)*(z_size_+1), testGrid3D.size());

 	//Test Copy Constructor
 	OccupancyGrid testGridCopy(testGrid3D);
 	ASSERT_EQ(x_size_  , testGridCopy.getXSize());
 	ASSERT_EQ(y_size_  , testGridCopy.getYSize());
 	ASSERT_EQ(z_size_  , testGridCopy.getZSize());
 	ASSERT_EQ((x_size_+1)*(y_size_+1)*(z_size_+1), testGridCopy.size());

 	//Test PointCloud based copy constructor
 	OccupancyGridCloud copyCloud;
 	OccupancyGrid testGridPCCopy(x_size_, y_size_, z_size_, res_, zero_, copyCloud);
 	ASSERT_EQ(x_size_  , testGridPCCopy.getXSize());
 	ASSERT_EQ(y_size_  , testGridPCCopy.getYSize());
 	ASSERT_EQ(z_size_  , testGridPCCopy.getZSize());
 	ASSERT_EQ((x_size_+1)*(y_size_+1)*(z_size_+1), testGridPCCopy.size());
 }

 TEST_F(OccupancyGridTest, testPointAccess)
 {
 	//Build a zero-origin'd grid. Can't test negative values here as they would throw exceptions and gtest doesn't support
 	OccupancyGrid testGrid3D(x_size_, y_size_, z_size_, res_, zero_);

 	PointTrait test1 = testGrid3D.getPointTrait(pxpy_.x, pxpy_.y, pxpy_.z);
 	PointTrait test2 = testGrid3D.getPointTrait(pxpy_);

 	ASSERT_EQ(aero_path_planning::UNKNOWN, test1);
 	ASSERT_EQ(aero_path_planning::UNKNOWN, test2);

 	//Build a non-zero origin'd grid.
 	OccupancyGrid testGrid3D2(x_size_, y_size_, z_size_, res_, pxpy_, aero_path_planning::FREE_LOW_COST);

 	PointTrait test3 = testGrid3D2.getPointTrait(pxpy_.x, pxpy_.y, pxpy_.z);
 	PointTrait test4 = testGrid3D2.getPointTrait(pxpy_);
 	PointTrait test5 = testGrid3D2.getPointTrait(nxny_.x, nxny_.y, nxny_.z);
 	PointTrait test6 = testGrid3D2.getPointTrait(nxny_);

 	ASSERT_EQ(aero_path_planning::FREE_LOW_COST, test3);
 	ASSERT_EQ(aero_path_planning::FREE_LOW_COST, test4);
 	ASSERT_EQ(aero_path_planning::FREE_LOW_COST, test5);
 	ASSERT_EQ(aero_path_planning::FREE_LOW_COST, test6);
 }

TEST_F(OccupancyGridTest, testPointTraitSetting)
{
 	//Build a non-zero origin'd grid.
 	OccupancyGrid testGrid3D(x_size_, y_size_, z_size_, res_, pxpy_, aero_path_planning::FREE_LOW_COST);
 	//Sanity check
 	PointTrait test1 = testGrid3D.getPointTrait(pxpy_);
 	PointTrait test2 = testGrid3D.getPointTrait(nxny_);
 	ASSERT_EQ(aero_path_planning::FREE_LOW_COST, test1);
 	ASSERT_EQ(aero_path_planning::FREE_LOW_COST, test2);

 	//Set some points to be obstacles
 	ASSERT_TRUE(testGrid3D.setPointTrait(pxpy_, aero_path_planning::OBSTACLE));
 	ASSERT_TRUE(testGrid3D.setPointTrait(pxny_, aero_path_planning::OBSTACLE));
 	//Set some points to be unknown
 	ASSERT_TRUE(testGrid3D.setPointTrait(nxny_, aero_path_planning::UNKNOWN));
 	ASSERT_TRUE(testGrid3D.setPointTrait(nxpy_, aero_path_planning::UNKNOWN));

 	//Check to see that those point traits were actually set
 	PointTrait test3 = testGrid3D.getPointTrait(pxpy_);
 	PointTrait test4 = testGrid3D.getPointTrait(nxny_);
 	PointTrait test5 = testGrid3D.getPointTrait(nxpy_);
 	PointTrait test6 = testGrid3D.getPointTrait(pxny_);

 	ASSERT_EQ(aero_path_planning::OBSTACLE, test3);
 	ASSERT_EQ(aero_path_planning::UNKNOWN,  test4);
 	ASSERT_EQ(aero_path_planning::UNKNOWN,  test5);
 	ASSERT_EQ(aero_path_planning::OBSTACLE, test6);
}
