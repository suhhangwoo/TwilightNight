#pragma once
#pragma comment (lib, "msimg32.lib")
#include <windows.h>	

#define TIMER_UPDATE 1				//������Ʈ Ÿ�̸� �ĺ� ��ȣ
#define TIMER_UPDATE_UNIT 10		//������Ʈ Ÿ�̸� ���� �ð�

//��Ʈ�� ��� ����
#define BITMAP_PLAYER_0 IDB_BITMAP1    
#define BITMAP_PLAYER_1 IDB_BITMAP2    
#define BITMAP_PLAYER_2 IDB_BITMAP3    
#define BITMAP_PLAYER_3 IDB_BITMAP4    
#define BITMAP_PLAYER_4 IDB_BITMAP8                   
#define BITMAP_PLAYER_5 IDB_BITMAP9                   
#define BITMAP_PLAYER_6 IDB_BITMAP10       
#define BITMAP_BG IDB_BITMAP7

enum WeaponKind {
	NONE,
	ROUND,
	SHOOT,
	BOUNCE,
	FALL,
	LAST,
	END
};


//string StringCut(string word, char dWord) {
//	size_t pos = word.find(dWord);
//
//	if (pos != string::npos) {
//		string sub = word.substr(0, pos);
//		return sub;
//	}
//	else return word;
//}