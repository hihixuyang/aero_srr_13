/**
 * @file   MultiTraitOccupancyGridHelpers.h
 *
 * @date   May 18, 2013
 * @author parallels
 * @brief  \TODO
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

#ifndef MULTITRAITOCCUPANCYGRIDHELPERS_H_
#define MULTITRAITOCCUPANCYGRIDHELPERS_H_

//*********** SYSTEM DEPENDANCIES ****************//
#include <occupancy_grid/MultiTraitOccupancyGrid.hpp>
#include <aero_path_planning/utilities/AeroPathPlanning.h>
#include <tf/transform_listener.h>
//************ LOCAL DEPENDANCIES ****************//

//***********    NAMESPACES     ****************//

namespace aero_path_planning
{
bool addPointCloudPatch(aero_path_planning::PointCloud& cloud, occupancy_grid::utilities::CellTrait trait, int confidence, occupancy_grid::MultiTraitOccupancyGrid& grid, tf::TransformListener& transformer_, std::string& error_message);

}

#endif /* MULTITRAITOCCUPANCYGRIDHELPERS_H_ */
