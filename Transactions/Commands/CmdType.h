//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_CMDTYPE_H
#define REPCREC_CMDTYPE_H

/**
 * Types of commands
 */
enum CmdType {
	Read, Write, Begin, End, Fail, Recover, BeginRO, None
};


#endif //REPCREC_CMDTYPE_H
