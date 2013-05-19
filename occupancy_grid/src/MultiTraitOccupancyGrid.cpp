/**
 * @file   OccupancyGrid.cpp
 *
 * @date   May 7, 2013
 * @author Adam Panzica
 * @brief  Implementation of the occupancy_grid namespace
 */

/*
 * Copyright (c) 2013, RIVeR Lab
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//*********** SYSTEM DEPENDANCIES ****************//
#include <boost/foreach.hpp>
//************ LOCAL DEPENDANCIES ****************//
#include <occupancy_grid/MultiTraitOccupancyGrid.hpp>
//***********    NAMESPACES     ****************//

using namespace occupancy_grid;
using namespace occupancy_grid::utilities;

//***************************************** CELLTRAIT *********************************************************//

CellTrait::CellTrait():
				enum_(UNKOWN)
{

}

CellTrait::CellTrait(Enum value):
				enum_(value)
{

}

CellTrait::CellTrait(int value)
{
	this->enum_ = enumFromValue(value);
}


CellTrait::Enum CellTrait::getEnum(void) const
{
	return this->enum_;
}

std::string CellTrait::getString(void) const
{
	return stringFromEnum(this->enum_);
}

int CellTrait::getValue(void) const
{
	return this->enum_;
}


std::ostream& CellTrait::operator<<(std::ostream& out) const
{
	out<<stringFromEnum(this->enum_);
	return out;
}

CellTrait& CellTrait::operator=(const CellTrait& rhs)
{
	this->enum_ = rhs.enum_;
	return *this;
}
CellTrait& CellTrait::operator=(const int& rhs)
{
	this->enum_ = enumFromValue(rhs);
	return *this;
}

bool CellTrait::operator==(const CellTrait& rhs) const
				{
	return rhs.enum_ == this->enum_;
				}
bool CellTrait::operator==(const int& rhs) const
				{
	return this->enum_ == enumFromValue(rhs);
				}

bool CellTrait::operator==(const Enum& rhs) const
				{
	return this->enum_ == rhs;
				}

CellTrait::Enum CellTrait::enumFromValue(int value)
{
	switch(value)
	{
	case FREE_LOW_COST:
		return FREE_LOW_COST;
		break;
	case FREE_HIGH_COST:
		return FREE_HIGH_COST;
		break;
	case OBSTACLE:
		return OBSTACLE;
		break;
	case GOAL:
		return GOAL;
		break;
	case TRAVERSED:
		return TRAVERSED;
		break;
	default:
		return  UNKOWN;
		break;
	}
	return UNKOWN;
}

std::string CellTrait::stringFromEnum(Enum value)
{
	switch(value)
	{
	case FREE_LOW_COST:
		return "FREE_LOW_COST";
		break;
	case FREE_HIGH_COST:
		return "FREE_HIGH_COST";
		break;
	case OBSTACLE:
		return "OBSTACLE";
		break;
	case GOAL:
		return "GOAL";
		break;
	case TRAVERSED:
		return "TRAVERSED";
		break;
	default:
		return  "UNKOWN";
		break;
	}
	return "UNKOWN";
}

//***************************** OCCUPANCYGRID **************************************//
MultiTraitOccupancyGrid::MultiTraitOccupancyGrid():temp_cell_values_(NULL),has_goal_(false){};

MultiTraitOccupancyGrid::MultiTraitOccupancyGrid(const MultiTraitOccupancyGrid& copy):
		grid_(copy.grid_),
		map_meta_data_(copy.map_meta_data_),
		trait_map_(copy.trait_map_),
		index_map_(copy.index_map_),
		frame_id_(copy.frame_id_),
		temp_cell_values_(new cell_data_t[copy.trait_map_.size()]),
		goal_pose_(copy.goal_pose_),
		has_goal_(copy.has_goal_)
{

}

