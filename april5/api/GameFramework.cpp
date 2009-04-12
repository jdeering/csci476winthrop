#include <iostream>
#include <algorithm>
using namespace std;
#include <windows.h>
#include "GameFramework.h"

void GameFramework::_clrBuffer()
{ memset(_msgBuffer, 0, GFW_BUFFER_SIZE); };

void GameFramework::kybdFunc(void (*f)(int, int))
{ cb_KH = f; };

void GameFramework::mouseFunc(void (*f)(int, int, int, int))
{ cb_MH = f; };

void GameFramework::spriteClickFunc(void (*f)(int, int, GFSprite&))
{ cb_SH = f; };

void GameFramework::gameFunc(bool (*f)())
{ cb_GL = f; };

void GameFramework::gameLoop()
{ if (cb_GL) do { _getMessages();} while(cb_GL()); }

void GameFramework::sendMessage()
{ std::cout << _msgBuffer << '\0' << std::endl; };

void GameFramework::_getMessages()
{
	DWORD bytesRead, bytesAvail;
	std::stringstream msgStream;
	char *message;
	
	msgStream.clear();
	PeekNamedPipe(stdinFW, _msgBuffer, GFW_BUFFER_SIZE, &bytesRead, &bytesAvail, NULL);
	
	if (bytesRead != 0)
	{
		_clrBuffer();
		if (bytesAvail > GFW_BUFFER_SIZE)
		{
			while (bytesRead >= GFW_BUFFER_SIZE)
			{
				_clrBuffer();
				// input handle, buffer, max message size, DWORD for bytesRead
				ReadFile(stdinFW, _msgBuffer, GFW_BUFFER_SIZE, &bytesRead, NULL);  //read the stdout pipe
				msgStream.write(_msgBuffer, bytesRead); // copy message to stringstream
				_parseMessage(msgStream);
			}
		}
		else 
		{
			// input handle, buffer, max message size, DWORD for bytesRead
			ReadFile(stdinFW, _msgBuffer, GFW_BUFFER_SIZE, &bytesRead, NULL);
			msgStream.write(_msgBuffer, bytesRead); // copy message to stringstream
			_parseMessage(msgStream);
		}
	}
	_clrBuffer(); // clears incMessage
}

void GameFramework::_parseMessage(std::stringstream &msgStream)
{
	/* SIZE OF BUFFER DATA READ */
	int p1, p2, p3, p4;

	/* MESSAGE OPCODE */
	int opcode;
	int scan_ret; 
	char message[GFW_BUFFER_SIZE];
	
	while(!msgStream.eof())
	{
		memset(message, 0, GFW_BUFFER_SIZE);
		msgStream.getline(message, GFW_BUFFER_SIZE);
		opcode = 0;

		/* SCAN FOR THE OPCODE */
		scan_ret = sscanf(message, "%d", &opcode);
		if(!opcode || scan_ret != 1) 
		{ 
			continue; 
		}
		
		switch(opcode)
		{
			case MOUSE_LOCATION_UPDATE:
				sscanf(message, "%*d %d %d", &mouseX, &mouseY);
				break;

			case MOUSE_STATE_CHANGE:
				if (!cb_MH) break;

				sscanf(message, "%*d %d %d %d %d", &p1, &p2, &p3, &p4);
				cb_MH(p1, p2, p3, p4); 
				break;
				
			case MOUSE_SPRITE_CLICK:
				if (!cb_SH) break;
				sscanf(message, "%*d %d %d %d", &p1, &p2, &p3);
				cb_SH(p1, p2, getSprite(p3)); 
				break;

			case KEY_STATE_CHANGE:
				if (!cb_KH) break;

				sscanf(message, "%*d %d %d", &p1, &p2);
				cb_KH(p1, p2); break;
		}
	}
}

GFSprite& GameFramework::createSprite(std::string aname, int x, int y, int w, int h)
{
	/* IF WE HAVE ENOUGH SPRITES ALREADY, STOP HERE */
	if (gfs_count >= GFS_MAX)
	{ 
		std::cerr << "Cannot create more than " << GFS_MAX << " sprites." << std::endl;
		return (GFSprite&)GFSprite::null;
	};

	/* IF THERE ARE SPACES IN THE ASSET NAME, EXIT AS GRACEFULLY AS POSSIBLE */
	if (aname.find(' ') != std::string::npos)
	{ std::cerr << "Malformed Asset Name: " << aname << std::endl; return (GFSprite&)GFSprite::null; };

	/* CREATE THE MESSAGE BUFFER TO SEND THE DATA TO THE FRAMEWORK */
	sprintf(_msgBuffer, "%d %d %s %d %d %d %d", SPRITE_CREATE, gfsi, aname.c_str(), x, y, w, h);

	/* SEND THE MESSAGE TO THE FRAMEWORK */
	sendMessage();

	/* FIND THE NEXT AVAILABLE INDEX */
	while (_index_table[gfsi] == INDEX_TAKEN)
	{ ++gfsi; if (gfsi >= GFSU) gfsi = GFSL; };

	/* CREATE THE OBJECT */
	_gfs.push_back(GFSprite(gfsi, x, y));

	/* INCREMENT VARIABLES */
	_index_table[gfsi] = INDEX_TAKEN; ++gfsi; ++gfs_count;

	/* RETURN THE REFERENCE */
	return _gfs.back();
}

