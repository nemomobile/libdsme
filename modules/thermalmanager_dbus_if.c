/**
   @file thermalmanager_dbus_if.c

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

#include "thermalmanager_dbus_if.h"

const char thermalmanager_service[]           = "com.nokia.thermalmanager";
const char thermalmanager_interface[]         = "com.nokia.thermalmanager";
const char thermalmanager_path[]              = "/com/nokia/thermalmanager";

const char thermalmanager_state_change_ind[]  = "thermal_state_change_ind";

const char thermalmanager_get_thermal_state[]            = "get_thermal_state";
const char thermalmanager_estimate_surface_temperature[] = "estimate_surface_temperature";
const char thermalmanager_core_temperature[]             = "core_temperature";
const char thermalmanager_battery_temperature[]          = "battery_temperature";
const char thermalmanager_sensor_temperature[]           = "sensor_temperature";

const char thermalmanager_thermal_status_low[]     = "low-temp-warning";
const char thermalmanager_thermal_status_normal[]  = "normal";
const char thermalmanager_thermal_status_warning[] = "warning";
const char thermalmanager_thermal_status_alert[]   = "alert";
const char thermalmanager_thermal_status_fatal[]   = "fatal";