MultiTraitOccupancyGrid::MultiTraitOccupancyGrid(const MultiTraitOccupancyGridMessage& message):
						map_meta_data_(message.trait_grids.at(0).info),
						frame_id_(message.header.frame_id),
						temp_cell_values_(new cell_data_t[message.trait_vector.size()])
{
	this->grid_ = message.trait_grids;
	this->goal_pose_ = message.goal;
	this->has_goal_  = message.has_goal;
	for(unsigned int i=0; i<message.trait_vector.size(); i++)
	{
		CellTrait trait(message.trait_vector.at(i));
		//ROS_INFO_STREAM("Loading Trait "<<trait.getString()<<" to vector index "<<i+1);
		this->trait_map_[trait.getEnum()] = i+1;
		this->index_map_[i+1] = trait.getEnum();
	}
}


MultiTraitOccupancyGrid::MultiTraitOccupancyGrid(const std::string& frame_id, const std::vector<trait_t>& traits, trait_t initial_trait, const nav_msgs::MapMetaData& slice_info):
						map_meta_data_(slice_info),
						frame_id_(frame_id),
						temp_cell_values_(new cell_data_t[traits.size()])
{
	this->goal_pose_.orientation.w = 1;
	this->has_goal_ = false;
	//Initialize the trait vector
	this->grid_ = grid_slice_t(traits.size()+1);
	BOOST_FOREACH(grid_slice_t::value_type& grid_trait, this->grid_)
	{
		grid_trait.info = this->map_meta_data_;
		buildEmptyOccupancyGrid(grid_trait);
	}

	//Build mapping between a grid in the trait vector and a trait type and vice-versa
	for(unsigned int i=1; i<traits.size()+1; i++)
	{
		this->trait_map_[traits.at(i-1).getEnum()] = i;
		this->index_map_[i] = traits.at(i-1).getEnum();
	}

	//Fill in the initial confidance type
	for(unsigned int x=0; x<this->map_meta_data_.width; x++)
	{
		for(unsigned int y=0; y<this->map_meta_data_.height; y++)
		{
			int cell_index = ogu::calcIndexRowMajor2D(x, y, this->map_meta_data_.width);
			this->grid_.at(this->trait_map_[initial_trait.getEnum()]).data[cell_index] = 100;
			this->grid_.at(0).data.at(cell_index) = initial_trait.getEnum();
		}
	}
}

MultiTraitOccupancyGrid::~MultiTraitOccupancyGrid()
{
	delete[] this->temp_cell_values_;
}


int MultiTraitOccupancyGrid::getXSizeGrid() const
{
	return this->map_meta_data_.width;
}

double MultiTraitOccupancyGrid::getXSizeMeter() const
{
	return this->map_meta_data_.width*this->map_meta_data_.resolution;
}

int MultiTraitOccupancyGrid::getYSizeGrid() const
{
	return this->map_meta_data_.height;
}

double MultiTraitOccupancyGrid::getYSizeMeter() const
{
	return this->map_meta_data_.height*this->map_meta_data_.resolution;
}

double MultiTraitOccupancyGrid::getResolution() const
{
	return this->map_meta_data_.resolution;
}

geometry_msgs::Pose MultiTraitOccupancyGrid::getOrigin() const
{
	return this->map_meta_data_.origin;
}

std::string MultiTraitOccupancyGrid::getFrameID() const
{
	return this->frame_id_;
}

MultiTraitOccupancyGrid::trait_t MultiTraitOccupancyGrid::getPointTrait(unsigned int x, unsigned int y) const  throw (bool)
{
	if(this->boundsCheck(x, y))
	{
		int index = ogu::calcIndexRowMajor2D(x, y, this->map_meta_data_.width);
		return this->grid_.at(0).data[index];
	}
	else throw false;
}