GFSprite& GameFramework::createSprite(std::string aname, int x, int y)
{
	/* IF WE HAVE ENOUGH SPRITES ALREADY, STOP HERE */
	if (gfs_count >= GFS_MAX)
	{ 
		std::cerr << "Cannot create more than " << GFS_MAX << " sprites." << std::endl;
		return (GFSprite&)GFSprite::null;
	};

	/* IF THERE ARE SPACES IN THE ASSET NAME, EXIT AS GRACEFULLY AS POSSIBLE */
	if (aname.find(' ') != std::string::npos)
	{ std::cerr << "Malformed Asset Name: " << aname << std::endl; return (GFSprite&)GFSprite::null; };

	/* CREATE THE MESSAGE BUFFER TO SEND THE DATA TO THE FRAMEWORK */
	sprintf(_msgBuffer, "%d %d %s %d %d", SPRITE_CREATE_FROM_ASSET, gfsi, aname.c_str(), x, y);

	/* SEND THE MESSAGE TO THE FRAMEWORK */
	sendMessage();

	/* FIND THE NEXT AVAILABLE INDEX */
	while (_index_table[gfsi] == INDEX_TAKEN)
	{ ++gfsi; if (gfsi >= GFSU) gfsi = GFSL; };

	/* CREATE THE OBJECT */
	_gfs.push_back(GFSprite(gfsi, x, y));

	/* INCREMENT VARIABLES */
	_index_table[gfsi] = INDEX_TAKEN; ++gfsi; ++gfs_count;

	/* RETURN THE REFERENCE */
	return _gfs.back();
}

void GameFramework::removeSprite(GFSprite &s)
{
	/* SOMETHING IS TERRIBLY WRONG IF THIS CHECK FAILS */
	if (_index_table[s._ref] == INDEX_TAKEN)
	{
		/* MARK THE INDEX AS AVAILABLE */
		_index_table[s._ref] = INDEX_AVAIL;

		/* INFORM THE FRAMEWORK */
		sprintf(_msgBuffer, "%d %d", SPRITE_REMOVE, s._ref);

		/* SEND THE MESSAGE TO THE FRAMEWORK */
		sendMessage();

		/* REMOVE THE OFFENDING OBJECT */
		_gfs.remove(s);
	}
	/* else WHERE IS YOUR GOD NOW? */
};

GFText& GameFramework::createTextFromAsset(std::string aname, int x, int y)
{
	/* IF WE HAVE ENOUGH TEXT OBJECTS ALREADY, STOP HERE */
	if (gft_count >= GFT_MAX)
	{ 
		std::cerr << "Cannot create more than " << GFT_MAX << " text objects." << std::endl;
		return (GFText&)GFText::null;
	};

	/* IF THERE ARE SPACES IN THE ASSET NAME, EXIT AS GRACEFULLY AS POSSIBLE */
	if (aname.find(' ') != std::string::npos)
	{ std::cerr << "Malformed Asset Name: " << aname << std::endl; return (GFText&)GFText::null; };

	/* CREATE THE MESSAGE BUFFER TO SEND THE DATA TO THE FRAMEWORK */
	sprintf(_msgBuffer, "%d %d %d %d %s", TEXT_CREATE_FROM_ASSET, gfti, x, y, aname.c_str());

	/* SEND THE MESSAGE TO THE FRAMEWORK */
	sendMessage();

	/* FIND THE NEXT AVAILABLE INDEX */
	while (_index_table[gfti] == INDEX_TAKEN)
	{ ++gfti; if (gfti >= GFTU) gfti = GFTL; };

	/* CREATE THE OBJECT */
	_gft.push_back(GFText(gfti, x, y));

	/* INCREMENT VARIABLES */
	_index_table[gfti] = INDEX_TAKEN; ++gfti; ++gft_count;

	/* RETURN THE REFERENCE */
	return _gft.back();
}

