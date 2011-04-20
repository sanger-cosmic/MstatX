/* Copyright (c) 2010 Guillaume Collet
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE. 
 */

#include "gap.h"
#include "options.h"

#include <fstream>

void
GapStat :: calculateStatistic(Msa & msa)
{
	int L = msa.getNcol();
	int N = msa.getNseq();
	for (int x(0); x < L; ++x){
		col_cons.push_back((float) msa.getGap(x) / (float) N);
	}
}


/** printStatistic(Msa & msa)
 *
 * Print Conservation score in output file 
 */
void 
GapStat :: printStatistic(Msa & msa){
	ofstream file(Options::Get().output_name.c_str());
	if (!file.is_open()){
	  cerr << "Cannot open file " << Options::Get().output_name << "\n";
		exit(0);
	}
	if (Options::Get().global){
		float total = 0.0;
		for (int col(0); col < col_cons.size(); ++col){
			total += col_cons[col];
		}
		file << total / col_cons.size() << "\n"; 
	} else {
		for (int col(0); col < col_cons.size(); ++col){
			file << col_cons[col] << "\n";
		}
	}
	file.close();
};
