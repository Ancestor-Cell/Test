#ifndef __MYCONSOLE__
#define __MYCONSOLE__

#ifdef __cplusplus



#include<windows.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
using namespace std;

class MyConsole{
	public:
		HANDLE hOut;
		HANDLE hIn;
		INPUT_RECORD    mouseRec;
		DWORD           res;  
    	COORD           crPos, crHome = {0, 0};  
		CONSOLE_SCREEN_BUFFER_INFO cInfo;
		bool LastSet;
		MyConsole(){
			hIn=GetStdHandle(STD_INPUT_HANDLE);
			hOut=GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(hOut,&cInfo);
			ReadConsoleInput(hIn, &mouseRec, 1, &res);
			LastSet=0;
		}
		~MyConsole(){
			CloseHandle(hOut);
		}
		inline void Goto(short X,short Y){
			COORD pos={X,Y};
			SetConsoleCursorPosition(hOut,pos);
		}
		inline void SetColor(short FrontColor,short BackColor){
			SetConsoleTextAttribute(hOut,FrontColor|BackColor);
		}
		inline void Clean(){
			COORD pos={0,0};
			FillConsoleOutputCharacter(hOut,' ',cInfo.dwSize.X*cInfo.dwSize.Y,pos,NULL);
			Goto(0,0);
		}
		inline void HideCursor(){
			CONSOLE_CURSOR_INFO curInfo;
			curInfo.dwSize=1;
			curInfo.bVisible=0;
			SetConsoleCursorInfo(hOut,&curInfo);
		}
		inline void SetTitle(char *a){
			SetConsoleTitle(TEXT(a));
		}
		inline bool Click(){
			if(!LastSet) ReadConsoleInput(hIn, &mouseRec, 1, &res);
			if (mouseRec.EventType == MOUSE_EVENT){
				 LastSet=0;
            	return mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED;
            }
            return 0;
        }
        inline void MouseMove(){
        	ReadConsoleInput(hIn, &mouseRec, 1, &res);
        	crPos = mouseRec.Event.MouseEvent.dwMousePosition;  
            GetConsoleScreenBufferInfo(hOut, &cInfo);
            Goto(crPos.X,crPos.Y);
            LastSet=1;
        }
        inline void SetSize(int length,int width){
		    COORD pos={length, width};  
		    SMALL_RECT rc={0, 0, length-1, width-1};
		    SetConsoleWindowInfo(hOut, true, &rc);
			SetConsoleScreenBufferSize(hOut, pos);
        }
        inline bool DoubleClick(){
        	if(Click())
     			return mouseRec.Event.MouseEvent.dwEventFlags==DOUBLE_CLICK;
     		return 0;
     	}
};



#endif

#endif
