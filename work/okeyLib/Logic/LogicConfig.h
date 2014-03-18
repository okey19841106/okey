//////////////////////////////////////////////////////////////
//                    .----.
//                 _.'__    `.
//             .--(#)(##)---/#\
//           .' @          /###\
//           :       ,     #####
//            `-..__.-' _.-\###/ 
//                   `;_:   `"'
//                 .'"""""`.
//                /,        ,\
//               //          \\
//               `-._______.-'
//              ___`. | .'___
//             (______|______)
//
//  created:	2011-12-16 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#ifndef __LOGIC_CONFIG_H__
#define __LOGIC_CONFIG_H__

namespace okey
{
	#define MAX_LOGIC_IN_OUT_PUT 8
	#define MAX_LOGIC_LIST 128
	#define MAX_LOGIC_GROUP_LIST 32

	enum Logic_Type
	{
		Logic_Type_Base = -1,
		Logic_Type_Int,
		Logic_Type_Float,
		Logic_Type_Char,
		Logic_Type_Ptr,
	};
}

#endif