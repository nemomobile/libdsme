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

// Signals
extern const char thermalmanager_state_change_ind[];

// Methods
extern const char thermalmanager_get_thermal_state[];
extern const char thermalmanager_estimate_surface_temperature[];
extern const char thermalmanager_core_temperature[];
extern const char thermalmanager_battery_temperature[];
extern const char thermalmanager_sensor_temperature[];

// Possible values for the status
extern const char thermalmanager_thermal_status_low[];
extern const char thermalmanager_thermal_status_normal[];
extern const char thermalmanager_thermal_status_warning[];
extern const char thermalmanager_thermal_status_alert[];
extern const char thermalmanager_thermal_status_fatal[];

#endif
