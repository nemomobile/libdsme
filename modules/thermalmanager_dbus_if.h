/**
   @file thermalmanager_dbus_if.h

   D-Bus names for Thermal Manager
   <p>
   Copyright (C) 2010 Nokia Corporation.

   @author Semi Malinen <semi.malinen@nokia.com>

   This file is part of Dsme.

   Dsme is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 2.1 as published by the Free Software Foundation.

   Dsme is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with Dsme.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef THERMALMANAGER_DBUS_IF_H
#define THERMALMANAGER_DBUS_IF_H

extern const char thermalmanager_service[];
extern const char thermalmanager_interface[];
extern const char thermalmanager_path[];

extern const char thermalmanager_state_change_ind[];
extern const char thermalmanager_get_thermal_state[];

#endif