GFText& GameFramework::createTextFromString(std::string str, int x, int y)
{
	/* IF WE HAVE ENOUGH TEXT OBJECTS ALREADY, STOP HERE */
	if (gft_count >= GFT_MAX)
	{ 
		std::cerr << "Cannot create more than " << GFT_MAX << " text objects." << std::endl;
		return (GFText&)GFText::null;
	};

	/* CREATE THE MESSAGE BUFFER TO SEND THE DATA TO THE FRAMEWORK */
	sprintf(_msgBuffer, "%d %d %d %d %d %s", TEXT_CREATE_FROM_STRING, gfti, str.length(), x, y, str.c_str());

	/* SEND THE MESSAGE TO THE FRAMEWORK */
	sendMessage();

	/* CREATE THE OBJECT */
	_gft.push_back(GFText(gfti, x, y));

	/* FIND THE NEXT AVAILABLE INDEX */
	while (_index_table[gfti] == INDEX_TAKEN)
	{ ++gfti; if (gfti >= GFTU) gfti = GFTL; };

	/* INCREMENT VARIABLES */
	_index_table[gfti] = INDEX_TAKEN; ++gfti; ++gft_count;

	/* RETURN THE REFERENCE */
	return _gft.back();
}

void GameFramework::removeText(GFText &t)
{
	/* SOMETHING IS TERRIBLY WRONG IF THIS CHECK FAILS */
	if (_index_table[t._ref] == INDEX_TAKEN)
	{
		/* MARK THE INDEX AS AVAILABLE */
		_index_table[t._ref] = INDEX_AVAIL;

		/* INFORM THE FRAMEWORK */
		sprintf(_msgBuffer, "%d %d", TEXT_REMOVE, t._ref);

		/* SEND THE MESSAGE TO THE FRAMEWORK */
		sendMessage();

		/* REMOVE THE OFFENDING OBJECT */
		_gft.remove(t);
	}
	/* else WHERE IS YOUR GOD NOW? */
};

void GameFramework::setTextSize(GFText &t, int size)
{
	/* SOMETHING IS TERRIBLY WRONG IF THIS CHECK FAILS */
	if (_index_table[t._ref] == INDEX_TAKEN)
	{
		/* INFORM THE FRAMEWORK */
		sprintf(_msgBuffer, "%d %d %d", TEXT_SIZE_CHANGE, t._ref, size);

		/* SEND THE MESSAGE TO THE FRAMEWORK */
		sendMessage();
	}
	/* else WHERE IS YOUR GOD NOW? */
};

void GameFramework::setTextColor(GFText &t, int r, int g, int b)
{
	/* SOMETHING IS TERRIBLY WRONG IF THIS CHECK FAILS */
	if (_index_table[t._ref] == INDEX_TAKEN)
	{
		/* INFORM THE FRAMEWORK */
		sprintf(_msgBuffer, "%d %d %d %d %d", TEXT_COLOR_CHANGE, t._ref, r, g, b);

		/* SEND THE MESSAGE TO THE FRAMEWORK */
		sendMessage();
	}
};

void GameFramework::setTextBGColor(GFText &t, int r, int g, int b)
{
	/* SOMETHING IS TERRIBLY WRONG IF THIS CHECK FAILS */
	if (_index_table[t._ref] == INDEX_TAKEN)
	{
		/* INFORM THE FRAMEWORK */
		sprintf(_msgBuffer, "%d %d %d %d %d", TEXT_BGCOLOR_CHANGE, t._ref, r, g, b);

		/* SEND THE MESSAGE TO THE FRAMEWORK */
		sendMessage();
	}
};

GFAudio& GameFramework::createAudio(std::string aname)
{
	/* IF WE HAVE ENOUGH AUDIO OBJECTS ALREADY, STOP HERE */
	if (gfa_count >= GFA_MAX)
	{ 
		std::cerr << "Cannot create more than " << GFA_MAX << " audio objects." << std::endl;
		return (GFAudio&)GFAudio::null;
	};

	/* IF THERE ARE SPACES IN THE ASSET NAME, EXIT AS GRACEFULLY AS POSSIBLE */
	if (aname.find(' ') != std::string::npos)
	{ std::cerr << "Malformed Asset Name: " << aname << std::endl; return (GFAudio&)GFAudio::null; };

	/* CREATE THE MESSAGE BUFFER TO SEND THE DATA TO THE FRAMEWORK */
	sprintf(_msgBuffer, "%d %d %s", AUDIO_CREATE, gfai, aname.c_str());

	/* SEND THE MESSAGE TO THE FRAMEWORK */
	sendMessage();

	/* FIND THE NEXT AVAILABLE INDEX */
	while (_index_table[gfai] == INDEX_TAKEN)
	{ ++gfai; if (gfai >= GFAU) gfai = GFAL; };

	/* CREATE THE OBJECT */
	_gfa.push_back(GFAudio(gfai));

	/* INCREMENT VARIABLES */
	_index_table[gfai] = INDEX_TAKEN; ++gfai; ++gfa_count;

	/* RETURN THE REFERENCE */
	return _gfa.back();
}

