// cd_counter_l3.h

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

#ifndef CD_COUNTER_L3_H
#define CD_COUNTER_L3_H

#include "../core_synth/synth_datatypes.h"
#include "../core_synth/constants.h"

///Counter for the decoder module
/**
	@class cd_counter_l3
	@description Counts the number of data doublewords that
	have been received and generates a flag to
	indicate the end of reception
	
	@author Max-Elie Salomon
			Ami Castonguay
*/
class cd_counter_l3 : public sc_module
{	
	///The actual count value
	sc_signal<sc_uint<4> > countVal;

public:

	//*******************************
	//	Inputs
	//*******************************

	///Clock to synchronize module
	sc_in< bool > clk;
	///Reset signal (active low)
	sc_in< bool > resetx;
	///Sets the number of doublewords to be received
	sc_in< bool > setCnt;
	///Decreases the number of doublewords to be received upon reception of a data doubleword
	sc_in< bool > decrCnt;
	///Input bit vector
	sc_in<sc_bv<32> > data;

	//*******************************
	//	Outputs
	//*******************************

	///Flag indicating the next valid data dword will be the last
	sc_out< bool > end_of_count;
	///Flag indicating the last data dword has been received
	//sc_out< bool > count_done;


	/**
		Process of counting the reception of data packets,
		sensitive to rising edge of clock
	*/
	void count_process();

	///SystemC Macro
	SC_HAS_PROCESS(cd_counter_l3);

	///Module constructor
	cd_counter_l3(sc_module_name name);
};

#endif
