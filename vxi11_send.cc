/* vxi11_send.c
 * Copyright (C) 2006 Steve D. Sharples
 *
 * A simple interactive utility that allows you to send a single command to
 * a device enabled with the VXI11 RPC ethernet protocol. Uses the files
 * generated by rpcgen vxi11.x, and the vxi11_user.h user libraries.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 * The author's email address is steve.sharples@nottingham.ac.uk
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vxi11_user.h"

#ifdef WIN32
#define strncasecmp(a, b, c) stricmp(a, b)
#endif

int main(int argc, char *argv[])
{

	static char *device_ip;
	char cmd[256];
	VXI11_CLINK *clink;

	if (argc < 2) {
		printf("usage: %s your.inst.ip.addr command\n", argv[0]);
		exit(1);
	}

	device_ip = argv[1];
	clink = vxi11_open_device(device_ip);

	if (!clink) {
		printf("Error: could not open device %s, quitting\n",
		       device_ip);
		exit(2);
	}

	memset(cmd, 0, 256);	// initialize command string
	strncpy(cmd, argv[2], 256);
	vxi11_send(clink, cmd);
	vxi11_close_device(device_ip, clink);
	return 0;
}
