/*
 * Copyright (c) 2004, Matthew P. Cashdollar <mpc@innographx.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of any contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: socket.cpp,v 1.8 2004/07/22 22:08:20 mpc Exp $
 */

#include "platform.hpp"
#include "socket_error.hpp"
#include "socket.hpp"
using namespace Libsockthread;

/*
 * Closes the socket
 */
void Socket::close()
{
	if (sock != SERR) {
		if (close(sock) == -1)
			;  // FIXME log the error
	}
	sock = SERR;
}

/*
 * Changes the address associated with the socket
 */
void Socket::set_addr(Socket_addr& addr)
{
	close();
	this->addr = addr;
	setup_socket();
}

/*
 * Prepares the socket for use
 */
void Socket::setup_socket()
{
	assert(sock == SERR);  // the descriptor shouldn't be active
	if (!addr.is_ready())
		throw Socket_error("Couldn't create socket: address isn't ready");

	sock = socket(addr.get_family(), addr.get_type(), 0);
	if (sock == SERR)
		throw Socket_error(strerror(errno));
}
