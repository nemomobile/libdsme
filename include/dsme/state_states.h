/**
   @file state_states.h

   DSME state definitions
   <p>
   Copyright (C) 2009 Nokia Corporation.

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
DSME_STATE(NOT_SET, -1)
DSME_STATE(SHUTDOWN, 0) /* runlevel 0 or reboot(POWEROFF) */
DSME_STATE(USER,     2) /* runlevel 2 */
DSME_STATE(ACTDEAD,  5) /* runlevel 5 */
DSME_STATE(REBOOT,   6) /* runlevel 6 or reboot(REBOOT) */
DSME_STATE(TEST,     7) /* runlevel 3: test server is started */
DSME_STATE(MALF,     8) /* state if something goes wrong */
DSME_STATE(BOOT,     9) // TODO: remove
DSME_STATE(LOCAL,   10) // TODO: remove
