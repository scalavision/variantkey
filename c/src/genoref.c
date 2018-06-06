// Copyright (c) 2017-2018 GENOMICS plc
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <string.h>
#include "genoref.h"

inline void load_genoref_index(const unsigned char *src, uint32_t idx[])
{
    idx[0] = 0;
    int i;
    for (i = 1; i <= 26; i++)
    {
        idx[i] = bytes_to_uint32_t(src, ((i - 1) * 4));
    }
}

inline char get_genoref_seq(const unsigned char *src, uint32_t idx[], uint8_t chrom, uint32_t pos)
{
    uint32_t offset = (idx[chrom] + pos);
    if (offset > (idx[(chrom + 1)] - 2))
    {
        return 0; // invalid position
    }
    return (char)src[offset];
}