void GameFramework::removeAudio(GFAudio &a)
{
	/* SOMETHING IS TERRIBLY WRONG IF THIS CHECK FAILS */
	if (_index_table[a._ref] == INDEX_TAKEN)
	{
		/* MARK THE INDEX AS AVAILABLE */
		_index_table[a._ref] = INDEX_AVAIL;

		/* INFORM THE FRAMEWORK */
		sprintf(_msgBuffer, "%d %d", AUDIO_REMOVE, a._ref);

		/* SEND THE MESSAGE TO THE FRAMEWORK */
		sendMessage();

		/* REMOVE THE OFFENDING OBJECT */
		_gfa.remove(a);
	}
	/* else WHERE IS YOUR GOD NOW? */
};

GFSprite& GameFramework::getSprite(int r)
{ 
	/* TEMPORARY OBJECT FOR EQUALITY */
	GFSprite tmp(r, 0, 0); 
	
	/* FIND THE OBJECT CORRESPONDING TO THE REFERENCE NUMBER */
	std::list<GFSprite>::iterator i = find(_gfs.begin(), _gfs.end(), tmp);
	
	/* RETURN THE OBJECT */
	return (i == _gfs.end() ? (GFSprite&)GFSprite::null : *i);
};

GFText& GameFramework::getTextObj(int r)
{ 
	/* TEMPORARY OBJECT FOR EQUALITY */
	GFText tmp(r, 0, 0); 
	
	/* FIND THE OBJECT CORRESPONDING TO THE REFERENCE NUMBER */
	std::list<GFText>::iterator i = find(_gft.begin(), _gft.end(), tmp); 
	
	/* RETURN THE OBJECT */
	return (i == _gft.end() ? (GFText&)GFText::null : *i);
};

GFAudio& GameFramework::getAudioObj(int r)
{ 
	/* TEMPORARY OBJECT FOR EQUALITY */
	GFAudio tmp(r); 
	
	/* FIND THE OBJECT CORRESPONDING TO THE REFERENCE NUMBER */
	std::list<GFAudio>::iterator i = find(_gfa.begin(), _gfa.end(), tmp); 
	
	/* RETURN THE OBJECT */
	return (i == _gfa.end() ? (GFAudio&)GFAudio::null : *i);
};

/* FUNCTION POINTERS */
void (*GameFramework::cb_KH)(int, int) = NULL;
void (*GameFramework::cb_MH)(int, int, int, int) = NULL;
void (*GameFramework::cb_SH)(int, int, GFSprite&) = NULL;
bool (*GameFramework::cb_GL)() = NULL;

/* MOUSE VALUES */
int GameFramework::mouseX;
int GameFramework::mouseY;

/* MAXIMUM NUMBER OF OBJECTS */
int const GameFramework::GFT_MAX =  50;
int const GameFramework::GFA_MAX =  50;
int const GameFramework::GFS_MAX = 500;

/* LOWER BOUND FOR OBJECT INDEXES */
int const GameFramework::GFTL =   0;
int const GameFramework::GFAL = 100;
int const GameFramework::GFSL = 200;

/* SPRITE COUNT */
int GameFramework::gft_count = 0;
int GameFramework::gfa_count = 0;
int GameFramework::gfs_count = 0;

/* ITERATION VALUES FOR GF OBJECTS */
int GameFramework::gfti = GameFramework::GFTL;
int GameFramework::gfai = GameFramework::GFAL;
int GameFramework::gfsi = GameFramework::GFSL;

/* UPPER BOUND FOR OBJECT INDEXES */
int const GameFramework::GFTU = GameFramework::GFTL + GameFramework::GFT_MAX;
int const GameFramework::GFAU = GameFramework::GFAL + GameFramework::GFA_MAX;
int const GameFramework::GFSU = GameFramework::GFSL + GameFramework::GFS_MAX;

/* VALUES FOR THE INDEX TABLE */
int const GameFramework::INDEX_AVAIL = 0;
int const GameFramework::INDEX_TAKEN = 1;

HANDLE GameFramework::stdinFW = GetStdHandle(STD_INPUT_HANDLE);
HANDLE GameFramework::stdoutFW = GetStdHandle(STD_OUTPUT_HANDLE);

char GameFramework::_msgBuffer[GameFramework::GFW_BUFFER_SIZE] = {0};
int GameFramework::_index_table[GameFramework::INDEX_TABLE_SIZE] = {GameFramework::INDEX_AVAIL};

std::list<GFSprite> GameFramework::_gfs;
std::list<GFText> GameFramework::_gft;
std::list<GFAudio> GameFramework::_gfa;
