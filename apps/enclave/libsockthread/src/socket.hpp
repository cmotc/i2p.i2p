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
 * $Id: socket.hpp,v 1.8 2004/07/22 22:08:20 mpc Exp $
 */

#ifndef LIBSOCKTHREAD_SOCKET_HPP
#define LIBSOCKTHREAD_SOCKET_HPP

namespace Libsockthread {
	class Socket {
		public:
			#ifdef WINSOCK
				typedef SOCKET socket_t;
				enum { SERR = SOCKET_ERROR };
			#else
				typedef int socket_t;
				enum { SERR = -1 };
			#endif

			Socket()
				: addr(), sock(SERR) {}
			Socket(Socket_addr& addr)  // throws Socket_error
				: addr(addr), sock(SERR) { setup_socket(); }

			void close();
			size_t read(vector<uchar_t>& buf, size_t max = 0);
			size_t read_until(vector<uchar_t>& buf, uchar_t delim = '\n');
			void set_addr(Socket_addr& addr);  // throws Socket_error
			void set_blocking(bool blocking);
			size_t write(vector<uchar_t>& buf);
			void write_all(vector<uchar_t>& buf);
			size_t write_until(vector<uchar_t& buf, uchar_t delim = '\n');
		private:
			void setup_socket();  // throws Socket_error

			Socket_addr addr;
			socket_t sock;
	};
}

#endif  // LIBSOCKTHREAD_SOCKET_HPP
