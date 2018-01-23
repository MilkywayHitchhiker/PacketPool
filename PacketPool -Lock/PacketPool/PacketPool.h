
#pragma once
#include <Windows.h>
#include "MemoryPool.h"

class Packet
{
public:
	enum PACKET
	{
		BUFFER_DEFAULT			= 10000,	// 패킷의 기본 버퍼 사이즈.
		Header_MAX_DEFAULT		= 5			// 헤더의 최대 사이즈.
	};

	// 생성자, 파괴자.
			Packet();
			Packet(int iBufferSize);
			Packet(const Packet &SrcPacket);

	virtual	~Packet();

	// 패킷 초기화.
	void	Initial(int iBufferSize = BUFFER_DEFAULT);

	//RefCnt를 1 증가시킴. 
	void	Add (void);

	// 자기자신을 delete하고 빠져나옴.
	void	Release(void);


	// 패킷 비우기.
	void	Clear(void);


	// 버퍼 사이즈 얻기.
	int		GetBufferSize (void)
	{
		return _iBufferSize;
	}

	// 현재 사용중인 데이터 사이즈 얻기.
	int		GetDataSize (void)
	{
		return _iDataSize;
	}

	//현재 사용중인 헤더 사이즈 얻기.
	int		GetHeaderSize (void)
	{
		return _iHeaderSize;
	}

	// 현재 사용중인 사이즈 얻기.
	int		GetUseSize (void)
	{
		return _iDataSize + _iHeaderSize;
	}

	// 버퍼 포인터 얻기.
	char	*GetBufferPtr (void)
	{
		return DataFieldStart;
	}
	char	*GetHeaderPtr (void)
	{
		return HeaderFieldStart;
	}


	// 버퍼 Pos 이동.
	int		MoveWritePos(int iSize);
	int		MoveReadPos(int iSize);






	// 연산자 오퍼레이터.
	Packet	&operator = (Packet &SrcPacket);

	//////////////////////////////////////////////////////////////////////////
	// 넣기.	각 변수 타입마다 모두 만듬.
	//////////////////////////////////////////////////////////////////////////
	Packet	&operator << (BYTE byValue);
	Packet	&operator << (char chValue);

	Packet	&operator << (short shValue);
	Packet	&operator << (WORD wValue);

	Packet	&operator << (int iValue);
	Packet	&operator << (DWORD dwValue);
	Packet	&operator << (float fValue);

	Packet	&operator << (__int64 iValue);
	Packet	&operator << (double dValue);

	//////////////////////////////////////////////////////////////////////////
	// 빼기.	각 변수 타입마다 모두 만듬.
	//////////////////////////////////////////////////////////////////////////
	Packet	&operator >> (BYTE &byValue);
	Packet	&operator >> (char &chValue);

	Packet	&operator >> (short &shValue);
	Packet	&operator >> (WORD &wValue);

	Packet	&operator >> (int &iValue);
	Packet	&operator >> (DWORD &dwValue);
	Packet	&operator >> (float &fValue);

	Packet	&operator >> (__int64 &iValue);
	Packet	&operator >> (double &dValue);




	// 데이타 얻기.
	// Return 복사한 사이즈.
	int		GetData(char *chpDest, int iSize);

	// 데이타 삽입.
	// Return 복사한 사이즈.
	int		PutData(char *chpSrc, int iSrcSize);

	// 헤더 삽입.
	// Return 복사한 사이즈
	int		PutHeader (char *chpSrc, int iSrcSize);

	// short 헤더 삽입.
	// Return 복사한 사이즈
	int		PutHeader (short chpSrc);

protected:
	//------------------------------------------------------------
	// 패킷버퍼 / 버퍼 사이즈.
	//------------------------------------------------------------
	char	BufferDefault[BUFFER_DEFAULT];
	char	*BufferExpansion;

	char	*Buffer;
	int		_iBufferSize;
	//------------------------------------------------------------
	// 패킷버퍼 시작 위치.
	//------------------------------------------------------------
	char	*DataFieldStart;
	char	*DataFieldEnd;
	char	*HeaderFieldStart;

	//------------------------------------------------------------
	// 버퍼의 읽을 위치, 넣을 위치.
	//------------------------------------------------------------
	char	*ReadPos;
	char	*WritePos;


	//------------------------------------------------------------
	// 현재 버퍼에 사용중인 사이즈.
	//------------------------------------------------------------
	int		_iDataSize;
	int		_iHeaderSize;

	//------------------------------------------------------------
	// 현재 Packet의 RefCnt
	//------------------------------------------------------------
	int iRefCnt;

public :
	static Hitchhiker::CMemoryPool<Packet> *PacketPool;

public :
	
	static void Initialize (void)
	{
		if ( PacketPool == NULL )
		{
			PacketPool = new Hitchhiker::CMemoryPool<Packet> (0);
		}
		return;
	}
	

	static Packet *Alloc (void)
	{
		Packet *p = PacketPool->Alloc ();
		return p;
	}
	static bool Free (Packet *p)
	{
		if ( InterlockedDecrement (( volatile long * )&p->iRefCnt) == 0 )
		{
			return PacketPool->Free (p);
		}
	}




};