MultiTraitOccupancyGrid::trait_t MultiTraitOccupancyGrid::getPointTrait(double x, double y, bool origin_corrected) const  throw (bool)
{
	ROS_INFO_STREAM("I Got Called With Double Values!");
	if(!origin_corrected)
	{
		x += this->map_meta_data_.origin.position.x;
		y += this->map_meta_data_.origin.position.y;
	}
	return this->getPointTrait((unsigned int)(x/this->map_meta_data_.resolution), (unsigned int)(y/this->map_meta_data_.resolution));
}

MultiTraitOccupancyGrid::trait_t MultiTraitOccupancyGrid::getPointTrait(const gm::PoseStamped& point) const  throw (bool)
{
	return this->getPointTrait((double)(point.pose.position.x+this->map_meta_data_.origin.position.x), (double)(point.pose.position.y+this->map_meta_data_.origin.position.y));
}

void MultiTraitOccupancyGrid::addPointTrait(const gm::PoseStamped& point, trait_t trait, int confidence)  throw (bool)
{
	this->addPointTrait((double)(point.pose.position.x+this->map_meta_data_.origin.position.x), (double)(point.pose.position.y+this->map_meta_data_.origin.position.y), trait, confidence);
}

void MultiTraitOccupancyGrid::addPointTrait(double x, double y, trait_t trait, int confidence, bool origin_corrected)  throw (bool)
{
	if(!origin_corrected)
	{
		x += this->map_meta_data_.origin.position.x;
		y += this->map_meta_data_.origin.position.y;
	}
	this->addPointTrait((unsigned int)(x/this->map_meta_data_.resolution), (unsigned int)(y/this->map_meta_data_.resolution), trait, confidence);
}

void MultiTraitOccupancyGrid::addPointTrait(unsigned int x, unsigned int y, trait_t trait, int confidence)  throw (bool)
{
	if(this->boundsCheck(x, y))
	{
		int cell_index = ogu::calcIndexRowMajor2D(x, y, this->map_meta_data_.width);
		//Fill the temp values
		BOOST_FOREACH(trait_map_t::value_type trait, this->trait_map_)
		{
			this->temp_cell_values_[trait.second-1] = this->grid_.at(trait.second).data[cell_index];
		}
		//Increase the confidence of the requested trait
		this->temp_cell_values_[this->trait_map_[trait.getEnum()]-1] += confidence;

		//Normalize the confidence values
		normalizeConfidance(this->temp_cell_values_, this->grid_.size()-1, this->temp_cell_values_);

		//Write back the values to the grid, update the current 'best' choice
		int best_trait_index = -1;
		cell_data_t best_trait_value = 0;
		for(unsigned int i=0; i<this->grid_.size()-1; i++)
		{
			if(this->temp_cell_values_[i]>best_trait_value)
			{
				best_trait_index = i;
				best_trait_value = this->temp_cell_values_[i];
			}
			this->grid_.at(i+1).data[cell_index] = this->temp_cell_values_[i];
		}
		this->grid_.at(0).data[cell_index] = this->index_map_[best_trait_index+1];
	}
	else throw false;
}

void MultiTraitOccupancyGrid::toROSMsg(MultiTraitOccupancyGridMessage& message) const
{
	message.trait_grids     = this->grid_;
	message.header.frame_id = this->frame_id_;
	message.header.stamp    = ros::Time::now();
	message.trait_vector    = std::vector<int32_t>(this->trait_map_.size());
	BOOST_FOREACH(trait_map_t::value_type trait_index, this->trait_map_)
	{
		CellTrait trait(trait_index.first);
		//ROS_INFO_STREAM("Copying Trait "<<trait.getString()<<" to vector index "<<trait_index.second-1);
		message.trait_vector.at(trait_index.second-1) = trait_index.first;
	}
}

void MultiTraitOccupancyGrid::toROSMsg(trait_t trait, nm::OccupancyGrid& message) const
{
	message.header.frame_id = this->frame_id_;
	message.header.stamp    = ros::Time::now();
	message.info            = this->map_meta_data_;
	message.data            = this->grid_.at(this->trait_map_.at(trait.getEnum())).data;
}

