// PacketPool.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "PacketPool.h"
#include "lib\Library.h"

int main()
{
	int Cnt;
	Packet::Initialize ();

	Packet *p[1000];
	while ( 1 )
	{
		for ( Cnt = 0; Cnt < 1000; Cnt++ )
		{
			p[Cnt] = Packet::Alloc ();
		}

		for ( Cnt = 0; Cnt < 1000; Cnt++ )
		{
			*p[Cnt] << 100;
		}


		printf ("\nFull : %d \n", Packet::PacketPool->GetFullCount ());
		printf ("Use : %d \n", Packet::PacketPool->GetAllocCount ());
		printf ("Free : %d \n", Packet::PacketPool->GetFreeCount ());

		int ref;
		for ( Cnt = 0; Cnt < 1000; Cnt++ )
		{
			*p[Cnt] >> ref;
			if ( ref != 100 )
			{
				CCrashDump::Crash ();
			}
		}

		for ( Cnt = 0; Cnt < 1000; Cnt++ )
		{
			if ( !Packet::Free (p[Cnt]) )
			{
				CCrashDump::Crash ();
			}
		}

		printf ("Full : %d \n", Packet::PacketPool->GetFullCount ());
		printf ("Use : %d \n", Packet::PacketPool->GetAllocCount ());
		printf ("Free : %d \n\n", Packet::PacketPool->GetFreeCount ());

		Sleep (999);
	}




    return 0;
}

