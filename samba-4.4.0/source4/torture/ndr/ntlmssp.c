/*
   Unix SMB/CIFS implementation.
   test suite for ntlmssp ndr operations

   Copyright (C) Guenther Deschner 2010

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "includes.h"
#include "torture/ndr/ndr.h"
#include "librpc/gen_ndr/ndr_ntlmssp.h"
#include "torture/ndr/proto.h"

static const uint8_t ntlmssp_NEGOTIATE_MESSAGE_data[] = {
	0x4e, 0x54, 0x4c, 0x4d, 0x53, 0x53, 0x50, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x97, 0x82, 0x08, 0xe2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x01, 0xb0, 0x1d,
	0x00, 0x00, 0x00, 0x0f
};

static bool ntlmssp_NEGOTIATE_MESSAGE_check(struct torture_context *tctx,
					    struct NEGOTIATE_MESSAGE *r)
{
	return true;
}

#if 0
static const uint8_t ntlmssp_CHALLENGE_MESSAGE_data[] = {
	0x4e, 0x54, 0x4c, 0x4d, 0x53, 0x53, 0x50, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x0a, 0x00, 0x0a, 0x00, 0x38, 0x00, 0x00, 0x00, 0x95, 0x82, 0x89, 0xe2,
	0xed, 0xc8, 0x2b, 0x7d, 0x2e, 0xd7, 0xd0, 0xd9, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x78, 0x00, 0x42, 0x00, 0x00, 0x00,
	0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x53, 0x00, 0x41, 0x00,
	0x4d, 0x00, 0x42, 0x00, 0x41, 0x00, 0x02, 0x00, 0x0a, 0x00, 0x53, 0x00,
	0x41, 0x00, 0x4d, 0x00, 0x42, 0x00, 0x41, 0x00, 0x01, 0x00, 0x10, 0x00,
	0x4d, 0x00, 0x54, 0x00, 0x48, 0x00, 0x45, 0x00, 0x4c, 0x00, 0x45, 0x00,
	0x4e, 0x00, 0x41, 0x00, 0x04, 0x00, 0x1c, 0x00, 0x62, 0x00, 0x65, 0x00,
	0x72, 0x00, 0x2e, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00, 0x68, 0x00,
	0x61, 0x00, 0x74, 0x00, 0x2e, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6d, 0x00,
	0x03, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x74, 0x00, 0x68, 0x00, 0x65, 0x00,
	0x6c, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x2e, 0x00, 0x62, 0x00,
	0x65, 0x00, 0x72, 0x00, 0x2e, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00,
	0x68, 0x00, 0x61, 0x00, 0x74, 0x00, 0x2e, 0x00, 0x63, 0x00, 0x6f, 0x00,
	0x6d, 0x00, 0x00, 0x00, 0x00, 0x00
};

static bool ntlmssp_CHALLENGE_MESSAGE_check(struct torture_context *tctx,
					    struct CHALLENGE_MESSAGE *r)
{
	return true;
}

static const uint8_t ntlmssp_AUTHENTICATE_MESSAGE_data[] = {
	0x4e, 0x54, 0x4c, 0x4d, 0x53, 0x53, 0x50, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x18, 0x00, 0x18, 0x00, 0x8c, 0x00, 0x00, 0x00, 0x0e, 0x01, 0x0e, 0x01,
	0xa4, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x58, 0x00, 0x00, 0x00,
	0x1a, 0x00, 0x1a, 0x00, 0x66, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x0c, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0xb2, 0x01, 0x00, 0x00,
	0x15, 0x82, 0x88, 0xe2, 0x06, 0x01, 0xb0, 0x1d, 0x00, 0x00, 0x00, 0x0f,
	0x50, 0xe2, 0xb2, 0xa7, 0xf5, 0x83, 0x3e, 0xda, 0x71, 0xa7, 0xe8, 0x6e,
	0x95, 0x1e, 0x3a, 0x57, 0x57, 0x00, 0x32, 0x00, 0x4b, 0x00, 0x38, 0x00,
	0x44, 0x00, 0x4f, 0x00, 0x4d, 0x00, 0x41, 0x00, 0x64, 0x00, 0x6d, 0x00,
	0x69, 0x00, 0x6e, 0x00, 0x69, 0x00, 0x73, 0x00, 0x74, 0x00, 0x72, 0x00,
	0x61, 0x00, 0x74, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x57, 0x00, 0x32, 0x00,
	0x4b, 0x00, 0x38, 0x00, 0x52, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xcf, 0xfb, 0x39,
	0x5a, 0xb3, 0x4c, 0x58, 0x86, 0x35, 0xa3, 0xe7, 0x1e, 0x00, 0x98, 0x43,
	0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x96, 0x79, 0x02, 0x77,
	0x1e, 0x54, 0xcb, 0x01, 0x3c, 0x21, 0x0a, 0xe9, 0xde, 0x61, 0xc0, 0x7e,
	0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0a, 0x00, 0x53, 0x00, 0x41, 0x00,
	0x4d, 0x00, 0x42, 0x00, 0x41, 0x00, 0x01, 0x00, 0x10, 0x00, 0x4d, 0x00,
	0x54, 0x00, 0x48, 0x00, 0x45, 0x00, 0x4c, 0x00, 0x45, 0x00, 0x4e, 0x00,
	0x41, 0x00, 0x04, 0x00, 0x1c, 0x00, 0x62, 0x00, 0x65, 0x00, 0x72, 0x00,
	0x2e, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00, 0x68, 0x00, 0x61, 0x00,
	0x74, 0x00, 0x2e, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x03, 0x00,
	0x2e, 0x00, 0x6d, 0x00, 0x74, 0x00, 0x68, 0x00, 0x65, 0x00, 0x6c, 0x00,
	0x65, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x2e, 0x00, 0x62, 0x00, 0x65, 0x00,
	0x72, 0x00, 0x2e, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00, 0x68, 0x00,
	0x61, 0x00, 0x74, 0x00, 0x2e, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6d, 0x00,
	0x08, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x0a, 0xfd, 0x3b, 0x2c,
	0xad, 0x43, 0x46, 0x8b, 0x49, 0x01, 0x6c, 0xa5, 0xf3, 0xbc, 0xd2, 0x13,
	0xbb, 0x70, 0xe2, 0x65, 0x96, 0xba, 0x0d, 0x8d, 0x5d, 0x31, 0xe6, 0x47,
	0x94, 0x61, 0xed, 0x28, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x09, 0x00, 0x1a, 0x00, 0x63, 0x00, 0x69, 0x00, 0x66, 0x00, 0x73, 0x00,
	0x2f, 0x00, 0x6d, 0x00, 0x74, 0x00, 0x68, 0x00, 0x65, 0x00, 0x6c, 0x00,
	0x65, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xa4, 0x23, 0xd4, 0x5c, 0x16, 0x52, 0x8d, 0x56, 0x34, 0x2d,
	0x1c, 0xff, 0x86, 0x17, 0xc9, 0x4f
};

static bool ntlmssp_AUTHENTICATE_MESSAGE_check(struct torture_context *tctx,
					       struct AUTHENTICATE_MESSAGE *r)
{
	return true;
}
#endif

struct torture_suite *ndr_ntlmssp_suite(TALLOC_CTX *ctx)
{
	struct torture_suite *suite = torture_suite_create(ctx, "ntlmssp");

	torture_suite_add_ndr_pull_test(suite, NEGOTIATE_MESSAGE, ntlmssp_NEGOTIATE_MESSAGE_data, ntlmssp_NEGOTIATE_MESSAGE_check);
#if 0
	torture_suite_add_ndr_pull_test(suite, CHALLENGE_MESSAGE, ntlmssp_CHALLENGE_MESSAGE_data, ntlmssp_CHALLENGE_MESSAGE_check);
	torture_suite_add_ndr_pull_test(suite, AUTHENTICATE_MESSAGE, ntlmssp_AUTHENTICATE_MESSAGE_data, ntlmssp_AUTHENTICATE_MESSAGE_check);
#endif
	return suite;
}
