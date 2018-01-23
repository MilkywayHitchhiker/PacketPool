
#pragma once
#include <Windows.h>
#include "MemoryPool.h"

class Packet
{
public:
	enum PACKET
	{
		BUFFER_DEFAULT			= 10000,	// ��Ŷ�� �⺻ ���� ������.
		Header_MAX_DEFAULT		= 5			// ����� �ִ� ������.
	};

	// ������, �ı���.
			Packet();
			Packet(int iBufferSize);
			Packet(const Packet &SrcPacket);

	virtual	~Packet();

	// ��Ŷ �ʱ�ȭ.
	void	Initial(int iBufferSize = BUFFER_DEFAULT);

	//RefCnt�� 1 ������Ŵ. 
	void	Add (void);

	// �ڱ��ڽ��� delete�ϰ� ��������.
	void	Release(void);


	// ��Ŷ ����.
	void	Clear(void);


	// ���� ������ ���.
	int		GetBufferSize (void)
	{
		return _iBufferSize;
	}

	// ���� ������� ������ ������ ���.
	int		GetDataSize (void)
	{
		return _iDataSize;
	}

	//���� ������� ��� ������ ���.
	int		GetHeaderSize (void)
	{
		return _iHeaderSize;
	}

	// ���� ������� ������ ���.
	int		GetUseSize (void)
	{
		return _iDataSize + _iHeaderSize;
	}

	// ���� ������ ���.
	char	*GetBufferPtr (void)
	{
		return DataFieldStart;
	}
	char	*GetHeaderPtr (void)
	{
		return HeaderFieldStart;
	}


	// ���� Pos �̵�.
	int		MoveWritePos(int iSize);
	int		MoveReadPos(int iSize);






	// ������ ���۷�����.
	Packet	&operator = (Packet &SrcPacket);

	//////////////////////////////////////////////////////////////////////////
	// �ֱ�.	�� ���� Ÿ�Ը��� ��� ����.
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
	// ����.	�� ���� Ÿ�Ը��� ��� ����.
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




	// ����Ÿ ���.
	// Return ������ ������.
	int		GetData(char *chpDest, int iSize);

	// ����Ÿ ����.
	// Return ������ ������.
	int		PutData(char *chpSrc, int iSrcSize);

	// ��� ����.
	// Return ������ ������
	int		PutHeader (char *chpSrc, int iSrcSize);

	// short ��� ����.
	// Return ������ ������
	int		PutHeader (short chpSrc);

protected:
	//------------------------------------------------------------
	// ��Ŷ���� / ���� ������.
	//------------------------------------------------------------
	char	BufferDefault[BUFFER_DEFAULT];
	char	*BufferExpansion;

	char	*Buffer;
	int		_iBufferSize;
	//------------------------------------------------------------
	// ��Ŷ���� ���� ��ġ.
	//------------------------------------------------------------
	char	*DataFieldStart;
	char	*DataFieldEnd;
	char	*HeaderFieldStart;

	//------------------------------------------------------------
	// ������ ���� ��ġ, ���� ��ġ.
	//------------------------------------------------------------
	char	*ReadPos;
	char	*WritePos;


	//------------------------------------------------------------
	// ���� ���ۿ� ������� ������.
	//------------------------------------------------------------
	int		_iDataSize;
	int		_iHeaderSize;

	//------------------------------------------------------------
	// ���� Packet�� RefCnt
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
