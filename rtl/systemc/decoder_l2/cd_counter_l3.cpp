// cd_counter_l3.cpp

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is HyperTransport Tunnel IP Core.
 *
 * The Initial Developer of the Original Code is
 * Ecole Polytechnique de Montreal.
 * Portions created by the Initial Developer are Copyright (C) 2005
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Max-Elie Salomon
 *   Ami Castonguay <acastong@grm.polymtl.ca>
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the Polytechnique HyperTransport Tunnel IP Core Source Code License 
 * (the  "PHTICSCL License", see the file PHTICSCL.txt), in which case the
 * provisions of PHTICSCL License are applicable instead of those
 * above. If you wish to allow use of your version of this file only
 * under the terms of the PHTICSCL License and not to allow others to use
 * your version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the PHTICSCL License. If you do not delete
 * the provisions above, a recipient may use your version of this file
 * under either the MPL or the PHTICSCL License."
 *
 * ***** END LICENSE BLOCK ***** */


#include "cd_counter_l3.h"

cd_counter_l3::cd_counter_l3(sc_module_name name) : sc_module(name)
{
	SC_METHOD(count_process);
	sensitive_neg << resetx;
	sensitive_pos<<clk;
}

	
void cd_counter_l3::count_process()
{
	sc_bv<4> count;
	count = data.read().range(25,22);

	//At reset, count goes back to 0 and default outputs
	if (!resetx.read()){
		countVal = 0;
		//count_done = true;
		end_of_count = true;
	}
	else{
		//If we are setting a new count
		if(setCnt.read()){	
			countVal = sc_uint<4>(count);
			//count_done = false;
			//If the count is 0, then there is only one data dword, so
			//the next one is the last.
			if(sc_uint<4>(count) == 0){;
				end_of_count = true;
			}
			else{
				end_of_count = false;
			}
		}
		//If we decrement, but it is not the last data
		else if (decrCnt.read() && countVal.read() !=0){
			countVal = countVal.read() - 1;
			//count_done = false;
			if(countVal.read() == 1){
				end_of_count = true;
			}
			else{
				end_of_count = false;
			}
		}
		//If we decrement, and that we reached the end of the count, output
		//that the count is done
		else if (decrCnt.read()){
			countVal = countVal.read();
			end_of_count = true;
			//count_done = true;
		}
	}			
}
