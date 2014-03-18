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
//  created:	2011-12-7 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#ifndef __PACKET_FACTORY_H__
#define __PACKET_FACTORY_H__

#include "Types.h"
#include "Factory.h"
#include "TManager.h"
#include "Singleton.h"
#include "Thread/Mutex.h"

namespace okey
{
	class PacketBase;

	class PacketFactory: public TManager<CFactoryArg0_Base>, public Singleton<PacketFactory, Mutex>
	{
	public:
		PacketFactory(){}
		~PacketFactory(){}
		void* CreatePacket(const char* name);
		void* CreatePacket(uint32 packetid);
		bool DestroyPacket(PacketBase* pkt);
	protected:
	private:
		
		PacketFactory(const PacketFactory&);
		PacketFactory& operator=(const PacketFactory&);
	};

	#define s_PacketFactory PacketFactory::GetSingleton()
}

#endif