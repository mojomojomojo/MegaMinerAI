//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "AI.h"
#include "network.h"
#include "game.h"

using namespace std;

int main(int argc, char** argv, char** env)
{

  // Parse the command-line. For real.
  int gameNumber = -1;
  char server_port[64];
  char* server_name = NULL;
  int noflag_args = 0;
  strncpy(server_port,"19000",6);
  for (int i=1; i<argc; i++) {
    if (string(argv[i]).compare("-port")==0 && i+1<argc) {
      cout << "  Using alternate server port: ";
      strncpy(server_port,argv[++i],63);
      server_port[63] = 0x0; // just in case -- haha, hackers!
      cout << server_port << endl;
    } else if (string(argv[i]).compare("-game")==0 && i+1<argc) {
      cout << "  Joining Game Number: ";
      gameNumber = atoi(argv[++i]);
      cout << gameNumber << endl;
    } else if (string(argv[i]).compare("-server")==0 && i+1<argc) {
      server_name = argv[++i];
    } else {
      noflag_args++;
    }
  }
  cout << "  " << noflag_args << " arguments without flags." << endl;
  // Support the stardard interface: <exe> <host> [<game_number>]
  if (noflag_args >= 1) server_name = argv[1];
  cout << "  Server: " << server_name << endl;
  if (noflag_args >= 2 && gameNumber == -1) {
    cout << "  Joining Game Number: ";
    gameNumber = atoi(argv[2]);
    cout << gameNumber << endl;
  }

  if(argc < 2)
  {
    cout<<"Please enter a host name."<<endl;
    return 1;
  }

  Connection* c;
  c = createConnection();
  AI ai(c);
  ai.configure(argc,argv,env);

  if(!serverConnect(c, server_name, server_port))
  {
    cerr << "Unable to connect to server" << endl;
    return 1;
  }
  if(!serverLogin(c, ai.username(), ai.password()))
  {
    return 1;
  }

  if(gameNumber == -1)
  {
    gameNumber = createGame(c);
  }
  else
  {
    if(!joinGame(c, gameNumber))
    {
      cerr << "Error joining game." << endl;
      return 1;
    }
  }
  while(networkLoop(c))
  {
    if(ai.startTurn())
    {
      endTurn(c);
    }
    else
    {
      getStatus(c);
    }
  }
  ai.end();
  //Grab a log
  networkLoop(c);
  //Grab the end game status
  networkLoop(c);
  destroyConnection(c);
  return 0;
}
