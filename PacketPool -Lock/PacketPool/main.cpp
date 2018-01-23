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

		short Header = 2;
		for ( Cnt = 0; Cnt < 1000; Cnt++ )
		{
			p[Cnt]->PutHeader (Header);
		}


		printf ("\nFull : %d \n", Packet::PacketPool->GetFullCount ());
		printf ("Use : %d \n", Packet::PacketPool->GetAllocCount ());
		printf ("Free : %d \n", Packet::PacketPool->GetFreeCount ());



		Sleep (999);
	}




    return 0;
}

