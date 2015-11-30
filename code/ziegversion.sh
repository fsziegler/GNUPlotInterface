#!/bin/sh
# The MIT License (MIT)
# 
# Copyright (c) 2014 Frederick S. Ziegler
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#        File: ziegversion.sh
#  Created on: Jun 26, 2014
#      Author: Fred Ziegler

sed -i -r 's/(const long int BuildNumber = )([0-9]+)/echo \1$((\2+1))/ge' ../../../code/ZiegVersion.h
sed -i -r "s/(const long int BuildNumber = )([0-9]+)/   const long int BuildNumber = \2;/g" ../../../code/ZiegVersion.h
sed -i -r "s/const long int UTCSeconds = [0-9]+;/const long int UTCSeconds = $(date +%s);/g" ../../../code/ZiegVersion.h
sed -i -r "s/const string BuildDate = \"[0-9\-]+\";/const string BuildDate = \"$(date +%F)\";/g" ../../../code/ZiegVersion.h
sed -i -r "s/const string BuildTime = \"[0-9\:]+\";/const string BuildTime = \"$(date +%T)\";/g" ../../../code/ZiegVersion.h
sed -i -r "s/const string UUID = \"[0-9a-z\-]+\";/const string UUID = \"$(uuid)\";/g" ../../../code/ZiegVersion.h
# cat ../../../code/ZiegVersion.h
pwd
