# qtnp
Qt+CGAL+ROS area partition and path planning for multiple UAVs for coastal regions.

***

# Multiple UAV waypoint path planning application.

Made with Qt5.5, for ROS Kinetic, using CGAL 4.8.

A kml file defines area borders and no-fly zones. 

Multiple UAVs can be assigned anywhere in that area, having different Field of View (FoV) footprint projections on the sea. Area decomposition and partition is performed based on those restrictions and coverage waypoint lists are produced in MAVlink format.


***
Copyright (C) 2017 Fotios Balampanis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