void MultiTraitOccupancyGrid::addPointTrait(const nm::OccupancyGrid& confidances, trait_t trait, bool scaling, bool use_zero_as_free, bool use_negative_as_unkown)  throw (bool)
{
	unsigned int copy_width  = confidances.info.width;
	unsigned int copy_height = confidances.info.height;
	if(copy_width > this->map_meta_data_.width)
	{
		copy_width = this->map_meta_data_.width;
	}
	if(copy_height > this->map_meta_data_.height)
	{
		copy_height = this->map_meta_data_.height;
	}
	for(unsigned int x = 0; x < copy_width; x++)
	{
		for(unsigned int y = 0; y < copy_height; y++)
		{
			int copy_confidence        = confidances.data[ogu::calcIndexRowMajor2D(x, y, confidances.info.width)];
			CellTrait copy_trait(trait);
			if(use_zero_as_free)
			{
				if(copy_confidence == 0)
				{
					copy_trait      = CellTrait::FREE_LOW_COST;
					copy_confidence = 100;
				}
			}
			if(use_negative_as_unkown)
			{
				if(copy_confidence<0)
				{
					copy_trait      = CellTrait::UNKOWN;
					copy_confidence = 10;
				}
			}
			this->addPointTrait((double)x*confidances.info.resolution, (double)y*confidances.info.resolution, copy_trait, copy_confidence);
		}
	}
}

bool MultiTraitOccupancyGrid::getGoal(gm::Pose& goal) const
{
	goal = this->goal_pose_;
	return this->has_goal_;
}

void MultiTraitOccupancyGrid::setGoal(unsigned int x, unsigned int y)
{
	this->has_goal_ = true;
	this->goal_pose_.position.x = (double)x*this->map_meta_data_.resolution;
	this->goal_pose_.position.y = (double)y*this->map_meta_data_.resolution;
	this->place_goal(x, y);
}

void MultiTraitOccupancyGrid::setGoal(double x, double y, bool origin_corrected)
{
	if(!origin_corrected)
	{
		x += this->map_meta_data_.origin.position.x;
		y += this->map_meta_data_.origin.position.y;
	}
	this->has_goal_ = true;
	this->goal_pose_.position.x = x;
	this->goal_pose_.position.y = y;
	this->place_goal(x/this->map_meta_data_.resolution, x/this->map_meta_data_.resolution);
}

void MultiTraitOccupancyGrid::setGoal(const gm::Pose& goal)
{
	gm::Pose corrected_goal(goal);
	corrected_goal.position.x += this->map_meta_data_.origin.position.x;
	corrected_goal.position.y += this->map_meta_data_.origin.position.y;
	corrected_goal.position.z = 0;
	this->has_goal_  = true;
	this->goal_pose_ = corrected_goal;
	this->place_goal(corrected_goal.position.x/this->map_meta_data_.resolution, corrected_goal.position.y/this->map_meta_data_.resolution);
}

void MultiTraitOccupancyGrid::place_goal(unsigned int x, unsigned int y)
{
	if(x<(int)this->map_meta_data_.width&&y<(int)this->map_meta_data_.height)
	{
		this->addPointTrait(x, y, CellTrait::GOAL, 1000);
	}
}

ros::Time MultiTraitOccupancyGrid::getCreationTime() const
{
	return this->map_meta_data_.map_load_time;
}

bool MultiTraitOccupancyGrid::generateOccupancyGridforTrait(nm::OccupancyGrid& message, ogu::CellTrait trait) const
{
	if(this->trait_map_.count(trait.getEnum())==1)
	{
		message =  this->grid_.at(this->trait_map_.at(trait.getEnum()));
		return true;
	}
	return false;
}

bool MultiTraitOccupancyGrid::boundsCheck(unsigned int x, unsigned int y) const
{
	bool xbound = x<this->map_meta_data_.width;
	bool ybound = y<this->map_meta_data_.height;
	return xbound&&ybound;
}
